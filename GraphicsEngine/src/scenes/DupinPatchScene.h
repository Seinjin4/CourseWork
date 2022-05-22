#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>

namespace scenes
{
	class DupinPatchScene : IScene {
	private:
		float p1Slider;
		float p2Slider;
		float p3Slider;
		float p4Slider;
		int size;
		float angle;

		geometry::PlaneGeometry plane;

		Shader uvTestShader;
		Shader dupinPatchShader;
	public:
		DupinPatchScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}