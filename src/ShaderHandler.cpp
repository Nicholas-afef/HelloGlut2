#include "ShaderHandler.h"

    ShaderHandler::ShaderHandler(std::string vertex, std::string frag) {
        vertexShader = parseShader(vertex);
        fragmentShader = parseShader(frag);
        shaderProgram = createShader();
        translator = glm::mat4(1.0f);
        rotator = glm::mat4(1.0f);
        scalar = glm::mat4(1.0f);
    }

    ShaderHandler::~ShaderHandler() {
        //delete program when the shader goes out of scope/dies
        glDeleteProgram(shaderProgram);
    }

    std::string ShaderHandler::parseShader(const std::string& filepath) {
        //reads a shader in from its respective text file and returns it as a string
        std::ifstream stream(filepath);
        std::stringstream ss;

        std::string line;
        while (getline(stream, line)) {
            ss << line << '\n';
        }
        return ss.str();
    }

    unsigned int ShaderHandler::compileShader(unsigned int type, const std::string& source) {
        //this function will compile our shaders. Source code is a string.
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        //error handling to ensure shaders are properly compiled.
        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)malloc(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Shader Compilation Error!" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }
        std::cout << "successfully compiled shader type: " << type << "\n";
        return id;
    }

    unsigned int ShaderHandler::createShader() {
        unsigned int shaderProgram = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(shaderProgram, vs);
        glAttachShader(shaderProgram, fs);
        glLinkProgram(shaderProgram);
        glValidateProgram(shaderProgram);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return shaderProgram;
    }

    unsigned int ShaderHandler::getProgram() {
        //returns the integer id of our shader program
        return shaderProgram;
    }

    void ShaderHandler::useShader() {
        //tells opengl to use our shader
        glUseProgram(shaderProgram);
    }

    void ShaderHandler::setBool(const std::string& name, bool value) const{
        //utility function for redefining boolean uniforms in our shader
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }

    void ShaderHandler::setUni1i(const std::string& name, int value) const{
        //utility function for redefining integer uniforms in our shader
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void ShaderHandler::setUni1f(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void ShaderHandler::setUni3f(const std::string& name, float v1, float v2, float v3) const {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3);
    }

    void ShaderHandler::setUni4f(const std::string& name, float v1, float v2, float v3, float v4) const{
        //utility function for redefining float uniforms in our shader
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
    }
    
    void ShaderHandler::setUni3f(const std::string& name, glm::vec3 vector) const {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), vector.x, vector.y, vector.z);
    }

    void ShaderHandler::setMat4f(const std::string& name, glm::mat4 matrix) {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }