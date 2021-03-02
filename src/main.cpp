#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include "ShaderHandler.h"
#include "MeshLoader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Matrix.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void display(GLFWwindow*);
GLFWwindow* windowInit(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);

int main(int argc, char** argv) {
    GLFWwindow* window = windowInit(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (glewInit() != GLEW_OK) {
        std::cout << "Glewinit error";
    }
    if (window != NULL){
        display(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void display(GLFWwindow* window) {

    //this is currently the object we're displaying
    MeshLoader mesh("mesh/cube.obj", 3);

    //these are our buffers the meshloader loads into to bind our vertices and indices
    VertexBuffer vb(mesh.getVertexBuffer(), mesh.vertexBufferSize());
    IndexBuffer ib(mesh.getIndexBuffer(), mesh.indexBufferSize());

    //defines the attributes of our vertices in the buffer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    ShaderHandler shaderHandler;
    shaderHandler.useShader();
    shaderHandler.setUni4f("inColor", 0.0f, 1.0f, 0.0f, 1.0f);
    
    //modify our view to match our object
    /* Loop until the user closes the window */

   /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, mesh.indexBufferSize(), GL_UNSIGNED_INT, nullptr);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    shaderHandler.~ShaderHandler();
    vb.~VertexBuffer();
    ib.~IndexBuffer();
}

GLFWwindow* windowInit(int width, int height) {
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "failstate: glfw failed to initialize";
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    if (!window){
        std::cout << "failstate: window failed to initialize";
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}

