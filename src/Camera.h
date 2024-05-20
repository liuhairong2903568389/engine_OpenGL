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
		
		
	private:
		glm::mat4 m_scale;
		glm::mat4 m_rotate;
		glm::mat4 m_translate;
		glm::mat4 u_MVP;
		std::string m_uniformname;
		Shader* m_program;
		
	};
	class camera {

	};
}

