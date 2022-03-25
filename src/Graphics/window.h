#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>

namespace rtiow{

    using Window = GLFWwindow*;
    struct RenderAction{
        void (*m_function)();
        GLuint m_shaderProgram;
        GLuint m_vertexArrayObject;
        GLuint m_texture;
    };

    extern Window defaultWindow;
    extern std::vector<RenderAction> actions;
    enum State {stateReady, stateRunning, stateExit};

    Window initWindow(int* width, int* height, char* name);

    bool runWindow( Window window);

    void closeWindow();

    void framebuffer_size_callback(Window window, int width, int height);

    void addAction(RenderAction action);

    void doAction(int index);
    void doActions();
}
#endif