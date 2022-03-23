#include "window.h"
#include "../app.h"


namespace rtiow{

Window defaultWindow = NULL;
std::vector<RenderAction> actions;

Window initWindow(int* width, int* height, char* name){
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

bool runWindow(Window window){

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

void closeWindow(){
    glfwTerminate();
}

void framebuffer_size_callback(Window window, int width, int height){
    glViewport(0, 0, width, height);
}

void addAction(RenderAction action){
    actions.push_back(action);
}

void doAction(int index){
    glUseProgram(actions[index].m_shaderProgram);
    glBindVertexArray(actions[index].m_vertexArrayObject);
    actions[index].m_function();
    glBindVertexArray(0);
}

void doActions(){
    for(RenderAction action : actions){
        glUseProgram(action.m_shaderProgram);
        glBindVertexArray(action.m_vertexArrayObject);
        action.m_function();
        glBindVertexArray(0);
    }
}

}