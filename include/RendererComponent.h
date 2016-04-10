//
//  RendererComponent.h
//  KrullGL
//
//  Created by Pontus Orraryd on 2015-08-04.
//  Copyright (c) 2015 Pontus Orraryd. All rights reserved.
//

#ifndef __KrullGL__RendererComponent__
#define __KrullGL__RendererComponent__

#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.hpp"
#include "GameObject.h"
class GameObject;

class RendererComponent
{
public:
    
    
    RendererComponent(ShaderProgram* shader, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
    
    // Destructor
    ~RendererComponent();
    
    void render(GameObject *obj);
    void setColor(glm::vec3 col);
    
private:
    static bool vaoInit;
    static void initBox();
    
    ShaderProgram* mShader;
    glm::vec3 mColor;
    
    //GL variables
    static GLuint vao;
};

#endif /* defined(__KrullGL__RendererComponent__) */
