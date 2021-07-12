#pragma once

#include "../Shader.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace Engine {
    static const char* defaultVertexShaderPath   = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.frag";
    static const char* defaultFragmentShaderPath = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.vert";

    class OpenGLShader : public Shader {
    public:
        OpenGLShader( const char* vertexShaderSourceCode   = nullptr,
                      const char* fragmentShaderSourceCode = nullptr,
                      const char* geometryShaderSourceCode = nullptr );
        
        ~OpenGLShader();

        virtual int recompileShader(const char* vertexShaderSourceCode   = nullptr,
                                    const char* fragmentShaderSourceCode = nullptr,
                                    const char* geometryShaderSourceCode = nullptr ) override;

        virtual void setBool (const std::string& name, bool  value                       ) override;
        virtual void setInt  (const std::string& name, int   value                       ) override;
        virtual void setFloat(const std::string& name, float value                       ) override;
        virtual void setVec2 (const std::string& name, const glm::vec2& value            ) override;
        virtual void setVec2 (const std::string& name, float x, float y                  ) override;
        virtual void setVec3 (const std::string& name, const glm::vec3& value            ) override;
        virtual void setVec3 (const std::string& name, float x, float y, float z         ) override;
        virtual void setVec4 (const std::string& name, const glm::vec4& value            ) override;
        virtual void setVec4 (const std::string& name, float x, float y, float z, float w) override;
        virtual void setMat2 (const std::string& name, const glm::mat2& mat              ) override;
        virtual void setMat3 (const std::string& name, const glm::mat3& mat              ) override;
        virtual void setMat4 (const std::string& name, const glm::mat4& mat              ) override;

    private:
        int checkShaderCompileErrors(GLuint shader, std::string type);
        int checkProgramCompileErrors(GLuint shader);
    };
}