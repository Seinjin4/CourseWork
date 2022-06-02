#pragma once
#include "IScene.h"
#include <geometries/TubeGeometry.h>
#include <geometries/SphereGeometry.h>

namespace scenes
{
	class SphereTestScene : IScene {
	private:
		geometry::SphereGeometry sphere;

		Shader ShadedColor;

	public:
		SphereTestScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}