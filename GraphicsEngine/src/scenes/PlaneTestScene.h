#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>

namespace scenes
{
	class PlaneTestScene : IScene {
	private:
		float mag = 1.0f;
		float a = 0.5f;
		float b = 0.5f;
		float c = 0.5f;

		geometry::PlaneGeometry plane;

		Shader singularityTexture;
		Shader uvTest;

	public:
		PlaneTestScene();

		glm::vec3 sceneCenter = glm::vec3(0.0f, 0.0f, 0.0f);

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}