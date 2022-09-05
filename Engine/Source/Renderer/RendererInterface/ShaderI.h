#pragma once

#include <Aliases.h>

#include "glm/glm.hpp"

namespace PetrolEngine {
    class ShaderI {
    public:
        uint32 ID;
        String name;
        
        virtual ~ShaderI() = default;
        virtual int recompileShader( const char* vertexShaderSourceCode   = nullptr,
                                     const char* fragmentShaderSourceCode = nullptr,
                                     const char* geometryShaderSourceCode = nullptr  ) = 0;

        // utility uniform functions

        virtual void setInt  ( const String& name, int   x                            ) = 0;
        virtual void setUint ( const String& name, uint  x                            ) = 0;
        virtual void setBool ( const String& name, bool  x                            ) = 0;
        virtual void setFloat( const String& name, float x                            ) = 0;
        virtual void setVec2 ( const String& name, float x, float y                   ) = 0;
        virtual void setVec3 ( const String& name, float x, float y, float z          ) = 0;
        virtual void setVec4 ( const String& name, float x, float y, float z, float w ) = 0;
        virtual void setVec2 ( const String& name, const glm::vec2& x ) = 0;
        virtual void setVec3 ( const String& name, const glm::vec3& x ) = 0;
        virtual void setVec4 ( const String& name, const glm::vec4& x ) = 0;
        virtual void setMat2 ( const String& name, const glm::mat2& x ) = 0;
        virtual void setMat3 ( const String& name, const glm::mat3& x ) = 0;
        virtual void setMat4 ( const String& name, const glm::mat4& x ) = 0;
        
    protected:
        uint32 geometryShaderID;
        uint32 fragmentShaderID;
        uint32   vertexShaderID;
    };

}