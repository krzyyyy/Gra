#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform float liveFactorF;

void main()
{
    vec3 barColor = vec3(1-liveFactorF, liveFactorF, 0 );
//    vec3 foreground 
    FragColor = vec4( barColor, 1.0f);// texture(ourTexture, TexCoord);
}