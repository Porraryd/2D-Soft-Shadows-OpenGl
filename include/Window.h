//
//  Window.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-26.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__Window__
#define __KrullGL__Window__


#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window{

public:
    Window(int width, int height, const char* title);
    
    ~Window();
    
    GLFWwindow* getWindow();
    
    void setWindowSize(int width, int height);
    
private:
    GLFWwindow* mWindow;
    
    static void error_callback(int error, const char* description);
    static void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
    
};

#endif /* defined(__KrullGL__Window__) */
