#pragma once

#include <Aliases.h>

#include "RendererResourceCreator.h"

#include <glm/glm.hpp>

namespace PetrolEngine {
    class Shader {
    public:
        uint32 ID;
        String name;
        
        virtual ~Shader() = 0;
        virtual int recompileShader( const char* vertexShaderSourceCode   = nullptr,
                                     const char* fragmentShaderSourceCode = nullptr,
                                     const char* geometryShaderSourceCode = nullptr  ) = 0;
        
        // remove all possible constructors (Shader is just interface for API shader)

        /// <summary>
        /// Loads and creates shader from a single file.
        /// Shaders are separated by "#{ShaderType}"
        /// Eg.
        /// <para>#vertexShader   </para>
        /// <para>...             </para>
        /// <para>#fragmentShader </para>
        /// <para>...             </para>
        /// If any  ShaderTypes will be missing,
        /// it will be replaced with default ones.
        /// </summary>
        /// <param name="path">- path to the shader</param>
        /// <returns>shared pointer to shader</returns>
        static Shader* create( RRC* creator, const String& path );
        
        /// <summary>
        /// Creates Shader using source code.
        /// If any shader source code will be missing it will be replaced with default.
        /// </summary>
        /// <param name="name"       > - unique name for the shader    </param>
        /// <param name="vertexSrc"  > - source code of vertex shader  </param>
        /// <param name="fragmentSrc"> - source code of fragment shader</param>
        /// <param name="geometrySrc"> - source code of geometry shader</param>
        /// <returns>shared pointer to the shader</returns>
        static Shader* create( RRC*         creator,
                               String&&   vertexSrc,
                               String&& fragmentSrc,
                               String&& geometrySrc  );

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