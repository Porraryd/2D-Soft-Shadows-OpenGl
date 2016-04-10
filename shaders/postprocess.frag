#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{
    color = texture(screenTexture, TexCoords);
    //color = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);
}
