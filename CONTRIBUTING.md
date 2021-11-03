####This file describes how you can contribute to this respository.

#I describe here those topics:
- ####General contribution info
- ####Preferred code style      



#General info

So to begin with, I'm open to any suggestions
that can help improve my code or knowledge.

If you see any bugs or things I could do better
please commit your change or tell me about it
on discord or any other media (can be found on https://www.yukiteru.xyz)


# Preferred code style


##before:
- lower camel case (ex. lowerCamelCase)
- upper camel case (ex. UpperCamelCase) so called pascal case
- all caps    case (ex. ALLCAPSCASE)


###Variable names are written with lower camel case.
```c++
int someVariable;
```

###Class names are written using upper camel case.
```c++
class SomeClass
```

###Files and directories are also named upper camel case.
```
PetrolEngine/Deps/Xyz.cpp
```

###Macros are all caps with words seperated with '_'
```c++
DEBUG_LOG("some message");
```

###Internal includes like Renderer/Renderer.h are in ""
```c++
#include "Renderer/Renderer.h"
```

###External includes like GLFW/glfw3.h are in <>
```c++
#include <GLFW/glfw3.h>
```

#Future

## Code

### My goto code style is something like:
```c++
Window* window = new Window(...);
Renderer* renderer = new Renderer(...);

renderer.bind(window);

```