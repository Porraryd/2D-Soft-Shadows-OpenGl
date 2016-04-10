//
//  GameObject.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-03.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//


#include "GameObject.h"

GameObject::GameObject()
: mPosition(glm::vec2(0,0)), mSize(glm::vec2(50,50))
{
    
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size)
: mPosition(pos), mSize(size)
{
    
}

void GameObject::addRendererComponent(ShaderProgram *program, glm::vec3 color)
{
    mRendererComponent = new RendererComponent(program, color);
}

void GameObject::update(float dt)
{
    
}

void GameObject::render()
{
    if (mRendererComponent != nullptr)
        mRendererComponent->render(this);
}