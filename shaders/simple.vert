#version 330 core
in vec2 vertexPos;


layout (std140) uniform Matrices{
    mat4 P;
    mat4 V;
};

uniform mat4 M;

out vec2 pos;

void main()
{
    pos = (M * vec4(vertexPos,0,1)).xy;
  gl_Position = P* V * M * vec4(vertexPos, 0.0,  1.0);
   // gl_Position = vec4(vertexPos, 0.0,  1.0);
}
