#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture_pos;
layout(location = 2) in vec3 m_normal;
out vec2 texture_Pos;
out vec3 m_Normal;
out vec3 Pos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_pro;
void main()
{
	gl_Position =u_pro * u_view * u_model * vec4(position, 1.0);
	texture_Pos = texture_pos;
	m_Normal = mat3(transpose(inverse(u_model))) * m_normal; ;
	Pos =vec3(u_model * vec4(position,1.0));
};

#shader fragment
#version 330 core
in vec2 texture_Pos;
in vec3 Pos;
in vec3 m_Normal;
out vec4 color;


uniform float T_color;
uniform sampler2D mytexture1;
uniform sampler2D mytexture2;
uniform vec3 LightPos;
uniform vec3 LightCol;
uniform vec3 ViewPos;
void main()
{
	float ambients = 0.1;
	//vec4 col_tex = mix(texture(mytexture1,texture_Pos),texture(mytexture2,texture_Pos),1.0);

	vec3 norm = normalize(m_Normal);
	vec3 lightDir = normalize(LightPos - Pos);
	float diff = max(dot(norm,lightDir),0.0);//cos
	vec3 diffus = diff * LightCol;//

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(ViewPos - Pos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 speculars = specularStrength * spec * LightCol;

	vec3 objectColor = vec3(1.0,1.0,0.2);

	vec3 resultcol = (ambients + diffus) * objectColor;
	color = vec4(resultcol,1.0);
};