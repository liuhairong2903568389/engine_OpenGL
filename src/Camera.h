#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"Renderer.h"
#include<iostream>

namespace my_engine {
	class model {





	};
	class translational {
	public:
		translational(const std::string& uniformname,Shader* program);
		~translational();
		void Set_transform(glm::vec3 scale, float angle, glm::vec3 rotate, glm::vec3 translate);
		void SetRotate(float angle, glm::vec3 rotate);
		void SetScale(glm::vec3 scale);
		void SetTranslate(glm::vec3 translate);
		void SetProjection(float angle,float width_height,float linear,float far);
		void SetOrtho(float left, float right, float down, float up, float linear, float far);
		void SetView(glm::vec3 viewpos,glm::vec3 viewfront,glm::vec3 viewup);
		void update() ;
		
		glm::mat4 getscale()const { return m_scale; };
		glm::mat4 getrotate()const { return m_rotate; };
		glm::mat4 gettranslate()const { return m_scale; };
		glm::mat4 getprojection()const { return m_projection; };
		glm::mat4 getview()const { return m_view; };
		glm::mat4 getMVP()const { return u_MVP; };


	private:
		glm::mat4 m_scale;
		glm::mat4 m_rotate;
		glm::mat4 m_translate;
		bool ortho;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 u_MVP;
		std::string m_uniformname;
		Shader* m_program;
		
	};
	class camera {
	public:
		camera();
		~camera();

	private:


	};
}

