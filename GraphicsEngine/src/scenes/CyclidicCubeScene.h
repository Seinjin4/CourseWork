#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>
#include <geometries/SphereGeometry.h>
#include <geometries/TubeGeometry.h>

namespace scenes
{
	class CyclidicCubeScene : IScene {
	private:
		float p3Slider;
		float p5Slider;
		float p6Slider;
		bool wireframeToggle;
		glm::vec3 v1;
		glm::vec3 v2;

		glm::vec3 p0 = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 p1 = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 p2 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 p3;

		glm::vec3 p4 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 p5;
		glm::vec3 p6;
		glm::vec3 p7;


		geometry::PlaneGeometry plain;
		//geometry::TubeGeometry tube;
		//geometry::SphereGeometry sphere;

		Shader cyclideCubeSideShader;

	public:
		CyclidicCubeScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}