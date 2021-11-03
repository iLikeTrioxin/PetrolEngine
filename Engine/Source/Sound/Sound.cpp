#include <PCH.h>

#include "Sound.h"

#include <thread>
#include <iostream>
#include <fstream>

#include <AL/al.h>
#include <AL/alc.h>

// TODO: rework this global sound system to actually work

static bool isBigEndian() {
    static const int a = 1;

    return !((char*)&a)[0];
}

static int convertToInt(const char* buffer, int len) {
    int a = 0;

    if   (!isBigEndian()) for (int i = 0; i<len; i++) ((char*)&a)[    i] = buffer[i];
    else                  for (int i = 0; i<len; i++) ((char*)&a)[3 - i] = buffer[i];

    return a;
}

static char* loadWAV(const char* fn, uint16& channels, uint32& samplerate, uint16& bitsPerSample, uint32& size) {
    char buffer[4];
    std::ifstream in(fn, std::ios::binary);

    // TODO: Figure out why Chunk2 data size does not provide correct size

    // I'm reading fileSize and then subtracting some length to
    // get audio data size because of reason described above
    in.seekg (0, std::ifstream::end);
    size = (uint32) in.tellg() - 78;
    in.seekg (0, std::ifstream::beg);

    /* .wav file structure
     *  Location ;    Field name    ;       Sample value      ;  Size
     * -----------------------------------------------------------------
     *    0 -4   ; Chunk ID         ; RIFF                    ; 4 Bytes
     *    4 -8   ; Chunk data size  ; 36 + {Chunk2 data size} ; 4 Bytes
     *    8 -12  ; RIFF type ID     ; WAVE                    ; 4 Bytes
     *    12-16  ; Chunk1 ID        ; fmt                     ; 4 Bytes
     *    16-20  ; Chunk1 data size ; 16                      ; 4 Bytes
     *    20-22  ; Format tag       ; 1                       ; 2 Bytes
     *    22-24  ; Channels number  ; 2                       ; 2 Bytes
     *    24-28  ; Samplerate       ; 44100                   ; 4 Bytes
     *    28-32  ; Byte rate        ; 176400                  ; 4 Bytes
     *    32-34  ; Block align      ; 4                       ; 2 Bytes
     *    34-36  ; Bits per sample  ; 16                      ; 2 Bytes
     *    36-40  ; Chunk2 ID        ; data                    ; 4 Bytes
     *    40-44  ; Chunk2 data size ; samples*channels*bps/8  ; 4 Bytes
     *    44-xx  ; Audio data       ; Binary data             ; x Bytes
     */

    in.read(buffer, 4); // Chunk ID

    if (strncmp(buffer, "RIFF", 4) != 0) { LOG("Tried to load not a valid WAVE file.", 2); return nullptr; }

    in.read(buffer, 4); // Chunk data size
    in.read(buffer, 4); // RIFF type ID
    in.read(buffer, 4); // Chunk1 ID
    in.read(buffer, 4); // Chunk1 data size
    in.read(buffer, 2); // Format tag

    in.read(buffer, 2); // Channels number
    channels = convertToInt(buffer, 2);

    in.read(buffer, 4); // Samplerate
    samplerate = convertToInt(buffer, 4);

    in.read(buffer, 4); // Byte rate //-V525
    in.read(buffer, 2); // Block align

    in.read(buffer, 2); // Bits per sample
    bitsPerSample = convertToInt(buffer, 2);

    in.read(buffer, 4); // Chunk2 ID
    in.read(buffer, 4); // Chunk2 data size

    char* data = new char[size];
    in.read(data  , size); // Audio data

    return data;
}

namespace PetrolEngine {
    ALCdevice* Sound::device;
    ALCcontext* Sound::context;

    int Sound::init() {
        device = alcOpenDevice(nullptr);

        if (!device) { LOG("Cannot open sound card.", 3); return 1; }

        context = alcCreateContext(device, nullptr);

        if ( !context || !alcMakeContextCurrent(context) ) {
            if (context) alcDestroyContext(context);
            alcCloseDevice(device);
            LOG("Cannot open sound card context.", 3);
            return 2;
        }

        return 0;
    }

    int Sound::soundPlayer(const char *file) {
        if ( !context || !alcMakeContextCurrent(context) ) {
            if (context) alcDestroyContext(context);
            alcCloseDevice(device);
            LOG("Cannot open sound card context.", 3);
            return 2;
        }

        uint16 bps, channel, format;
        uint32 sampleRate, size;
        char *data = loadWAV(file, channel, sampleRate, bps, size);

        if (channel == 1) {
            if (bps == 8) { format = AL_FORMAT_MONO8 ; }
            else          { format = AL_FORMAT_MONO16; }
        } else {
            if (bps == 8) { format = AL_FORMAT_STEREO8 ; }
            else          { format = AL_FORMAT_STEREO16; }
        }

        unsigned int bufferID;
        alGenBuffers(1, &bufferID);
        alBufferData(bufferID, format, data, (int) size, (int) sampleRate);

        unsigned int sourceID;
        alGenSources(1, &sourceID);
        alSourcei(sourceID, AL_BUFFER, (int) bufferID);

        ALenum state;

        alSourcePlay(sourceID);
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
        } while (alGetError() == AL_NO_ERROR && state == AL_PLAYING);

        alDeleteSources(1, &sourceID);
        alDeleteBuffers(1, &bufferID);

        alcDestroyContext(context);
        alcCloseDevice(device);

        return 0;
    }

    void Sound::playSound(const char *file) {
        new std::thread(soundPlayer, file);
    }
}