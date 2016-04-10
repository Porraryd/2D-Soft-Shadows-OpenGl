//
//  RendererComponent.cpp
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-04.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#include "RendererComponent.h"
bool RendererComponent::vaoInit = false;
GLuint RendererComponent::vao;

RendererComponent::RendererComponent(ShaderProgram* shader, glm::vec3 color)
: mShader(shader), mColor(color)
{
    if(!vaoInit)
        RendererComponent::initBox();
}

void RendererComponent::render(GameObject* obj)
{
    mShader->use();
    mShader->setVector3f("boxColor", mColor);
    
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(obj->mPosition.x, obj->mPosition.y, 0.f));
    transform = glm::translate(transform, glm::vec3(0.5 * obj->mSize.x, 0.5 * obj->mSize.y, 0.0));
    transform = glm::rotate(transform, 0.f, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::translate(transform, -glm::vec3(0.5 * obj->mSize.x, 0.5 * obj->mSize.y, 0.0));
    
    transform = glm::scale(transform, glm::vec3(obj->mSize.x, obj->mSize.y, 1.0f));
    
    mShader->setMatrix4("M", transform);
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    mShader->disable();
}

void RendererComponent::setColor(glm::vec3 col) {
    
    mColor = col;
}

 void RendererComponent::initBox(){
    GLfloat vertex_array_data[] = {
        0, 1, 0, 1,
        1, 0, 1, 0,
        0, 0, 0, 0,
        1, 1, 1, 1
    };
    GLuint index_array_data[] = {
        0, 1, 2,
        0, 3, 1,
        
    };
    
    //vertexarray = vertex_array_data;
    //indexarray = index_array_data;
    
    //numberOfVertices = 4;
    //numberOfTriangles = 2;
     GLuint vertexbuffer;
     GLuint indexbuffer;
     
     glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &indexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array_data), vertex_array_data, GL_STATIC_DRAW);
    
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    
    // Activate the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    // Present our vertex indices to OpenGL
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 3 * 2 * sizeof(GLuint), index_array_data, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     
     vaoInit = true;
    
}