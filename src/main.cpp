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
#include "VertexArrayObj.h"
#include "Matrices/Model.h"
#include "Matrices/View.h"
#include "Matrices/Perspective.h"
#include "globals.h"

void display(GLFWwindow*);
GLFWwindow* windowInit(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
static void windowControls(GLFWwindow* window, int key, int scancode, int action, int mods); 
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void reshape(ShaderHandler& shader);
static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
void keepTime();
Model modelMatrix;
View viewMatrix;
Perspective perspectiveMatrix;
float lastFrame = 0.0f; //records the previous frames value
float deltaTime = 0.0f; //our change in time variable
float lastX = SCREEN_WIDTH/2, lastY = SCREEN_HEIGHT/2; //default mouse position

int main(int argc, char** argv) {
    GLFWwindow* window = windowInit(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (glewInit() != GLEW_OK) {
        std::cout << "Glewinit error";
    }

    //**Put all GL settings here**
    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    //glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    if (window != NULL){
        display(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void display(GLFWwindow* window) {

    //this is currently the object we're displaying
    MeshLoader mesh("mesh/cow.obj", 3);

    //these are our buffers the meshloader loads into to bind our vertices and indices
    VertexArrayObj vao(mesh.getVertexData(), mesh.vertexDataSize(), mesh.getIndexData(), mesh.indexDataSize());

    //constructs the shaderHandler which loads our shader program
    ShaderHandler shaderHandler;
    shaderHandler.useShader();
    //sets color of our object
    shaderHandler.setUni4f("inColor", 0.0f, 1.0f, 0.0f, 1.0f);

   /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        keepTime(); //calculates the length of time the previous frame took for our deltaTime
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        reshape(shaderHandler);
        glDrawElements(GL_TRIANGLES, mesh.indexDataSize(), GL_UNSIGNED_INT, (void*)0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    shaderHandler.~ShaderHandler();
    vao.~VertexArrayObj();
}

GLFWwindow* windowInit(int width, int height) {
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "failstate: glfw failed to initialize";
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Obj Loader", NULL, NULL);

    if (!window){
        std::cout << "failstate: window failed to initialize";
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, windowControls);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}

static void windowControls(GLFWwindow* window, int key, int scancode, int action, int mods){
    float cameraSpeed = 10.0f * deltaTime;
    switch (key){
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_W:
        //move given units (camera speed) in the directing we (the camera) are facing
        viewMatrix.moveForward(cameraSpeed);
        break;
    case GLFW_KEY_A:
        //move given units orthogonal to the direction we're facing
        viewMatrix.moveLeft(cameraSpeed);
        break;
    case GLFW_KEY_S:
        //move given units opposite the direction we're facing
        viewMatrix.moveBackward(cameraSpeed);
        break;
    case GLFW_KEY_D:
        //move given units orthogonal to the direction we're facing
        viewMatrix.moveRight(cameraSpeed);
        break;
    case GLFW_KEY_SPACE:
        //Vertical movement
        viewMatrix.moveUp(cameraSpeed);
        break;
    case GLFW_KEY_LEFT_SHIFT:
        viewMatrix.moveDown(cameraSpeed);
        break;
    case GLFW_KEY_E:
        modelMatrix.rotateObject(2.0f);
        break;
    case GLFW_KEY_Q:
        modelMatrix.rotateObject(-2.0f);
        break;
    case GLFW_KEY_1:
        perspectiveMatrix.changeAngle(-1.0f);
        break;
    case GLFW_KEY_2:
        perspectiveMatrix.changeAngle(1.0f);
        break;
    case GLFW_KEY_3:
        perspectiveMatrix.moveNearPlane(-.1f);
        break;
    case GLFW_KEY_4:
        perspectiveMatrix.moveNearPlane(.1f);
        break;
    case GLFW_KEY_5:
        perspectiveMatrix.moveFarPlane(-.1f);
        break;
    case GLFW_KEY_6:
        perspectiveMatrix.moveFarPlane(.1f);
        break;
    }

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos){
    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    viewMatrix.calcDirections(xOffset, yOffset);
}

void reshape(ShaderHandler& shader) {
    glm::mat4 perspective = perspectiveMatrix.getPerspective(SCREEN_WIDTH / SCREEN_HEIGHT);
    glm::mat4 modelView;
    modelView = viewMatrix.getView() * modelMatrix.getModel();
    //send our new shape structure to our shader for rendering
    shader.setMat4f("perspectiveMatrix", perspective);
    shader.setMat4f("modelViewMatrix", modelView);
}

void keepTime() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}