#pragma once

#include "../Shader.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace PetrolEngine {
    class VulkanShader : public Shader {
    public:
        VulkanShader( const char* vertexShaderSourceCode   = nullptr,
                      const char* fragmentShaderSourceCode = nullptr,
                      const char* geometryShaderSourceCode = nullptr );
        
        ~VulkanShader() override;

        int recompileShader(const char* vertexShaderSourceCode  ,
                            const char* fragmentShaderSourceCode,
                            const char* geometryShaderSourceCode ) override;

        void setBool (const String& name, bool  value                       ) override;
        void setInt  (const String& name, int   value                       ) override;
        void setFloat(const String& name, float value                       ) override;
        void setVec2 (const String& name, const glm::vec2& value            ) override;
        void setVec2 (const String& name, float x, float y                  ) override;
        void setVec3 (const String& name, const glm::vec3& value            ) override;
        void setVec3 (const String& name, float x, float y, float z         ) override;
        void setVec4 (const String& name, const glm::vec4& value            ) override;
        void setVec4 (const String& name, float x, float y, float z, float w) override;
        void setMat2 (const String& name, const glm::mat2& mat              ) override;
        void setMat3 (const String& name, const glm::mat3& mat              ) override;
        void setMat4 (const String& name, const glm::mat4& mat              ) override;

    private:
        int checkShaderCompileErrors (GLuint shader, String type);
        int checkProgramCompileErrors(GLuint shader             );
    };
}