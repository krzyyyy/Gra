#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float liveFactor;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    float offsetYAxis = 0.1;
    vec3 newPos = vec3(aPos.x*liveFactor, aPos.y , aPos.z+ offsetYAxis);
    gl_Position = projection * view * model * vec4(newPos, 1.0);//vec4(aPos, 1.0f);// 
    ourColor = vec3(1., 1., 1.);
    TexCoord = vec2(1., 1.);
}