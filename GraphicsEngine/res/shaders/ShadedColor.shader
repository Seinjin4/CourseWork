#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

out vec3 vposition;
out vec3 vnormal;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * position;
    vposition = position.xyz;
    vnormal = normal.xyz;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vnormal;
in vec3 vposition;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.7;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(vnormal);
    vec3 lightDir = normalize(lightPos - vposition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - vposition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
};