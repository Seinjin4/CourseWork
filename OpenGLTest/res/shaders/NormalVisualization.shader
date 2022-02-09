#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

out vec4 v_color;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   vec4 t_normal = u_MVP * normal;
   v_color = vec4(t_normal.x, t_normal.y, t_normal.z, 1.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;

void main()
{
	color = v_color;
};