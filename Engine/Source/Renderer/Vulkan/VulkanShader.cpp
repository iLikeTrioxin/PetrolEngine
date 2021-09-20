#include <PCH.h>

#include "VulkanShader.h"

#include "../Shader.h"
#include "../../Core/Files.h"
#include <fstream>

//
// INFO
// 1. I use here propertie of glShaderXXX(shader) which is stated at khronos site "A value of 0 for shader will be silently ignored."
//

namespace PetrolEngine {

    int VulkanShader::recompileShader( const char* vertexShaderSourceCode  ,
                                       const char* fragmentShaderSourceCode,
                                       const char* geometryShaderSourceCode ) {
        debug_log("started");
        uint32_t   newVertexShaderID = 0,
                 newFragmentShaderID = 0,
                 newGeometryShaderID = 0;

        if (vertexShaderSourceCode) {
            newVertexShaderID = glCreateShader(GL_VERTEX_SHADER);    

            glShaderSource (vertexShaderID, 1, &vertexShaderSourceCode, NULL);
            glCompileShader(vertexShaderID);

            int error = checkShaderCompileErrors(vertexShaderID, "VERTEX");

            if (!error) {
                glDetachShader(ID,    vertexShaderID);
                glAttachShader(ID, newVertexShaderID);
            }
        }

        if (fragmentShaderSourceCode) {
            newFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(fragmentShaderID, 1, &fragmentShaderSourceCode, NULL);
            glCompileShader(fragmentShaderID);

            int error = checkShaderCompileErrors(fragmentShaderID, "FRAGMENT");

            if (!error) {
                glDetachShader(ID,    fragmentShaderID);
                glAttachShader(ID, newFragmentShaderID);
            }
        }

        if (geometryShaderSourceCode) {
            newGeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

            glShaderSource(geometryShaderID, 1, &geometryShaderSourceCode, NULL);
            glCompileShader(geometryShaderID);

            int error = checkShaderCompileErrors(geometryShaderID, "GEOMETRY");

            if (!error) {
                glDetachShader(ID,    geometryShaderID);
                glAttachShader(ID, newGeometryShaderID);
            }
        }

        glLinkProgram(ID);

        int error = checkProgramCompileErrors(ID);

        if (!error) {
            // We need to remove only old code before we change old id's to new
            if (  vertexShaderSourceCode) { glDeleteShader(  vertexShaderID);   vertexShaderID =   newVertexShaderID; }
            if (fragmentShaderSourceCode) { glDeleteShader(fragmentShaderID); fragmentShaderID = newFragmentShaderID; }
            if (geometryShaderSourceCode) { glDeleteShader(geometryShaderID); geometryShaderID = newGeometryShaderID; }
            
            return 0;
        }
        
        // reverse all changes
        if (  vertexShaderSourceCode) { glDetachShader(ID,   newVertexShaderID); glAttachShader(ID,   vertexShaderID); glDeleteShader(  vertexShaderID); }
        if (fragmentShaderSourceCode) { glDetachShader(ID, newFragmentShaderID); glAttachShader(ID, fragmentShaderID); glDeleteShader(fragmentShaderID); }
        if (geometryShaderSourceCode) { glDetachShader(ID, newGeometryShaderID); glAttachShader(ID, geometryShaderID); glDeleteShader(geometryShaderID); }
        
        glLinkProgram(ID);
        return 1;
    }

    VulkanShader::VulkanShader( const char* vertexShaderSourceCode  ,
                                const char* fragmentShaderSourceCode,
                                const char* geometryShaderSourceCode ) {
        this->  vertexShaderID = 0;
        this->fragmentShaderID = 0;
        this->geometryShaderID = 0;

        this->ID = glCreateProgram();

        // creating and attaching vertex shader
        {
            this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            
            glShaderSource (vertexShaderID, 1, &vertexShaderSourceCode, NULL);
            glCompileShader(vertexShaderID);

            debug_log("VERTEX\n" << vertexShaderSourceCode << "\nVERTEX");

            checkShaderCompileErrors(vertexShaderID, "VERTEX");

            glAttachShader(ID, vertexShaderID);
        }
        
        // creating and attaching fragment shader
        {
            this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(fragmentShaderID, 1, &fragmentShaderSourceCode, NULL);
            glCompileShader(fragmentShaderID);

            debug_log("FRAGMENT\n" << fragmentShaderSourceCode << "\nFRAGMENT");

            checkShaderCompileErrors(fragmentShaderID, "FRAGMENT");

            glAttachShader(ID, fragmentShaderID);
        }

        // creating and attaching geometry shader if given
        if (geometryShaderSourceCode != nullptr)
        {
            this->geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

            glShaderSource (geometryShaderID, 1, &geometryShaderSourceCode, NULL);
            glCompileShader(geometryShaderID);
            
            debug_log("GEOMETRY\n" << geometryShaderSourceCode << "\nGEOMETRY");

            checkShaderCompileErrors(geometryShaderID, "GEOMETRY");
            
            glAttachShader(ID, geometryShaderID);
        }

        glLinkProgram(ID);

        checkProgramCompileErrors(ID);
        
        // delete the shaders as they're linked into our program now and no longer necessery
        //glDeleteShader(vertexShaderID);
        //glDeleteShader(fragment);
        //glDeleteShader(geometry);
    }

    

    VulkanShader::~VulkanShader() {
        glDeleteShader(vertexShaderID  );
        glDeleteShader(fragmentShaderID);
        glDeleteShader(geometryShaderID);

        glDeleteProgram(this->ID);
    }

    void VulkanShader::setVec4(const std::string& name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    void VulkanShader::setBool(const std::string& name, bool     value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void VulkanShader::setInt(const std::string& name, int      value) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void VulkanShader::setFloat(const std::string& name, float     value) {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void VulkanShader::setVec2(const std::string& name, const glm::vec2& value) {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void VulkanShader::setVec2(const std::string& name, float x, float    y) {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void VulkanShader::setVec3(const std::string& name, const glm::vec3& value) {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void VulkanShader::setVec3(const std::string& name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void VulkanShader::setVec4(const std::string& name, const glm::vec4& value) {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void VulkanShader::setMat2(const std::string& name, const glm::mat2& mat) {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void VulkanShader::setMat3(const std::string& name, const glm::mat3& mat) {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void VulkanShader::setMat4(const std::string& name, const glm::mat4& mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    int VulkanShader::checkProgramCompileErrors(GLuint shader) {
        GLint success;
        GLchar infoLog[1024];

        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (success)
            return 0;

        glGetProgramInfoLog(shader, 1024, NULL, infoLog);

        debug_log( "ERROR::PROGRAM_LINKING_ERROR: " << infoLog );

        return 1;
    }

    int VulkanShader::checkShaderCompileErrors(GLuint shader, std::string type) {
        GLint success;
        GLchar infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success)
            return 0;

        glGetShaderInfoLog(shader, 1024, NULL, infoLog);

        debug_log( "ERROR::SHADER_COMPILATION_ERROR(" << type << "): " << infoLog );

        return 1;
    }
}