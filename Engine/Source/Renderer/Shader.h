#pragma once

#include <memory>
#include <sstream>
#include <fstream>
#include <map>

namespace Engine {
    class Shader {
    public:
        uint32_t ID;
        
        template<>
        Shader(){}

        virtual ~Shader() = default;
        
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
        static std::shared_ptr<Shader> load(std::string path);
        
        /// <summary>
        /// Creates Shader using source code.
        /// If any shader source code will be missing it will be replaced with default.
        /// </summary>
        /// <param name="name"       > - unique name for the shader    </param>
        /// <param name="vertexSrc"  > - source code of vertex shader  </param>
        /// <param name="fragmentSrc"> - source code of fragment shader</param>
        /// <param name="geometrySrc"> - source code of geometry shader</param>
        /// <returns>shared pointer to the shader</returns>
        static std::shared_ptr<Shader> load(std::string&&        name,
                                            std::string&&   vertexSrc = "",
                                            std::string&& fragmentSrc = "",
                                            std::string&& geometrySrc = "" );

        // activate the shader
        virtual void use();
        
        // utility uniform functions

        virtual void setBool (const std::string& name, bool  value);
        virtual void setInt  (const std::string& name, int   value);
        virtual void setFloat(const std::string& name, float value);
        virtual void setVec2 (const std::string& name, const glm::vec2& value);
        virtual void setVec2 (const std::string& name, float x, float y);
        virtual void setVec3 (const std::string& name, const glm::vec3& value);
        virtual void setVec3 (const std::string& name, float x, float y, float z);
        virtual void setVec4 (const std::string& name, const glm::vec4& value);
        virtual void setVec4 (const std::string& name, float x, float y, float z, float w);
        virtual void setMat2 (const std::string& name, const glm::mat2& mat);
        virtual void setMat3 (const std::string& name, const glm::mat3& mat);
        virtual void setMat4 (const std::string& name, const glm::mat4& mat);
        
    private:
        static std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;
        
        // creates a shader with current graphics API (it do not prevent copying, use load instead)
        static std::shared_ptr<Shader> create(std::string&&   vertexSrc,
                                              std::string&& fragmentSrc,
                                              std::string&& geometrySrc );
    };

}