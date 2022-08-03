#pragma once
#include "IScene.h"
#include "Shader.h"
#include <geometries/BezierIntervalGeometry.h>
#include <geometries/SphereGeometry.h>

namespace scenes
{
	class QuaternionicBezierScene : IScene {
	private:
		glm::vec4 u_q;
		glm::vec4 u_Pq0;
		glm::vec4 u_Pq1;

		glm::vec3 viewPos;
		glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 16.0f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		geometry::BezierIntervalGeometry line;
		geometry::SphereGeometry sphere;

		Shader quaternionShader;
		Shader shadedColor;
	public:
		QuaternionicBezierScene();

		glm::vec3 sceneCenter = glm::vec3(0.0f, 1.0f, 0.0f);

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}
