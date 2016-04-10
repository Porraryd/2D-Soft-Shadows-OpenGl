//
//  Game.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-28.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__Game__
#define __KrullGL__Game__

#include <stdio.h>
#include "Window.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include <vector>


const unsigned int NUMBER_OF_KEYS = 1024;

class Game{
    
    const unsigned static int SCREEN_WIDTH = 1280;
    const unsigned static int SCREEN_HEIGHT = 720;
    
public:
    Game(Window* window);
    
    void processInput(float dt);
    
    void update(float dt);
    
    void render();
    
    Camera* mCamera;
    Camera* mLightCamera;
    
    bool keys[NUMBER_OF_KEYS];
    float cursorX, cursorY;
    
private:
    int angleSamples = 2048;
    int lightResolution = 512;
    void initFbos();
    Window* mWindow;
    std::vector<GameObject*> objects;
    GameObject* background;
    
    Light* light;
    ShaderProgram* shader;
    ShaderProgram* postShader;
    ShaderProgram* shadowMapShader;
    
    
    GLuint mFrameBufferObj;
    GLuint mQuadVao;
    GLuint mPostprocessTexture;
    GLuint mSndFBO;
    GLuint mPolarTexture;
};

#endif /* defined(__KrullGL__Game__) */
