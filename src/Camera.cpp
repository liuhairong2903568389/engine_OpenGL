#include "Camera.h"


my_engine::translational::translational(const std::string& uniformname,Shader* program) : m_uniformname(uniformname),m_program(program)
{
	u_MVP = glm::mat4(1.0f);
	m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_scale = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f, 1.0f, 1.0f));
	
	
}

my_engine::translational::~translational()
{

}

void my_engine::translational::Set_transform(glm::vec3 scale, float angle, glm::vec3 rotate, glm::vec3 translate)
{
	
	SetTranslate(translate);
	SetRotate(angle, rotate);
	SetScale(scale);
	u_MVP = m_translate * m_rotate * m_scale;
	m_program->SetUniformmat4(m_uniformname, u_MVP);

}

void my_engine::translational::SetRotate(float angle, glm::vec3 rotate)
{

	m_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotate);
}

void my_engine::translational::SetScale(glm::vec3 scale)
{
	m_scale = glm::scale(glm::mat4(1.0f), scale);
}

void my_engine::translational::SetTranslate(glm::vec3 translate)
{
	m_translate = glm::translate(glm::mat4(1.0f), translate);
}








