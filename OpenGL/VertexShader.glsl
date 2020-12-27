#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);//vec4(aPos, 1.0f);// 
    ourColor = vec3(1., 1., 1.);
    TexCoord = vec2(1., 1.);
}