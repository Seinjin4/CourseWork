#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 UV;

out vec4 v_color;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * position;
    v_color = vec4(UV.x, 1.0f, UV.y, 1.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{
    color = v_color;
};