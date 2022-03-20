#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <vector>

using Window = GLFWwindow*;
namespace rtiow{
    extern Window defaultWindow;
    extern std::vector<void(*)()> actions;

    Window initWindow(int* width, int* height, char* name);

    bool runWindow( Window window);

    void terminateWindow();

    void addAction(void(* function)());

    void doAction(int index);
    void doActions();
}
#endif