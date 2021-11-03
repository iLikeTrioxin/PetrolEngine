#pragma once

#include <Aliases.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace PetrolEngine{

    class Sound{
    public:
        static void playSound(const char* file);
        static int init();

    private:
        static int soundPlayer(const char* file);
        static ALCdevice* device;
        static ALCcontext* context;
    };
}