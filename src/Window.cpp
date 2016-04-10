//
//  Window.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-26.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#include "Window.h"
#include <iostream>
Window::Window(int width, int height, const char* title)
{
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_resize_callback);
    
    glfwMakeContextCurrent(mWindow);
    glClearColor(0.f, 0.f, 0.f, 0.f);

}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
}

GLFWwindow* Window::getWindow()
{
    return mWindow;
}

void Window::setWindowSize(int width, int height)
{
    glfwSetWindowSize(mWindow, width, height);
}


 void Window::error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
void Window::framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "Viewport changed to: " << width <<"x" << height << std::endl;
}