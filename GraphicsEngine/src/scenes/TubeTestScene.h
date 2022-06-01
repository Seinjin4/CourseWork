#pragma once
#include "IScene.h"
#include <geometries/TubeGeometry.h>

namespace scenes
{
	class TubeTestScene : IScene {
	private:
		std::vector<glm::vec3> testPath = {glm::vec3(0.0f, 0.0f ,0.0f), glm::vec3(1.0f, 0.0f ,0.0f), glm::vec3(1.0f, 2.0f ,0.0f) };

		geometry::TubeGeometry tube;

		Shader basicColorShader;

		std::vector<glm::vec3> generateCircularPoints(unsigned int pointCount);

	public:
		TubeTestScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}