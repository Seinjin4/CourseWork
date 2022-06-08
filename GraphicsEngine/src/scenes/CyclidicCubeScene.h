#pragma once
#include "IScene.h"
#include <geometries/PlaneGeometry.h>
#include <geometries/SphereGeometry.h>
#include <geometries/TubeGeometry.h>
#include <vendor/MathCalculations.h>

namespace scenes
{
	class CyclidicCubeScene : IScene {
	private:
		float p3Slider;
		float p5Slider;
		float p6Slider;
		bool wireframeToggle = false;
		bool pointToggle = false;
		bool cubeToggle = true;

		glm::vec3 viewPos;
		glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 16.0f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 p0 = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 p1 = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 p2 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 p3;

		glm::vec3 p4 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 p5;
		glm::vec3 p6;
		glm::vec3 p7;

		mathCalc::CircleData sideA;
		mathCalc::CircleData sideB;
		mathCalc::CircleData sideC;

		geometry::PlaneGeometry plain;
		//geometry::TubeGeometry tube;
		geometry::SphereGeometry sphere;

		Shader cyclideCubeSideShader;
		Shader shadedColor;

		void RenderCube(const Renderer& renderer);
		void RenderPoints(const Renderer& renderer);
		void CalculatePoints();

	public:
		CyclidicCubeScene();

		void RenderScene(const Renderer& renderer, glm::mat4 newView);
	};
}