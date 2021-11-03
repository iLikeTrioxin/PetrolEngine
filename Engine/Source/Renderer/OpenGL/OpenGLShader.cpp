#include <PCH.h>

#include "OpenGLShader.h"

#include "../../Core/Files.h"

//
// INFO
// 1. I use here properties of glShaderXXX(shader) which is stated at khronos site "A value of 0 for shader will be silently ignored."
//

namespace PetrolEngine {

    int OpenGLShader::recompileShader( const char* vertexShaderSourceCode  ,
                                       const char* fragmentShaderSourceCode,
                                       const char* geometryShaderSourceCode ) {
        uint32_t   newVertexShaderID,
                 newFragmentShaderID,
                 newGeometryShaderID;

        if (vertexShaderSourceCode) {
            newVertexShaderID = glCreateShader(GL_VERTEX_SHADER);    

            glShaderSource (newVertexShaderID, 1, &vertexShaderSourceCode, nullptr);
            glCompileShader(newVertexShaderID);

            int error = checkShaderCompileErrors(newVertexShaderID, "VERTEX");

            if (!error) {
                glDetachShader(ID,    vertexShaderID);
                glAttachShader(ID, newVertexShaderID);
            }
        }

        if (fragmentShaderSourceCode) {
            newFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource (newFragmentShaderID, 1, &fragmentShaderSourceCode, nullptr);
            glCompileShader(newFragmentShaderID);

            int error = checkShaderCompileErrors(newFragmentShaderID, "FRAGMENT");

            if (!error) {
                glDetachShader(ID,    fragmentShaderID);
                glAttachShader(ID, newFragmentShaderID);
            }
        }

        if (geometryShaderSourceCode) {
            newGeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

            glShaderSource (newGeometryShaderID, 1, &geometryShaderSourceCode, nullptr);
            glCompileShader(newGeometryShaderID);

            int error = checkShaderCompileErrors(newGeometryShaderID, "GEOMETRY");

            if (!error) {
                glDetachShader(ID,    geometryShaderID);
                glAttachShader(ID, newGeometryShaderID);
            }
        }

        glLinkProgram(ID);

        int error = checkProgramCompileErrors(ID);

        if (!error) {
            // We need to remove only old code before we change old id's to the new ones
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

    OpenGLShader::OpenGLShader( const char* vertexShaderSourceCode  ,
                                const char* fragmentShaderSourceCode,
                                const char* geometryShaderSourceCode ) {
        this->  vertexShaderID = 0;
        this->fragmentShaderID = 0;
        this->geometryShaderID = 0;

        this->ID = glCreateProgram();

        // creating and attaching vertex shader
        {
            this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            
            glShaderSource (vertexShaderID, 1, &vertexShaderSourceCode, nullptr);
            glCompileShader(vertexShaderID);

            checkShaderCompileErrors(vertexShaderID, "VERTEX");

            glAttachShader(ID, vertexShaderID);
        }
        
        // creating and attaching fragment shader
        {
            this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(fragmentShaderID, 1, &fragmentShaderSourceCode, nullptr);
            glCompileShader(fragmentShaderID);

            checkShaderCompileErrors(fragmentShaderID, "FRAGMENT");

            glAttachShader(ID, fragmentShaderID);
        }

        // creating and attaching geometry shader if given
        if (geometryShaderSourceCode != nullptr)
        {
            this->geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

            glShaderSource (geometryShaderID, 1, &geometryShaderSourceCode, nullptr);
            glCompileShader(geometryShaderID);

            checkShaderCompileErrors(geometryShaderID, "GEOMETRY");
            
            glAttachShader(ID, geometryShaderID);
        }

        glLinkProgram(ID);

        checkProgramCompileErrors(ID);
        
        // delete the shaders as they're linked into our program now and no longer necessary
        //glDeleteShader(vertexShaderID);
        //glDeleteShader(fragment);
        //glDeleteShader(geometry);
    }

    

    OpenGLShader::~OpenGLShader() {
        glDeleteShader(vertexShaderID  );
        glDeleteShader(fragmentShaderID);
        glDeleteShader(geometryShaderID);

        glDeleteProgram(this->ID);
    }

    void OpenGLShader::setVec4(const String& uniform, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(ID, uniform.c_str()), x, y, z, w);
    }
    void OpenGLShader::setBool(const String& uniform, bool     x) {
        glUniform1i(glGetUniformLocation(ID, uniform.c_str()), (int)x);
    }
    void OpenGLShader::setInt(const String& uniform, int      x) {
        glUniform1i(glGetUniformLocation(ID, uniform.c_str()), x);
    }
    void OpenGLShader::setUint(const String& uniform, uint      x) {
        glUniform1ui(glGetUniformLocation(ID, uniform.c_str()), x);
    }
    void OpenGLShader::setFloat(const String& uniform, float     x) {
        glUniform1f(glGetUniformLocation(ID, uniform.c_str()), x);
    }
    void OpenGLShader::setVec2(const String& uniform, const glm::vec2& x) {
        glUniform2fv(glGetUniformLocation(ID, uniform.c_str()), 1, &x[0]);
    }
    void OpenGLShader::setVec2(const String& uniform, float x, float    y) {
        glUniform2f(glGetUniformLocation(ID, uniform.c_str()), x, y);
    }
    void OpenGLShader::setVec3(const String& uniform, const glm::vec3& x) {
        glUniform3fv(glGetUniformLocation(ID, uniform.c_str()), 1, &x[0]);
    }
    void OpenGLShader::setVec3(const String& uniform, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(ID, uniform.c_str()), x, y, z);
    }
    void OpenGLShader::setVec4(const String& uniform, const glm::vec4& x) {
        glUniform4fv(glGetUniformLocation(ID, uniform.c_str()), 1, &x[0]);
    }
    void OpenGLShader::setMat2(const String& uniform, const glm::mat2& mat) {
        glUniformMatrix2fv(glGetUniformLocation(ID, uniform.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::setMat3(const String& uniform, const glm::mat3& mat) {
        glUniformMatrix3fv(glGetUniformLocation(ID, uniform.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void OpenGLShader::setMat4(const String& uniform, const glm::mat4& mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, uniform.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    int OpenGLShader::checkProgramCompileErrors(GLuint shader) {
        GLint success;
        GLchar infoLog[1024];

        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (success)
            return 0;

        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

        LOG( std::string("PROGRAM_LINKING_ERROR: ") + infoLog, 2);

        return 1;
    }

    int OpenGLShader::checkShaderCompileErrors(GLuint shader, const String& type) {
        GLint success;
        GLchar infoLog[1024];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success)
            return 0;

        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

        LOG( "ERROR::SHADER_COMPILATION_ERROR(" + type + "): " + infoLog, 2);

        return 1;
    }
}