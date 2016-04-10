#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;
#define PI 3.14

void main()
{
    
    int samples = 2*512;
    float distance = 1.0;
    
    bool hit = false;
    //Sampled angle
    float theta = TexCoords.x * 2*PI;
    
    for (float y =0.0; y<samples; y +=1.0) {
        //radius to sample, between 0 and 1
        float r = (y/samples);
        
        vec2 coord = vec2(r*cos(theta), r*sin(theta))/2 + 0.5;
        
        vec4 data = texture(screenTexture, coord);
        
        if (data.a > 0.1){
            distance = r;
            hit = true;
        }
        if (data.a < 0.1 && hit){
            break;
        }
    }
    color = vec4(distance, 0,0,1.0);
        //color = vec4(1.0, 0,0,1.0);
}

/*
//inputs from vertex shader
varying vec2 vTexCoord0;

//uniform values
uniform sampler2D u_texture;
uniform vec2 resolution;

//alpha threshold for our occlusion map
const float THRESHOLD = 0.75;

void main(void) {
    float distance = 1.0;
    
    for (float y=0.0; y<resolution.y; y+=1.0) {
        //rectangular to polar filter
        vec2 norm = vec2(vTexCoord0.s, y/resolution.y) * 2.0 - 1.0;
        float theta = PI*1.5 + norm.x * PI;
        float r = (1.0 + norm.y) * 0.5;
        
        //coord which we will sample from occlude map
        vec2 coord = vec2(-r * sin(theta), -r * cos(theta))/2.0 + 0.5;
        
        //sample the occlusion map
        vec4 data = texture2D(u_texture, coord);
        
        //the current distance is how far from the top we've come
        float dst = y/resolution.y;
        
        //if we've hit an opaque fragment (occluder), then get new distance
        //if the new distance is below the current, then we'll use that for our ray
        float caster = data.a;
        if (caster > THRESHOLD) {
            distance = min(distance, dst);
            //NOTE: we could probably use "break" or "return" here
        }
    }
    gl_FragColor = vec4(vec3(distance), 1.0);
}*/