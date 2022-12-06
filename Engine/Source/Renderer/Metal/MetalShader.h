#pragma once

#include "Renderer/RendererInterface/Shader.h"
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

namespace PetrolEngine {
    class MetalShader : public Shader {
    public:
        MetalShader( String         name,
                      String   vertexCode,
                      String fragmentCode,
                      String geometryCode  );
        
        ~MetalShader() override;

        Vector<uint32>* fromSpvToGlslSpv(Vector<uint32>* spv, ShaderType type);

        //void reflect(Vector<uint32>* spv, ShaderType type);

        void compileFromSpv(
                Vector<uint32>* vertexByteCode,
                Vector<uint32>* fragmentByteCode,
                Vector<uint32>* geometryByteCode
        ) override;

        void compileNative(
                const String& vertexShaderSourceCode  ,
                const String& fragmentShaderSourceCode,
                const String& geometryShaderSourceCode
        ) override;

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

        void bindUniformBuffer(const String& name, UniformBuffer* uniformBuffer) override{
            uint32 bind = this->metadata.uniforms[name];
            glUniformBlockBinding(this->ID, bind, uniformBuffer->getBinding());
        }

    protected:
        static int checkShaderCompileErrors (GLuint shader, const String& type);
        static int checkProgramCompileErrors(GLuint shader);
    };
}