#include "MathCalculations.h"
#include "glm/glm.hpp"
#include <vendor/glm/ext/matrix_transform.hpp>

namespace mathCalc
{
	CircleData GetCircleDataFrom3Points(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
	{
		glm::vec3 plainDirection = glm::normalize(glm::cross(p3 - p1, p2 - p1));
		glm::vec3 tempPlainDirection = glm::normalize(glm::cross(p2 - p1, p3 - p1));

		glm::vec3 plainTranslation = -p1;
		glm::vec3 plainRotationAxis = glm::cross(plainDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		float plainRotationAngle;

		if (glm::length(plainRotationAxis) == 0)
		{
			plainRotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
			plainRotationAngle = 0.0f;
		}
		else
		{
			plainRotationAxis = glm::normalize(plainRotationAxis);
			plainRotationAngle = glm::acos(glm::dot(plainDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), plainTranslation);;

		glm::mat4 rotationMatrix =
			glm::rotate(glm::mat4(1.0f), plainRotationAngle, plainRotationAxis);

		glm::vec3 transformedP1 = translationMatrix * glm::vec4(p1, 1.0f);
		glm::vec3 transformedP2 = translationMatrix * glm::vec4(p2, 1.0f);
		glm::vec3 transformedP3 = translationMatrix * glm::vec4(p3, 1.0f);
		
		transformedP1 = rotationMatrix * glm::vec4(transformedP1, 1.0f);
		transformedP2 = rotationMatrix * glm::vec4(transformedP2, 1.0f);
		transformedP3 = rotationMatrix * glm::vec4(transformedP3, 1.0f);

		glm::vec3 v12 = transformedP1 - transformedP2;
		glm::vec3 v13 = transformedP1 - transformedP3;

		glm::vec3 v31 = transformedP3 - transformedP1;
		glm::vec3 v21 = transformedP2 - transformedP1;

		glm::vec3 sv13 = glm::vec3(glm::pow(transformedP1.x, 2) - glm::pow(transformedP3.x, 2), 0, glm::pow(transformedP1.z, 2) - glm::pow(transformedP3.z, 2));

		glm::vec3 sv21 = glm::vec3(glm::pow(transformedP2.x, 2) - glm::pow(transformedP1.x, 2), 0, glm::pow(transformedP2.z, 2) - glm::pow(transformedP1.z, 2));

		float centerZ = -(
			((sv13.x) * (v12.x) + (sv13.z) * (v12.x) + (sv21.x) * (v13.x) + (sv21.z) * (v13.x)) /
			(2 * (
				(v31.z) * (v12.x) - (v21.z) * (v13.x)
				)));

		float centerX = -(
			((sv13.x) * (v12.z) + (sv13.z) * (v12.z) + (sv21.x) * (v13.z) + (sv21.z) * (v13.z)) /
			(2 * (
				(v31.x) * (v12.z) - (v21.x) * (v13.z)
				)));

		glm::vec3 centerCoordinates = glm::vec3(centerX, 0, centerZ);

		rotationMatrix =
			glm::rotate(glm::mat4(1.0f), -plainRotationAngle, plainRotationAxis);

		translationMatrix =
			glm::translate(glm::mat4(1.0f), -plainTranslation);

		centerCoordinates = rotationMatrix * glm::vec4(centerCoordinates, 1.0f);
		centerCoordinates = translationMatrix * glm::vec4(centerCoordinates, 1.0f);

		CircleData returnData = { plainDirection, centerCoordinates, glm::length(p1 - centerCoordinates) };

		return returnData;
	}
	
	glm::vec3 CalculatePointInCircle(CircleData circleData, float angle)
	{
		glm::vec3 point = glm::vec3(
			glm::sin(angle) * circleData.radius,
			0,
			glm::cos(angle) * circleData.radius
		);

		glm::vec3 plainRotationAxis = glm::cross(circleData.direction, glm::vec3(0.0f, 1.0f, 0.0f));
		float plainRotationAngle;

		if (glm::length(plainRotationAxis) == 0)
		{
			plainRotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
			plainRotationAngle = 0.0f;
		}
		else
		{
			plainRotationAxis = glm::normalize(plainRotationAxis);
			plainRotationAngle = glm::acos(glm::dot(circleData.direction, glm::vec3(0.0f, 1.0f, 0.0f)));
		}

		glm::vec3 transformedPoint =
			glm::rotate(glm::mat4(1.0f), plainRotationAngle, plainRotationAxis) *
			glm::vec4(point, 1.0f);

		transformedPoint =
			glm::translate(glm::mat4(1.0f), circleData.centerPosition) *
			glm::vec4(transformedPoint, 1.0f);

		return transformedPoint;
	}
	glm::vec3 IntersectionPointFrom3Planes(Plane plane1, Plane plane2, Plane plane3)
	{
		glm::vec3 m1 = glm::vec3(plane1.normal.x, plane2.normal.x, plane3.normal.x);
		glm::vec3 m2 = glm::vec3(plane1.normal.y, plane2.normal.y, plane3.normal.y);
		glm::vec3 m3 = glm::vec3(plane1.normal.z, plane2.normal.z, plane3.normal.z);

		glm::vec3 d = glm::vec3(plane1.distance, plane2.distance, plane3.distance);

		glm::vec3 u = glm::cross(m2, m3);
		glm::vec3 v = glm::cross(m1, d);

		float denom = glm::dot(m1, u);

		if (glm::abs<float>(denom) < 0.001f)
			return glm::vec3(0.0f);

		glm::vec3 intersectionPoint = glm::vec3(
			glm::dot(d, u) / denom,
			glm::dot(m3, v) / denom,
			-glm::dot(m2, v) / denom
		);

		return intersectionPoint;
	}
	Plane GetPlaneFromCircleData(CircleData circleData)
	{
		glm::vec3 normalizedCircleCenterVector = glm::normalize(circleData.centerPosition);
		glm::vec3 rotationAxis = glm::cross(normalizedCircleCenterVector, circleData.direction);
		float angleCos = glm::dot(normalizedCircleCenterVector, glm::normalize(circleData.direction));

		float angleCosByHandX = 
			normalizedCircleCenterVector.x * circleData.direction.x;
		float angleCosByHandY = 
			normalizedCircleCenterVector.y * circleData.direction.y;
		float angleCosByHandZ = 
			normalizedCircleCenterVector.z * circleData.direction.z;

		float distance = glm::length(circleData.centerPosition) * angleCos;
		Plane plane = { circleData.direction, distance };

		return plane;
	}
}
