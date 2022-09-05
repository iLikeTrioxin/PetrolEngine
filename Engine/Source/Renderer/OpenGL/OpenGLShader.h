#pragma once

#include "Renderer/RendererInterface/ShaderI.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace PetrolEngine {
    class OpenGLShader : public ShaderI {
    public:
        OpenGLShader( const char* vertexShaderSourceCode  ,
                      const char* fragmentShaderSourceCode,
                      const char* geometryShaderSourceCode  );
        
        ~OpenGLShader() override;

        int recompileShader( const char* vertexShaderSourceCode  ,
                             const char* fragmentShaderSourceCode,
                             const char* geometryShaderSourceCode  ) override;

        void setInt  ( const String& uniform, int   x                           ) override;
        void setUint ( const String& uniform, uint  x                           ) override;
        void setBool ( const String& uniform, bool  x                           ) override;
        void setFloat( const String& uniform, float x                           ) override;
        void setVec2 ( const String& uniform, float x, float y                  ) override;
        void setVec3 ( const String& uniform, float x, float y, float z         ) override;
        void setVec4 ( const String& uniform, float x, float y, float z, float w) override;
        void setVec2 ( const String& uniform, const glm::vec2& x ) override;
        void setVec3 ( const String& uniform, const glm::vec3& x ) override;
        void setVec4 ( const String& uniform, const glm::vec4& x ) override;
        void setMat2 ( const String& uniform, const glm::mat2& x ) override;
        void setMat3 ( const String& uniform, const glm::mat3& x ) override;
        void setMat4 ( const String& uniform, const glm::mat4& x ) override;

    private:
        static int checkShaderCompileErrors (GLuint shader, const String& type);
        static int checkProgramCompileErrors(GLuint shader);
    };
}