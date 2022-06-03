#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>
#include <geometries/SphereGeometry.h>
#include <geometries/TubeGeometry.h>

namespace scenes
{
	class CyclidicCubeScene : IScene {
	private:
		float p6Slider;
		bool wireframeToggle;
		glm::vec3 v1;
		glm::vec3 v2;

		geometry::PlaneGeometry plain;
		//geometry::TubeGeometry tube;
		//geometry::SphereGeometry sphere;

		Shader cyclideCubeSideShader;

	public:
		CyclidicCubeScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}