#include <PCH.h>

#include "MetalShader.h"

#include "../../Core/Files.h"

#include <spirv_cross.hpp>
#include <spirv_glsl.hpp>
#include <shaderc/shaderc.hpp>

namespace PetrolEngine {

    Vector<uint32>* MetalShader::fromSpvToGlslSpv(Vector<uint32>* spv, ShaderType type) {
        LOG("Shader compilation failed: ", 3);
        return nullptr;
    }

    void MetalShader::compileFromSpv(Vector<uint32>*   vertexByteCode,
                                      Vector<uint32>* fragmentByteCode,
                                      Vector<uint32>* geometryByteCode ){
        // code
    }

    MetalShader::MetalShader( String         name,
                                String   vertexCode,
                                String fragmentCode,
                                String geometryCode ) {
        this->vertexShaderSourceCode   =   vertexCode;
        this->fragmentShaderSourceCode = fragmentCode;
        this->geometryShaderSourceCode = geometryCode;

        this->name = name;
        this->compile();
    }

    MetalShader::~MetalShader() {
    }

    void MetalShader::compileNative( const String& vertexShaderSourceCode  ,
                                      const String& fragmentShaderSourceCode,
                                      const String& geometryShaderSourceCode ) {
    }

    void MetalShader::setVec4(const String& uniform, float x, float y, float z, float w) {
    }
    void MetalShader::setBool(const String& uniform, bool     x) {
    }
    void MetalShader::setInt(const String& uniform, int      x) {
    }
    void MetalShader::setUint(const String& uniform, uint      x) {
    }
    void MetalShader::setFloat(const String& uniform, float     x) {
    }
    void MetalShader::setVec2(const String& uniform, const glm::vec2& x) {
    }
    void MetalShader::setVec2(const String& uniform, float x, float    y) {
    }
    void MetalShader::setVec3(const String& uniform, const glm::vec3& x) {
    }
    void MetalShader::setVec3(const String& uniform, float x, float y, float z) {
    }
    void MetalShader::setVec4(const String& uniform, const glm::vec4& x) {
    }
    void MetalShader::setMat2(const String& uniform, const glm::mat2& mat) {
    }
    void MetalShader::setMat3(const String& uniform, const glm::mat3& mat) {
    }
    void MetalShader::setMat4(const String& uniform, const glm::mat4& mat) {
    }

    int MetalShader::checkProgramCompileErrors(GLuint id) {
        return 1;
    }

    int MetalShader::checkShaderCompileErrors(GLuint shader, const String& type) {
        return 1;
    }
}