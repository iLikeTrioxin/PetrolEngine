#pragma once

#include <Aliases.h>

#include <memory>
#include <sstream>
#include <fstream>
#include <map>

#include <glm/glm.hpp>

namespace PetrolEngine {
    class Shader {
    public:
        uint32_t ID;
        std::string name;
        
        virtual ~Shader() = default;
        virtual int recompileShader(const char* vertexShaderSourceCode   = nullptr,
                                    const char* fragmentShaderSourceCode = nullptr,
                                    const char* geometryShaderSourceCode = nullptr ) = 0;
        
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
        static std::shared_ptr<Shader> load(const String& path);
        
        /// <summary>
        /// Creates Shader using source code.
        /// If any shader source code will be missing it will be replaced with default.
        /// </summary>
        /// <param name="name"       > - unique name for the shader    </param>
        /// <param name="vertexSrc"  > - source code of vertex shader  </param>
        /// <param name="fragmentSrc"> - source code of fragment shader</param>
        /// <param name="geometrySrc"> - source code of geometry shader</param>
        /// <returns>shared pointer to the shader</returns>
        static std::shared_ptr<Shader> load(String&&        name,
                                            String&&   vertexSrc = "",
                                            String&& fragmentSrc = "",
                                            String&& geometrySrc = "" );

        // utility uniform functions

        virtual void setBool (const String& name, bool  value                        ) = 0;
        virtual void setInt  (const String& name, int   value                        ) = 0;
        virtual void setFloat(const String& name, float value                        ) = 0;
        virtual void setVec2 (const String& name, const glm::vec2& value             ) = 0;
        virtual void setVec2 (const String& name, float x, float y                   ) = 0;
        virtual void setVec3 (const String& name, const glm::vec3& value             ) = 0;
        virtual void setVec3 (const String& name, float x, float y, float z          ) = 0;
        virtual void setVec4 (const String& name, const glm::vec4& value             ) = 0;
        virtual void setVec4 (const String& name, float x, float y, float z, float w ) = 0;
        virtual void setMat2 (const String& name, const glm::mat2& mat               ) = 0;
        virtual void setMat3 (const String& name, const glm::mat3& mat               ) = 0;
        virtual void setMat4 (const String& name, const glm::mat4& mat               ) = 0;
        
    protected:
        uint32_t geometryShaderID;
        uint32_t fragmentShaderID;
        uint32_t   vertexShaderID;

    private:
        static std::unordered_map<String, std::shared_ptr<Shader>> loadedShaders;
        
        // creates a shader with current graphics API (it do not prevent copying, use load instead)
        static std::shared_ptr<Shader> create(String&&   vertexSrc,
                                              String&& fragmentSrc,
                                              String&& geometrySrc );
    };

}