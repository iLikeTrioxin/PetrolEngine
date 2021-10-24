#pragma once

#include "../Shader.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace PetrolEngine {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader( const char* vertexShaderSourceCode  ,
                      const char* fragmentShaderSourceCode,
                      const char* geometryShaderSourceCode  );
        
        ~OpenGLShader() override;

        int recompileShader( const char* vertexShaderSourceCode  ,
                             const char* fragmentShaderSourceCode,
                             const char* geometryShaderSourceCode  ) override;

        void setInt  ( const String& name, int   x                           ) override;
        void setBool ( const String& name, bool  x                           ) override;
        void setFloat( const String& name, float x                           ) override;
        void setVec2 ( const String& name, float x, float y                  ) override;
        void setVec3 ( const String& name, float x, float y, float z         ) override;
        void setVec4 ( const String& name, float x, float y, float z, float w) override;
        void setVec2 ( const String& name, const glm::vec2& x ) override;
        void setVec3 ( const String& name, const glm::vec3& x ) override;
        void setVec4 ( const String& name, const glm::vec4& x ) override;
        void setMat2 ( const String& name, const glm::mat2& x ) override;
        void setMat3 ( const String& name, const glm::mat3& x ) override;
        void setMat4 ( const String& name, const glm::mat4& x ) override;

    private:
        int checkShaderCompileErrors(GLuint shader, std::string type);
        int checkProgramCompileErrors(GLuint shader);
    };
}