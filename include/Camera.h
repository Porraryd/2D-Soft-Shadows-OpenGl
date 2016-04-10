//
//  Camera.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-07-28.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__Camera__
#define __KrullGL__Camera__

#include <stdio.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera(int width, int height);
    
    void move(glm::vec2 movement);
    void zoom(float deltaZoom);
    
    void use();
    void setZoom(float zoom);
    glm::mat4 getViewMatrix();
    inline glm::vec2 getPosition() {return position;}
    inline void setPosition(glm::vec2 pos) { position = pos; updateUniform(); }
    
private:
    
    glm::vec2 position;
    float screenWidth, screenHeight;
    float mZoom = 1.0f;
    GLuint uboMatrices;
    void updateUniform();
    
};

#endif /* defined(__KrullGL__Camera__) */
