#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>
#include <geometries/SphereGeometry.h>
#include <geometries/TubeGeometry.h>

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
		geometry::TubeGeometry tube;
		geometry::SphereGeometry sphere;

		Shader uvTestShader;
		Shader dupinPatchShader;
		Shader shadedColor;

		std::vector<glm::vec3> generateCircularPoints(unsigned int pointCount);

	public:
		DupinPatchScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}