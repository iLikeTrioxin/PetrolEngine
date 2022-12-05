#pragma once

#include <Aliases.h>

#include "Component.h"

namespace PetrolEngine{
    class TextMesh : public Component {
    public:
        TextMesh(String text);

    private:
        String text;
    };
}