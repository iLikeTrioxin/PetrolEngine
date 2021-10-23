This file describes how you can contribute to this respository.

I describe here those topics:
    - General contribution info
    - Prefered code style      


//
// General info
//

So to begin with, I'm open to any sugesstions
that can help improve my code or knowlage.

If you see any bugs or things I could do better
please commit your change or tell me about it
on discord or any other media (can be found on https://www.yukiteru.xyz)

//
// Prefered code style
//

before:
    - lower camel case (ex. lowerCamelCase)
    - upper camel case (ex. UpperCamelCase) so called pascal case
    - all caps    case (ex. ALLCAPSCASE)


Variable names are written with lower camel case.
    int someVariable;

Class names are written using upper camel case.
    class SomeClass

Files and directories are also named upper camel case.
    PetrolEngine/Deps/Xyz.cpp

Macros are all caps with words seperated with '_'
    DEBUG_LOG(msg)

Internal includes like Rednerer/Renderer.h are in ""
    #include "Rednerer/Renderer.h"

External includes like GLFW/glfw3.h are in <>
    #include <GLFW/glfw3.h>
