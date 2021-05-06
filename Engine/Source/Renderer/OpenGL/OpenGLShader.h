#pragma once

#include "../Shader.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace Engine {
    const char* defaultVertexShaderPath   = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.frag";
    const char* defaultFragmentShaderPath = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.vert";

    class OpenGLShader : public Shader {
    public:
        OpenGLShader() = default;
        OpenGLShader(std::string&& vShaderCode, std::string&& fShaderCode, std::string&& gShaderCode = "");

        void use();

        void setBool (const std::string& name, bool  value                       ) override;
        void setInt  (const std::string& name, int   value                       ) override;
        void setFloat(const std::string& name, float value                       ) override;
        void setVec2 (const std::string& name, const glm::vec2& value            ) override;
        void setVec2 (const std::string& name, float x, float y                  ) override;
        void setVec3 (const std::string& name, const glm::vec3& value            ) override;
        void setVec3 (const std::string& name, float x, float y, float z         ) override;
        void setVec4 (const std::string& name, const glm::vec4& value            ) override;
        void setVec4 (const std::string& name, float x, float y, float z, float w) override;
        void setMat2 (const std::string& name, const glm::mat2& mat              ) override;
        void setMat3 (const std::string& name, const glm::mat3& mat              ) override;
        void setMat4 (const std::string& name, const glm::mat4& mat              ) override;

    private:
        void checkCompileErrors(GLuint shader, std::string type);
    };
}