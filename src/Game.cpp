//
//  Game.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-28.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#include "Game.h"


Game::Game(Window* window)
{
    mWindow = window;
    window->setWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    for (int i=0; i<NUMBER_OF_KEYS; i++)
        keys[i] = false;
    
    //Shader Init
    shader = new ShaderProgram();
    shader->initFromFiles("shaders/simple.vert", "shaders/simple.frag");
    shader->addAttribute("vertexPos");
    shader->addUniform("boxColor");
    shader->addUniform("M");
    shader->addUniform("pass");
    shader->setUniformBlock("Matrices", 0);
    shader->setUniformBlock("Light", 1);
    
    postShader = new ShaderProgram();
    postShader->initFromFiles("shaders/postprocess.vert", "shaders/postprocess.frag");
    
    shadowMapShader = new ShaderProgram();
    shadowMapShader->initFromFiles("shaders/shadowMap.vert", "shaders/shadowMap.frag");
    
    //Some test sprites.
    for (int i=0; i<100; i++)
    {
        GameObject* box = new GameObject(glm::vec2(((i*100)%1000 - 500), ((i/10)*100 - 500)), glm::vec2(50,50));
        box->addRendererComponent(shader, glm::vec3(1,0,0));
        objects.push_back(box);
    }
    /*
    GameObject* box = new GameObject(glm::vec2(0,0), glm::vec2(150,150));
    box->addRendererComponent(shader, glm::vec3(0,1,0));
    objects.push_back(box);
     */
    background = new GameObject(glm::vec2(-1000,-1000), glm::vec2(2000,2000));
    background->addRendererComponent(shader, glm::vec3(0.2,0.2,0.2));
    
    light = new Light(glm::vec2(-50,-50), 10);
    
    //Camera
    mCamera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
    mLightCamera = new Camera(light->getRadius(),light->getRadius());
    mLightCamera->setPosition(light->getPosition());
    mLightCamera->setZoom(0.5);
    mCamera->use();
    initFbos();
}

void Game::processInput(float dt){
    if (keys[GLFW_KEY_D])
        mCamera->move(glm::vec2(1.0f, 0.0f));
    if (keys[GLFW_KEY_A])
        mCamera->move(glm::vec2(-1.0f, 0.0f));
    if (keys[GLFW_KEY_W])
        mCamera->move(glm::vec2(0.0f, -1.0f));
    if (keys[GLFW_KEY_S])
        mCamera->move(glm::vec2(0.0f, 1.0f));
    if (keys[GLFW_KEY_Q])
        mCamera->zoom(-0.01f);
    if (keys[GLFW_KEY_E])
        mCamera->zoom(0.01f);
    
}

void Game::update(float dt)
{
    glm::vec4 toWorldCoords=
    glm::inverse(mCamera->getViewMatrix())*glm::vec4(cursorX,cursorY, 1,1);
    light->setPosition(glm::vec2(toWorldCoords.x,toWorldCoords.y));
    light->updateUniform();
}

void Game::render()
{
    bool dual_pass = true;
    if (dual_pass){
        // First pass - render occlusionmaps
        mLightCamera->use();
        mLightCamera->setPosition(light->getPosition());
        int width, height;
        glfwGetFramebufferSize(mWindow->getWindow(), &width, &height);
        
        int lightRadius = light->getRadius();
        glViewport(0,0,lightRadius,lightRadius);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferObj);
        glClearColor(0.0f, 0.1f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader->use();
        shader->setInt("pass",1);
        for (GameObject* o : objects)
        {
            o->render();
        }
        shader->disable();
        // Render shadowmaps
        
        glViewport(0,0,lightRadius*2,1);
        glBindFramebuffer(GL_FRAMEBUFFER, mSndFBO); // back to default
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shadowMapShader->use();
        glBindVertexArray(mQuadVao);
        glBindTexture(GL_TEXTURE_2D, mPostprocessTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        shadowMapShader->disable();
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mCamera->use();
        glViewport(0, 0, width, height);
        
        //Todo - render actual scene
        glBindTexture(GL_TEXTURE_2D, mPolarTexture);
        
        shader->use();
        shader->setInt("pass",2);
        background->render();
        for (GameObject* o : objects)
        {
            o->render();
        }
        shader->disable();
        //Render quad over screen:
        /*
        postShader->use();
        glBindVertexArray(mQuadVao);
        glBindTexture(GL_TEXTURE_2D, mPolarTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        postShader->disable();*/
        
    }
    else{
        background->render();
        for (GameObject* o : objects)
        {
            o->render();
        }
         //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    //glClear(GL_COLOR_BUFFER_BIT);
    
}

void Game::initFbos(){
    
    //First FBO 
    glGenFramebuffers(1, &mFrameBufferObj);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferObj);

    glGenTextures(1, &mPostprocessTexture);
    glBindTexture(GL_TEXTURE_2D, mPostprocessTexture);
    
     int lightRadius = light->getRadius();
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2*SCREEN_WIDTH, 2*SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lightRadius, lightRadius, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPostprocessTexture, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //Second FBO
    glGenFramebuffers(1, &mSndFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mSndFBO);
    
    glGenTextures(1, &mPolarTexture);
    glBindTexture(GL_TEXTURE_2D, mPolarTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2*lightRadius, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPolarTexture, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

    //init postquad for final image
    GLfloat vertex_array_data[] = {
        -1, 1, 0, 1,
        1, -1, 1, 0,
        -1, -1, 0, 0,
        1, 1, 1, 1
    };
    GLuint index_array_data[] = {
        0, 1, 2,
        0, 3, 1,
        
    };
    
    GLuint vertexbuffer;
    GLuint indexbuffer;
    
    glGenVertexArrays(1, &mQuadVao);
    glBindVertexArray(mQuadVao);
    
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &indexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array_data), vertex_array_data, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*2));
    
    // Activate the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    // Present our vertex indices to OpenGL
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 3 * 2 * sizeof(GLuint), index_array_data, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}