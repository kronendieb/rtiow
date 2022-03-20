#include "window.h"
#include "../app.h"

Window rtiow::defaultWindow;
std::vector<void(*)()> rtiow::actions;

Window rtiow::initWindow(int* width, int* height, char* name){
    Window window;

    if(!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(*width, *height, name, NULL, NULL);
    if(!window){
        glfwTerminate();
        return nullptr;
    }


    glfwGetFramebufferSize(window, width, height);
    glViewport(0, 0, *width, *height);

    return window;
}

bool rtiow::runWindow(Window window){

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        doActions();

        glfwPollEvents();
    }
    return true;
}

void rtiow::terminateWindow(){
    glfwTerminate();
}

void rtiow::addAction(void(* function)()){
    actions.push_back(function);
}

void rtiow::doAction(int index){
    actions.at(index)();
}

void rtiow::doActions(){
    for(auto& action : actions)
        action();
}