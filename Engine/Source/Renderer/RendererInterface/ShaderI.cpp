#include <PCH.h>

#include "Shader.h"
#include <cassert>

#include <fstream>
#include "Core/Files.h"

#include <shaderc/shaderc.hpp>
#include <spirv_cross.hpp>

namespace PetrolEngine {

    shaderc_shader_kind shaderTypeToShadercShaderKind(ShaderType type) {
        switch (type) {
            case ShaderType::Vertex:   return shaderc_glsl_vertex_shader;
            case ShaderType::Fragment: return shaderc_glsl_fragment_shader;
            case ShaderType::Geometry: return shaderc_glsl_geometry_shader;
        }
    }

    Vector<uint32> compileShader(const String& name, const String& shaderSource, ShaderType type) {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;

//        options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
        //options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
        options.SetOptimizationLevel(shaderc_optimization_level_zero);
        //options.SetHlslIoMapping(true);
        //options.SetAutoMapLocations(true);

        //options.SetHlslOffsets(true);
        //options.SetHlslRegisterSetAndBinding(true);
        //options.SetHlslFunctionality1(true);

        auto result = compiler.CompileGlslToSpv(
                shaderSource,
                shaderTypeToShadercShaderKind(type),
                name.c_str(),
                options
        );

        if(!result.GetCompilationStatus())
            return Vector<uint32>(result.cbegin(), result.cend());

        LOG("Shader compilation failed: " + result.GetErrorMessage(), 3);
        return {};
    }

    void Shader::compile() {
        this->vertexByteCode   = compileShader(this->name, this->vertexShaderSourceCode  , ShaderType::Vertex  );
        this->fragmentByteCode = compileShader(this->name, this->fragmentShaderSourceCode, ShaderType::Fragment);

        if(!this->geometryShaderSourceCode.empty())
            this->geometryByteCode = compileShader(this->name, this->geometryShaderSourceCode, ShaderType::Geometry);

        compileFromSpv(
            vertexByteCode  .empty() ? nullptr : &vertexByteCode  ,
            fragmentByteCode.empty() ? nullptr : &fragmentByteCode,
            geometryByteCode.empty() ? nullptr : &geometryByteCode
        );

        this->metadata = {};

        this->reflect(this->vertexByteCode  , ShaderType::Vertex);
        this->reflect(this->fragmentByteCode, ShaderType::Vertex);

        if(!this->geometryShaderSourceCode.empty())
            this->reflect(this->geometryByteCode, ShaderType::Geometry);
    }

    void Shader::reflect(const Vector<uint32>& spv, ShaderType type) {
        spirv_cross::Compiler compiler(spv);
        spirv_cross::ShaderResources resources = compiler.get_shader_resources();

        LOG("Reflect - " + this->name, 3);
        LOG("uniform buffers - " + toString(resources.uniform_buffers.size()), 3);
        LOG("resources - "       + toString(resources.sampled_images .size()), 3);

        for(const auto& resource : resources.sampled_images){
            uint32 binding = compiler.get_decoration(resource.id, spv::DecorationBinding);

            this->metadata.textures.push_back(binding);
        }

        LOG("Uniform buffers:", 3);
        for (const auto& resource : resources.uniform_buffers) {
            const auto& bufferType = compiler.get_type(resource.base_type_id);
            uint32_t bufferSize    = compiler.get_declared_struct_size(bufferType);
            uint32_t binding       = compiler.get_decoration(resource.id, spv::DecorationBinding);

            int memberCount = bufferType.member_types.size();

            this->metadata.uniforms[resource.name] = binding;

            LOG(resource.name     + ":", 3);
            LOG("  * Size = {0}"    + toString(bufferSize ), 3);
            LOG("  * Binding = {0}" + toString(binding    ), 3);
            LOG("  * Members = {0}" + toString(memberCount), 3);
        }
    }
}