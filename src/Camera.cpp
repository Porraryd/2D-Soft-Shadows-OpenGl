//
//  Camera.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-28.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height)
{
    
    screenWidth = width;
    screenHeight = height;
    position.x = 0;
    position.y = 0;
    
    //Create uniform buffer:
    glGenBuffers(1, &uboMatrices);
    
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    
    //Put in the Projection matrix.
    glm::mat4 projection = glm::ortho(0.f, screenWidth, screenHeight, 0.f, -1.f, 1.f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    //put in View Matrix
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(getViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0); 
}

glm::mat4 Camera::getViewMatrix(){
    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(screenWidth/2, screenHeight/2, 0.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(screenWidth/2, screenHeight/2, 0.0f));
    view = glm::scale(view, glm::vec3(mZoom,mZoom, 1.0));
    view = glm::translate(view, glm::vec3(-position, 0.0f));
    return view;
}
void Camera::move(glm::vec2 movement)
{
    position += movement;
    updateUniform();
}

void Camera::zoom(float deltaZoom)
{
    mZoom += deltaZoom;
    if(mZoom < 0.1)
        mZoom = 0.1;
    
    updateUniform();
}

void Camera::setZoom(float zoom)
{
    if (zoom > 0.1)
        mZoom = zoom;
    else
        mZoom = 0.1;
}
void Camera::updateUniform(){
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(getViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::use(){
    
   
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
    
    //Put in the Projection matrix.
    glm::mat4 projection = glm::ortho(0.f, screenWidth, screenHeight, 0.f, -1.f, 1.f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    //put in View Matrix
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(getViewMatrix()));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
}