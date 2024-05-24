#include "Camera.h"


namespace my_engine
{
	model_trans::model_trans(const std::string& trnasname,Shader* program):m_uname(trnasname),m_program(program)
	{
		m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		m_rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		m_trans = m_translate * m_rotate * m_rotate;
		m_program->SetUniformmat4(m_uname, m_trans);
	}

	model_trans::~model_trans()
	{
	}

	void model_trans::Set_transform(glm::vec3 scale, float angle, glm::vec3 rotate, glm::vec3 translate)
	{
		SetTranslate(translate);
		SetRotate(angle, rotate);
		SetScale(scale);
		m_trans = m_translate * m_rotate * m_rotate;
		m_program->SetUniformmat4(m_uname, m_trans);
	}

	void model_trans::SetRotate(float angle, glm::vec3 rotate)
	{
		m_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotate);
		m_trans = m_translate * m_rotate * m_rotate;
		m_program->SetUniformmat4(m_uname, m_trans);
	}

	void model_trans::SetScale(glm::vec3 scale)
	{
		m_scale = glm::scale(glm::mat4(1.0f), scale);
		m_trans = m_translate * m_rotate * m_rotate;
		m_program->SetUniformmat4(m_uname, m_trans);
	}

	void model_trans::SetTranslate(glm::vec3 translate)
	{
		m_translate = glm::translate(glm::mat4(1.0f), translate);
		m_trans = m_translate * m_rotate * m_rotate;
		m_program->SetUniformmat4(m_uname, m_trans);
	}

	projection::projection(const std::string& uniformname, Shader* program):m_program(program),m_uname(uniformname)
	{
		ortho = true;
		m_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		m_program->SetUniformmat4(m_uname, m_projection);
	}

	projection::~projection()
	{

	}

	void projection::SetProjection(float angle, float width_height, float linear, float far)
	{
		ortho = false;
		m_projection = glm::perspective(glm::radians(angle), width_height, linear, far);
		m_program->SetUniformmat4(m_uname, m_projection);
	}

	void projection::SetOrtho(float left, float right, float down, float up, float linear, float far)
	{
		ortho = true;
		m_projection = glm::ortho(left,right,down,up,linear,far);
		m_program->SetUniformmat4(m_uname, m_projection);

	}

	

	camera::camera(const std::string& u_name,Shader* program,glm::vec3 pos, glm::vec3 front, glm::vec3 up)
		:m_Pos(pos),m_Front(front),m_Up(up),m_uname(u_name),m_program(program)
	{
		m_look = glm::lookAt(pos,front,up);
		m_program->SetUniformmat4(m_uname, m_look);
	}

	camera::~camera()
	{
	}

}







