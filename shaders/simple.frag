#version 330 core

#define PI 3.14
const int Light_Count = 4;

struct LightInformation {
    vec4 posRadInt;
    vec4 color;
};
uniform sampler2D occlusionMap;

layout(std140) uniform Light {
    LightInformation Lights;
};

in vec2 pos;
out vec4 frag_color;

uniform vec3 boxColor;
uniform int pass;

float sample(float theta, float r) {
    return step(r, texture(occlusionMap, vec2(theta,0.0)).r);
}


void main()
{
    if (pass == 1){
        frag_color = vec4(boxColor, 1);
    }else if (pass == 2){
        float d = distance(pos, Lights.posRadInt.xy);
        float radius = Lights.posRadInt.z;
        
        float attenuation = clamp(1.0 - d*d/(radius*radius), 0.0, 1.0);
        
        vec2 lightToPos = pos-Lights.posRadInt.xy;
        float theta = acos(dot(normalize(lightToPos), vec2(1,0)));
        if (pos.y > Lights.posRadInt.y){
            theta = 2*PI - theta;
        }
        //normalize
        theta = theta/(2*PI);
        float r = length(lightToPos)/(radius);
        
        //we multiply the blur amount by our distance from center
        //this leads to more blurriness as the shadow "fades away"
        float blur = (1./512)  * smoothstep(0., 1., r);
        
        //now we use a simple gaussian blur
        float sum = 0.0;
        
        sum += sample(theta - 4.0*blur, r) * 0.05;
        sum += sample(theta - 3.0*blur, r) * 0.09;
        sum += sample(theta - 2.0*blur, r) * 0.12;
        sum += sample(theta - 1.0*blur, r) * 0.15;
        
        sum += sample(theta, r) * 0.16;
        
        sum += sample(theta + 1.0*blur, r) * 0.15;
        sum += sample(theta + 2.0*blur, r) * 0.12;
        sum += sample(theta + 3.0*blur, r) * 0.09;
        sum += sample(theta + 4.0*blur, r) * 0.05;
        
        frag_color = vec4(boxColor, 1) * attenuation*sum;
        //frag_color = vec4(occluded,0.0,0.0,1.0);
    }else{
        frag_color = vec4(1.0,1.0,1.0, 1);
    }
    
}
