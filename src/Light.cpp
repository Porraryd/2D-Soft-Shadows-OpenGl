//
//  Light.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-09.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#include "Light.h"


Light::Light(glm::vec2 pos, float intensity, glm::vec3 color)
: mPos(pos), mIntensity(intensity), mColor(color)
{
    mRadius = 512;
    //Create uniform buffer:
    glGenBuffers(1, &ubo);
    
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(UBOData), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 1, ubo, 0, sizeof(UBOData));
}

void Light::updateUniform(){
    ubodata.pos = mPos;
    ubodata.radius = mRadius;
    ubodata.intensity = mIntensity;
    ubodata.color = mColor;
    
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(UBOData), &ubodata);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Light::setPosition(glm::vec2 pos){
    mPos = pos;
}