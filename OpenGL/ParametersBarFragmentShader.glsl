#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color;

void main()
{
    vec3 background = vec3(1.f, 0.f, 0.f);
//    vec3 foreground 
    FragColor = vec4( color, 1.0f);// texture(ourTexture, TexCoord);
}