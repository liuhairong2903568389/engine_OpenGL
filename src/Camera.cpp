#include "Camera.h"


namespace my_engine
{
	model_trans::model_trans(const std::string& trnasname)
	{
		m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		m_rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		m_trans = glm::mat4(1.0);
	}

	model_trans::~model_trans()
	{
	}

	void model_trans::Set_transform(glm::vec3 scale, float angle, glm::vec3 rotate, glm::vec3 translate)
	{
		SetTranslate(translate);
		SetRotate(angle, rotate);
		SetScale(scale);
	}

	void model_trans::SetRotate(float angle, glm::vec3 rotate)
	{
		m_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotate);
	}

	void model_trans::SetScale(glm::vec3 scale)
	{
		m_scale = glm::scale(glm::mat4(1.0f), scale);
	}

	void model_trans::SetTranslate(glm::vec3 translate)
	{
		m_translate = glm::translate(glm::mat4(1.0f), translate);
	}

	void model_trans::update_trans()
	{
		*m_translate* m_rotate* m_scale;
	}

	translational::translational(const std::string& uniformname, Shader* program) : m_uniformname(uniformname), m_program(program)
	{
		u_MVP = glm::mat4(1.0f);
		ortho = true;
		
		m_projection = glm::mat4(1.0f);
		m_view = glm::mat4(1.0f);


	}

	translational::~translational()
	{

	}

	

	void translational::SetProjection(float angle, float width_height, float linear, float far)
	{
		ortho = false;
		m_projection = glm::perspective(glm::radians(angle), width_height, linear, far);
	}

	void translational::SetOrtho(float left, float right, float down, float up, float linear, float far)
	{
		ortho = true;
		m_projection = glm::ortho(left, right, down, up, linear, far);
	}

	void translational::SetView(glm::vec3 viewpos, glm::vec3 viewfront, glm::vec3 viewup)
	{
		m_view = glm::lookAt(viewpos, viewfront, viewup);
	}

	void translational::update()
	{
		u_MVP = m_projection * m_view;
		m_program->SetUniformmat4(m_uniformname, u_MVP);
	}

	camera::camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up):m_Pos(pos),m_Front(front),m_Up(up)
	{
		m_look = glm::lookAt(pos,front,up);
	}

	camera::~camera()
	{
	}

	void camera::do_movement()
	{

	}

	

}







