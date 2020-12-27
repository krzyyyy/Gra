#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color;

void main()
{
    FragColor = vec4(ourColor.x, 0., 0., 1.0f);// texture(ourTexture, TexCoord);
}