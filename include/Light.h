//
//  Light.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-09.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__Light__
#define __KrullGL__Light__

#include <stdio.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
class Light
{
public:
    
    struct UBOData{
        glm::vec2 pos;
        float radius;
        float intensity;
        glm::vec3 color;
    };
    
    Light(glm::vec2 pos, float intensity, glm::vec3 color = glm::vec3(1,1,1));
    
    void updateUniform();
    
    void setPosition(glm::vec2 pos);
    inline glm::vec2 getPosition() { return mPos; }
    inline float getRadius(){return mRadius;}
    GLuint renderOcclusionMap();
    
private:
    glm::vec2 mPos;
    glm::vec3 mColor;
    float mIntensity;
    
    float mRadius;
    
    GLuint ubo;
    UBOData ubodata;
};

#endif /* defined(__KrullGL__Light__) */