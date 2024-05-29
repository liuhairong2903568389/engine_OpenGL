#pragma once
#include"glm/glm.hpp"
#include"Renderer.h"

namespace my_engine {
	class material {
	public:
		material();
		~material();

		void setMaterial(Shader*);
	private:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

	};

	class light {
	public:
		light(Shader* m_shader,glm::vec3 lightposition,glm::vec3 lightcolor = glm::vec3(1.0f));
		~light();

		void setLight();
	private:
		glm::vec3 m_position;
		glm::vec3 m_ambients;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
		Shader* m_program;
	};
}
