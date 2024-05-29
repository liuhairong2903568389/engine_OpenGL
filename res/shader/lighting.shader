#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_pro;
void main()
{
	gl_Position =u_model * vec4(position, 1.0);
	
};

#shader fragment
#version 330 core

out vec4 color;


uniform float T_color;

void main()
{
	color = vec4(1.0);
};