#include <iostream>

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "adder.h"

int glfwInitialize();

int main(){
    glm::vec3 vectorino = glm::vec3();
    float a = 92.23f;
    float b = 72.45f;
    printf("%f\n", add(a, b));
    printf("%f, %f, %f\n", vectorino.x, vectorino.y, vectorino.z);

    return glfwInitialize();
}

int glfwInitialize(){
    float aspect_ratio = 16/9;
    int width = 640, height = int(float(width) / aspect_ratio);

    GLFWwindow* window;
    if(!glfwInit())
        return -1;


    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }


    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}