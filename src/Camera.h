#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"Renderer.h"
#include<iostream>

namespace my_engine {
	class model_trans {
	public:
		model_trans(const std::string&);
		~model_trans();
		void Set_transform(glm::vec3 scale, float angle, glm::vec3 rotate, glm::vec3 translate);
		void SetRotate(float angle, glm::vec3 rotate);
		void SetScale(glm::vec3 scale);
		void SetTranslate(glm::vec3 translate);

		void update_trans();
		glm::mat4 getscale()const { return m_scale; };
		glm::mat4 getrotate()const { return m_rotate; };
		glm::mat4 gettranslate()const { return m_scale; };

	private:
		glm::mat4 m_scale;
		glm::mat4 m_rotate;
		glm::mat4 m_translate;
		glm::mat4 m_trans;
	};

	class translational {
	public:
		translational(const std::string& uniformname,Shader* program);
		~translational();
		
		void SetProjection(float angle,float width_height,float linear,float far);
		void SetOrtho(float left, float right, float down, float up, float linear, float far);
		void SetView(glm::vec3 viewpos,glm::vec3 viewfront,glm::vec3 viewup);
		void update() ;
		
		
		glm::mat4 getprojection()const { return m_projection; };
		glm::mat4 getview()const { return m_view; };
		glm::mat4 getMVP()const { return u_MVP; };
	private:
		
		bool ortho;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 u_MVP;
		std::string m_uniformname;
		Shader* m_program;
		
	};
	class camera {
	public:
		camera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 front = glm::vec3(0.0f,0.0f,-1.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f));
		~camera();
		void setPos(glm::vec3 pos) { m_Pos = pos; };
		void setFront(glm::vec3 front) { m_Front = front; };
		void setUp(glm::vec3 up) { m_Up = up; };

		void do_movement();
	private:
		glm::vec3 m_Pos;
		glm::vec3 m_Front;
		glm::vec3 m_Up;

		glm::mat4 m_look;

	};
}

