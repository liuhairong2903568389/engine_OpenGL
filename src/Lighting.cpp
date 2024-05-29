#include "Lighting.h"

my_engine::material::material()
{

}

my_engine::material::~material()
{

}

void my_engine::material::setMaterial(Shader*)
{

}

my_engine::light::light(Shader* m_shader, glm::vec3 lightposition, glm::vec3 lightcolor)
	:m_program(m_shader),m_position(lightposition),m_ambients(lightcolor * 0.1f),m_diffuse(lightcolor * 0.2f),m_specular(lightcolor * 0.7f)
{

}

my_engine::light::~light()
{

}

void my_engine::light::setLight()
{

}
