#pragma once
#include "glm/glm.hpp"
#include <vector>

namespace mathCalc
{
	struct CircleData
	{
		glm::vec3 direction;
		glm::vec3 centerPosition;
		float radius;
	};

	struct Plane
	{
		glm::vec3 normal;
		float distance;
	};

	CircleData GetCircleDataFrom3Points(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
	glm::vec3 CalculatePointInCircle(CircleData circleData, float angle);
	glm::vec3 IntersectionPointFrom3Planes(Plane plane1, Plane plane2, Plane plane3);
	Plane GetPlaneFromCircleData(CircleData circleData);
	std::vector<glm::vec3> GenerateCircularPoints(unsigned int pointCount);
}
