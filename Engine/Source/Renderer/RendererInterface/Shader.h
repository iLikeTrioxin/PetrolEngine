#pragma once

#include <Aliases.h>

#include "glm/glm.hpp"
#include <shaderc/shaderc.hpp>
#include <utility>
#include "UniformBuffer.h"

namespace PetrolEngine {

    enum class ShaderType {
        Vertex, Fragment, Geometry
    };

    shaderc_shader_kind shaderTypeToShadercShaderKind(ShaderType type);

    class Shader {
    public:
        String name;
        
        virtual ~Shader() = default;

        // utility uniform functions
        void compile();

        virtual void compileNative(
                const String& vertexShaderSourceCode  ,
                const String& fragmentShaderSourceCode,
                const String& geometryShaderSourceCode
        ) = 0;

        void recomplie(
                const String& vertexShaderSourceCode  ,
                const String& fragmentShaderSourceCode,
                const String& geometryShaderSourceCode = "") {
            this->vertexShaderSourceCode = vertexShaderSourceCode;
            this->fragmentShaderSourceCode = fragmentShaderSourceCode;

            if(!geometryShaderSourceCode.empty())
                this->geometryShaderSourceCode = geometryShaderSourceCode;

            compile();
        }

        uint32 getID() const { return ID; }
        String getName() const { return name; }

        void reflect(const Vector<uint32>& spv, ShaderType type);
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

        virtual void bindUniformBuffer(const String& name, UniformBuffer* uniformBuffer) = 0;

        class UniformBinding {
        public:
            Shader* shader;
            String  name;

            UniformBinding(Shader* shader, String name): shader(shader), name(std::move(name)) {}
            UniformBinding(const UniformBinding& other) = delete;

            void operator=(UniformBuffer* buffer) const { shader->bindUniformBuffer(name, buffer); }
        };
        UniformBinding operator[] (const String& name) {
            return {this, name};
        }

        struct Metadata{
            UnorderedMap<String, uint32> uniforms;
            Vector<uint32> textures;
        } metadata;

    protected:
        uint32 geometryShaderID;
        uint32 fragmentShaderID;
        uint32   vertexShaderID;
        uint32               ID;

        virtual void compileFromSpv(
                Vector<uint32>* vertexByteCode,
                Vector<uint32>* fragmentByteCode,
                Vector<uint32>* geometryByteCode
        ) = 0;

        // optional
        String geometryShaderSourceCode;
        String fragmentShaderSourceCode;
        String   vertexShaderSourceCode;

        // spv byte code
        Vector<uint32> vertexByteCode  ;
        Vector<uint32> fragmentByteCode;
        Vector<uint32> geometryByteCode;
    };

}