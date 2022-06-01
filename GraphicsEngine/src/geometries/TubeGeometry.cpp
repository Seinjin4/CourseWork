#include "TubeGeometry.h"
#include "glm/glm.hpp"
#include <vendor/glm/ext/matrix_transform.hpp>

namespace geometry
{
	VertexBufferLayout TubeGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);

		return VertexBufferLayout();
	}

	void TubeGeometry::GenerateVertexBufferData(const std::vector<glm::vec3>& path, int segments, float radius, bool loop)
	{
		glm::vec3 directionToNextPoint;
		for (size_t pointIndex = 0; pointIndex < path.size(); pointIndex++)
		{
			glm::vec3 currentPoint = path[pointIndex];
			glm::vec3 nextPoint;
			glm::vec3 previousPoint;

			if (pointIndex == path.size() - 1)
			{
				if (loop)
				{
					nextPoint = path[0];
				}
				else
				{
					nextPoint = currentPoint + directionToNextPoint;
				}
			}
			else
			{
				nextPoint = path[pointIndex + 1];
			}

			if (pointIndex == 0)
			{
				directionToNextPoint = glm::normalize(nextPoint - currentPoint);
			}
			else
			{
				previousPoint = path[pointIndex - 1];
				directionToNextPoint = glm::normalize(glm::normalize(nextPoint - currentPoint) - glm::normalize(previousPoint - currentPoint));
			}

			//glm::vec3 tangentVector = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(directionToNextPoint, 1.0f);
			//TODO: use (0, 1, 0) for y positive, use (0, -1, 0) for y negative
			glm::vec3 crossVector = glm::vec3(0.0f, 1.0f, 0.0f);;

			if (directionToNextPoint.x < 0 && directionToNextPoint.z == 0)
			{
				crossVector = glm::vec3(0.0f, -1.0f, 0.0f);
			}
			else if (directionToNextPoint.z < 0 && directionToNextPoint.x == 0)
			{
				crossVector = glm::vec3(0.0f, -1.0f, 0.0f);
			}
			else
			{
				crossVector = glm::vec3(0.0f, 1.0f, 0.0f);
			}

			glm::vec3 tangentVector = glm::normalize(glm::cross(directionToNextPoint, crossVector));

			for (size_t i = 0; i < segments; i++)
			{
				glm::vec3 newPoint = glm::rotate(glm::mat4(1.0f), glm::pi<float>() * 2 * i / segments, directionToNextPoint) * glm::vec4(tangentVector, 1.0f) * radius;

				glm::vec3 normal = glm::vec3(newPoint);

				glm::vec3 newVertexCoordinate = newPoint + currentPoint;

				tubeVertexBufferData->push_back(newVertexCoordinate.x);
				tubeVertexBufferData->push_back(newVertexCoordinate.y);
				tubeVertexBufferData->push_back(newVertexCoordinate.z);

				tubeVertexBufferData->push_back(normal.x);
				tubeVertexBufferData->push_back(normal.y);
				tubeVertexBufferData->push_back(normal.z);
			}
		}
	}

	void TubeGeometry::GenerateIndexBufferData(int pathPartCount, int segments, bool loop)
	{
		int tubePartCount;

		if (loop)
			tubePartCount = pathPartCount;
		else
			tubePartCount = pathPartCount - 1;

		for (size_t y = 0; y < tubePartCount; y++)
		{
			for (size_t x = 0; x < segments; x++)
			{
				//first quad polygon
				tubeIndexBufferData->push_back(y * segments + x);
				tubeIndexBufferData->push_back((y + 1) % pathPartCount * segments + x);
				tubeIndexBufferData->push_back(y * segments + (x + 1) % segments);

				//second quad polygon
				tubeIndexBufferData->push_back((y + 1) % pathPartCount * segments + x);
				tubeIndexBufferData->push_back((y + 1) % pathPartCount * segments + (x + 1) % segments);
				tubeIndexBufferData->push_back(y * segments + (x + 1) % segments);
			}
		}
	}

	TubeGeometry::TubeGeometry(const std::vector<glm::vec3>& path, int segments, float radius, bool loop):
		tubeVertexBufferData(new std::vector<float>),
		tubeIndexBufferData(new std::vector<unsigned int>)
	{
		GenerateVertexBufferData(path, segments, radius, loop);
		GenerateIndexBufferData(path.size(), segments, loop);
		GenerateLayout();

		geometryData.CreateVertexArray(tubeVertexBufferData->data(), tubeVertexBufferData->size() * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(tubeIndexBufferData->data(), tubeIndexBufferData->size());
	}
	TubeGeometry::~TubeGeometry()
	{
		delete tubeVertexBufferData;
		delete tubeIndexBufferData;
	}
}
