#include "ShaderHandler.h"

    ShaderHandler::ShaderHandler() {
        vertexShader = parseShader("res/shaders/VertexShader.txt");
        fragmentShader = parseShader("res/shaders/FragmentShader.txt");
        program = createShader();
    }

    ShaderHandler::~ShaderHandler() {
        //delete program when the shader goes out of scope/dies
        glDeleteProgram(program);
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
        //returns the integer id of our shader program
        return program;
    }

    void ShaderHandler::useShader() {
        //tells opengl to use our shader
        glUseProgram(program);
    }

    void ShaderHandler::setBool(const std::string& name, bool value) const{
        //utility function for redefining boolean uniforms in our shader
        glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
    }

    void ShaderHandler::setInt(const std::string& name, int value) const{
        //utility function for redefining integer uniforms in our shader
        glUniform1i(glGetUniformLocation(program, name.c_str()), value);
    }

    void ShaderHandler::setUni4f(const std::string& name, float v1, float v2, float v3, float v4) const{
        //utility function for redefining float uniforms in our shader
        glUniform4f(glGetUniformLocation(program, name.c_str()), v1, v2, v3, v4);
    }
    
    void ShaderHandler::setMatrix(const std::string& name, Matrix matrix) {
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, matrix.getMatrix());
    }

    void ShaderHandler::setMatrix(const std::string& name, float* matrix){
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, matrix);
    }
