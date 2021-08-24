#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main()
{    
//vec3 ambient  = 1  * vec3(texture(texture_diffuse1, TexCoords));
//vec3 diffuse  = 1  * 1 * vec3(texture(texture_diffuse1, TexCoords));  
//vec3 specular = 1 * 1 * vec3(texture(texture_specular1, TexCoords));
//FragColor = vec4( diffuse, 1.0);   
    FragColor = texture(texture_diffuse1, TexCoords);
}