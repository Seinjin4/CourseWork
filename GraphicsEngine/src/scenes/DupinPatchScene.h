#pragma once
#include "IScene.h"
#include "Shader.h"
#include <geometries/PlaneGeometry.h>

namespace scenes
{
	class DupinPatchScene : IScene {
	private:
		glm::vec4 p;

		geometry::PlaneGeometry plane;

		Shader uvTest;
		//Shader dupin;

	public:
		DupinPatchScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);

	};
}