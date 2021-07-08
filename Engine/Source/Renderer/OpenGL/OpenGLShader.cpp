#include "../../PCH.h"

#include "OpenGLShader.h"

#include "../Shader.h"
#include "../../Core/Files.h"
#include <fstream>

namespace Engine {
    OpenGLShader::OpenGLShader(std::string&& vShaderCode, std::string&& fShaderCode, std::string&& gShaderCode) {
        if (vShaderCode.empty())
            vShaderCode = ReadFile(defaultVertexShaderPath);
        if (fShaderCode.empty())
            fShaderCode = ReadFile(defaultFragmentShaderPath);

        int a = glCreateProgram();
        this->ID = a;

        // ID's of program shaders
        unsigned int vertex, fragment, geometry;

        // creating and attaching vertex shader
        {
            vertex = glCreateShader(GL_VERTEX_SHADER);

            const char* vertexShaderSourceCode = vShaderCode.c_str();
            
            debug_log("VVV");
            debug_log(vertexShaderSourceCode);
            debug_log("VVV");

            glShaderSource(vertex, 1, &vertexShaderSourceCode, NULL);
            glCompileShader(vertex);

            checkCompileErrors(vertex, "VERTEX");

            glAttachShader(ID, vertex);
        }
        
        // creating and attaching fragment shader
        {
            fragment = glCreateShader(GL_FRAGMENT_SHADER);

            const char* fragmentShaderSourceCode = fShaderCode.c_str();
            
            debug_log("FFF");
            debug_log(fragmentShaderSourceCode);
            debug_log("FFF");

            glShaderSource(fragment, 1, &fragmentShaderSourceCode, NULL);
            glCompileShader(fragment);

            checkCompileErrors(fragment, "FRAGMENT");

            glAttachShader(ID, fragment);
        }

        // creating and attaching geometry shader if given
        if (!gShaderCode.empty())
        {
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            
            const char* geometryShaderSourceCode = fShaderCode.c_str();

            debug_log("GGG");
            debug_log(geometryShaderSourceCode);
            debug_log("GGG");

            glShaderSource (geometry, 1, &geometryShaderSourceCode, NULL);
            glCompileShader(geometry);
            
            checkCompileErrors(geometry, "GEOMETRY");
            
            glAttachShader(ID, geometry);
        }

        glLinkProgram(ID);

        checkCompileErrors(ID, "PROGRAM");
        
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if (!gShaderCode.empty())
            glDeleteShader(geometry);
    }

    void OpenGLShader::setVec4(const std::string& name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void OpenGLShader::setBool(const std::string& name, bool     value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void OpenGLShader::setInt(const std::string& name, int      value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void OpenGLShader::setFloat(const std::string& name, float     value) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::setVec2(const std::string& name, float x, float    y) {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::setVec3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void OpenGLShader::setMat2(const std::string& name, const glm::mat2& mat)
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::setMat3(const std::string& name, const glm::mat3& mat)
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}