#include <PCH.h>

#include "Files.h"

#include <fstream>

namespace PetrolEngine {
    std::string ReadFile(const std::string& filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII

        if (!in) { DEBUG_LOG("[!] Failed to read content of file(" << filepath << ")"); return ""; }

        in.seekg(0, std::ios::end);
        long size = in.tellg();

        if (size == -1) { DEBUG_LOG("[!] Failed to read content of file(" << filepath << ")"); return ""; }

        result.resize(size);

        in.seekg(0, std::ios::beg);
        in.read(&result[0], size);

        return result;
    }
}