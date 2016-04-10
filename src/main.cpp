
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.hpp"
#include "Window.h"
#include "Camera.h"
#include "Game.h"

Camera* mainCamera;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    Game * game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game->keys[key] = true;
        else if (action == GLFW_RELEASE)
            game->keys[key] = false;
    }
}

static void cursor_callback(GLFWwindow *window, double x , double y )
{
    Game * game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    
    game->cursorX = x;
    game->cursorY = y;
}

int main(void)
{
    
    Window* window = new Window(256, 256, "Krull");
    
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    
    glfwSwapInterval(1);
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwSetCursorPosCallback(window->getWindow(), cursor_callback);
    
    Game* game = new Game(window);
    
    glfwSetWindowUserPointer(window->getWindow(), game);
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;
    
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        game->processInput(deltaTime);
        game->update(deltaTime);
        
        glClear(GL_COLOR_BUFFER_BIT);
        game->render();
        
        
        glfwSwapBuffers(window->getWindow());
        
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
