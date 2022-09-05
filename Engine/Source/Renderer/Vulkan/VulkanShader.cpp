#include <PCH.h>

#include "VulkanShader.h"

#include "Renderer/RawRenderer/ShaderApi.h"
#include "../../Core/Files.h"
#include <fstream>

//
// INFO
// 1. I use here properties of glShaderXXX(shader) which is stated at khronos site "A value of 0 for shader will be silently ignored."
//

namespace PetrolEngine {

    int VulkanShader::recompileShader( const char* vertexShaderSourceCode  ,
                                       const char* fragmentShaderSourceCode,
                                       const char* geometryShaderSourceCode ) {
        return 0;
    }

    VulkanShader::VulkanShader( const char* vertexShaderSourceCode  ,
                                const char* fragmentShaderSourceCode,
                                const char* geometryShaderSourceCode ) {}

    VulkanShader::~VulkanShader() {}

    void VulkanShader::setVec4(const std::string& name, float x, float y, float z, float w) {}
    void VulkanShader::setBool(const std::string& name, bool     value) {}
    void VulkanShader::setInt(const std::string& name, int      value) {}
    void VulkanShader::setUint(const String &name, uint x) {}
    void VulkanShader::setFloat(const std::string& name, float     value) {}
    void VulkanShader::setVec2(const std::string& name, const glm::vec2& value) {}
    void VulkanShader::setVec2(const std::string& name, float x, float    y) {}
    void VulkanShader::setVec3(const std::string& name, const glm::vec3& value) {}
    void VulkanShader::setVec3(const std::string& name, float x, float y, float z) {}
    void VulkanShader::setVec4(const std::string& name, const glm::vec4& value) {}
    void VulkanShader::setMat2(const std::string& name, const glm::mat2& mat) {}
    void VulkanShader::setMat3(const std::string& name, const glm::mat3& mat) {}
    void VulkanShader::setMat4(const std::string& name, const glm::mat4& mat) {}

    int VulkanShader::checkProgramCompileErrors(GLuint shader) {
        return 0;
    }

    int VulkanShader::checkShaderCompileErrors(GLuint shader, std::string type) {
        return 0;
    }
}