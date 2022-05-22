#include "TubeGeometry.h"
#include "glm/glm.hpp"
#include <vendor/glm/ext/matrix_transform.hpp>

namespace geometry
{
	float tubeVertexBufferData = {};

	int tubeIndexBufferData = {};

	VertexBufferLayout TubeGeometry::GenerateLayout()
	{
		return VertexBufferLayout();
	}

	void TubeGeometry::GenerateVertexBufferData(int segments)
	{
	}

	void TubeGeometry::GenerateIndexBufferData(std::vector<glm::vec3> path, int segments, bool loop)
	{
		for (size_t pointIndex = 0; pointIndex < path.size(); pointIndex)
		{
			glm::vec3 currentPoint = path[pointIndex];
			glm::vec3 nextPoint;
			if (pointIndex == path.size() - 1)
			{
				if (loop)
				{
					nextPoint = path[0];
				}
				else
				{
					nextPoint = path[pointIndex - 1]; //TODO: this wont work, the indeces will be fliped, the faces will be mangled together
				}
			}
			else
			{
				nextPoint = path[pointIndex + 1];
			}

			glm::vec3 directionToNextPoint = glm::normalize(nextPoint - currentPoint);
			glm::mat4 tangentVector = glm::rotate(
				glm::translate(glm::mat4(1.0f), directionToNextPoint),
				glm::pi<float>() / 2,
				glm::vec3(0.0f, 1.0f, 0.0f));

		}
	}

	TubeGeometry::TubeGeometry(std::vector<glm::vec3> path, int segments, bool loop)
	{
	}
}
