#include "window.h"
#include "../app.h"

Window rtiow::defaultWindow = NULL;
std::vector<void(*)()> rtiow::actions;

Window rtiow::initWindow(int* width, int* height, char* name){
    Window window;

    if(!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(*width, *height, name, NULL, NULL);
    if(!window){
        glfwTerminate();
        return nullptr;
    }

    glfwGetFramebufferSize(window, width, height);
    glViewport(0, 0, *width, *height); 
    
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK){
        glfwTerminate();
        return nullptr;
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    printf("Renderer: %s\nVersion supported: %s\n", renderer, version);

    return window;
}

bool rtiow::runWindow(Window window){

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        doActions();
    }
    return true;
}

void rtiow::closeWindow(){
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