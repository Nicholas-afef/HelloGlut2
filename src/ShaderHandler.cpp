#include "ShaderHandler.h"

    ShaderHandler::ShaderHandler() {
        vertexShader = parseShader("res/shaders/VertexShader.txt");
        fragmentShader = parseShader("res/shaders/FragmentShader.txt");
        program = createShader();
    }

    std::string ShaderHandler::parseShader(const std::string& filepath) {
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
            char* message = (char*)alloca(length * sizeof(char));
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
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    unsigned int ShaderHandler::getProgram() {
        return program;
    }
