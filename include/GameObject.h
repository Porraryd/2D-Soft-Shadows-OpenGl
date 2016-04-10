//
//  GameObject.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-03.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__GameObject__
#define __KrullGL__GameObject__

#include <stdio.h>
#include <glm/glm.hpp>

#include "RendererComponent.h"

class RendererComponent;

class GameObject {
public:
    
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size);
    
    void addRendererComponent(ShaderProgram* program, glm::vec3 color);
    void update(float dt);

    void addTexture(GLuint textureID);
    
    void render();

    glm::vec2 mVelocity;
    glm::vec2 mSize;
    glm::vec2 mPosition;
    
    inline glm::vec2 getPosition() { return mPosition; }
    inline glm::vec2 getVelocity() { return mPosition; }

private:
    
    RendererComponent* mRendererComponent;
    
    
};

#endif /* defined(__KrullGL__GameObject__) */
