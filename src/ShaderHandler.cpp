#include "ShaderHandler.h"

    ShaderHandler::ShaderHandler() {
        vertexShader = parseShader("res/shaders/VertexShader.txt");
        fragmentShader = parseShader("res/shaders/FragmentShader.txt");
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

    void ShaderHandler::setInt(const std::string& name, int value) const{
        //utility function for redefining integer uniforms in our shader
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void ShaderHandler::setUni4f(const std::string& name, float v1, float v2, float v3, float v4) const{
        //utility function for redefining float uniforms in our shader
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v1, v2, v3, v4);
    }
    
    void ShaderHandler::setTranslate(glm::vec3 tVec) {
        translator = glm::mat4(1.0f);
        translator = glm::translate(translator, tVec);
    }

    void ShaderHandler::setScale(float s) {
        scalar = glm::mat4(1.0f);
        scalar = glm::scale(scalar, glm::vec3(s));
    }
    void ShaderHandler::setRotate(float angle, glm::vec3 axisOfRotation) {
        //assume the rotation needs to be reset on an update
        rotator = glm::mat4(1.0f);
        axisOfRotation = glm::normalize(axisOfRotation);
        rotator = glm::rotate(rotator, glm::radians(angle), axisOfRotation);
    }

    void ShaderHandler::updateModelView() {
        //calculates our modelView Matrix from our transformations and passes it to the shader
        glm::mat4 modelView = view * translator * rotator * scalar;
        GLint uniTrans = glGetUniformLocation(shaderProgram, "modelViewMatrix");
        glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(modelView));
    }

    void ShaderHandler::setView(glm::vec3 position, glm::vec3 nVec, glm::vec3 upVec) {
        //sets the view matrix for our modelview
        view = glm::lookAt(position, nVec, upVec);
    }

    void ShaderHandler::setPerspective(float angle, float screenWidth, float screenHeight, float near,float far) {
        //sets the projection matrix in our shader based on given parameters
        float aspectRatio = screenWidth / screenHeight;
        glm::mat4 proj = glm::perspective(glm::radians(angle), aspectRatio, 1.0f, 10.0f);
        GLint uniProj = glGetUniformLocation(shaderProgram, "projectionMatrix");
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    }

