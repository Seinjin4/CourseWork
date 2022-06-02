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

		geometry::BezierIntervalGeometry line;
		//geometry::SphereGeometry sphere;

		Shader quaternionShader;
		Shader normalVisualization;
	public:
		QuaternionicBezierScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}
