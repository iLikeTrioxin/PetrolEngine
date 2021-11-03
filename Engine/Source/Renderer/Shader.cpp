#include <PCH.h>

#include "Shader.h"
#include "Renderer.h"
#include <cassert>

#include "OpenGL/OpenGLShader.h"
#include "Vulkan/VulkanShader.h"

#include <fstream>
#include "../Core/Files.h"

namespace PetrolEngine {
    static const char* defaultVertexShaderPath   = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.frag";
    static const char* defaultFragmentShaderPath = "C:/Users/mpr19/Desktop/Engine/Engine/Resources/Shaders/shader.vert";

	std::unordered_map<String, Ref<Shader>> Shader::loadedShaders;
	
	auto getSourcesFromString(String fileSource, String keyword = "#type") {
		std::unordered_map<String, String> sources;

		String lcSource; // lower case source because find would detect only lower case "#type"
		
		lcSource.resize(fileSource.length());

		// copy fileSource to lcSource while lowering case and lower keyword directly
		std::transform(fileSource.begin(), fileSource.end(), lcSource.begin(), [](unsigned char c) { return std::tolower(c); });
		std::transform(keyword   .begin(), keyword   .end(), keyword .begin(), [](unsigned char c) { return std::tolower(c); });
		
		for(std::size_t keyPos     = lcSource.find(keyword); keyPos != std::string::npos;) {
			std::size_t nextKeyPos = lcSource.find(keyword,  keyPos + keyword.length());

			std::size_t endOfKeyPos   = keyPos + keyword.length() + 1;
			std::size_t endOfTypeLine = lcSource.find("\r\n", endOfKeyPos);

			std::string type = lcSource.substr(endOfKeyPos, endOfTypeLine - endOfKeyPos);
			
			sources[type]    = fileSource.substr(endOfTypeLine, nextKeyPos - endOfTypeLine);

			keyPos = nextKeyPos;
		}

		return sources;
	}
	Ref<Shader> Shader::load(const String& path) {
		// check if shader with that path wasn't already loaded
		auto isShaderInHash = loadedShaders.find(path);

		if (isShaderInHash != loadedShaders.end())
			return isShaderInHash->second;
		
		// Read file content and get separated sources
		auto sources(getSourcesFromString(ReadFile(path)));
		
		// list of strings with names of valid shader types
		std::string shaders[3] = {"vertex", "fragment", "geometry"};
		
		// iterate thought every shader and replace shader name
		// with source code if defined or empty string if not
		for(auto& shader : shaders){
			auto source = sources.find(shader);
			
			shader = (source == sources.end()) ? "" : std::move(source->second);
		}

		// create shader from corresponding sources and store it
		auto shader = Shader::create(std::move(shaders[0]),
									 std::move(shaders[1]),
									 std::move(shaders[2]) );

		shader->name = path;

		// add shader to unordered map to not clone it in future
		loadedShaders[path] = shader;

		return shader;
	}

	Ref<Shader> Shader::load( String&& name       ,
                              String&& vertexSrc  ,
                              String&& fragmentSrc,
                              String&& geometrySrc  ) {
		LOG_FUNCTION();

		// find shader with that name
		auto isShaderInHash = loadedShaders.find(name);

		// if such a shader exists return it and continue if not
		if (isShaderInHash != loadedShaders.end())
			return isShaderInHash->second;
		
		// create shader with corresponding sources
		auto shader = Shader::create(std::move( vertexSrc ),
									 std::move(fragmentSrc),
								     std::move(geometrySrc) );
		
		shader->name = name;

		// add it to unordered map to prevent copying
		loadedShaders[name] = shader;
		
		return shader;
	}

	Ref<Shader> Shader::create(String&& vertexSrc, String&& fragmentSrc, String&& geometrySrc){ LOG_FUNCTION();
		switch (RendererAPI::get())
		{
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>( vertexSrc .c_str(), fragmentSrc.c_str(), nullptr );
            case RendererAPI::API::Vulkan: return CreateRef<VulkanShader>( vertexSrc .c_str(), fragmentSrc.c_str(), nullptr );
			default: return nullptr;
		}
	}
}