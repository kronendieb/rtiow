#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using Window = GLFWwindow*;
namespace rtiow{
    extern Window defaultWindow;
    extern std::vector<void(*)()> actions;
    enum State {stateReady, stateRunning, stateExit};

    Window initWindow(int* width, int* height, char* name);

    bool runWindow( Window window);

    void closeWindow();

    void addAction(void(* function)());

    void doAction(int index);
    void doActions();
}
#endif