#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 v_color;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{
    color = v_color;
};