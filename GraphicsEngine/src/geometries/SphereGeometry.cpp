#include "SphereGeometry.h"

namespace geometry
{
	VertexBufferLayout SphereGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);

		return vbLayout;
	}

	void SphereGeometry::GenerateVertexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(ratio);
		sphereVertexBufferData->push_back(0.0f);

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(1.0f);
		sphereVertexBufferData->push_back(0.0f);

		for (size_t i = 0; i < verticalSegments; i++)
		{
			//float newYCoordinate = ratio - ((float)(i + 1) / (verticalSegments + 1)) * 2 * ratio;
			float newYCoordinate = ratio * glm::cos(glm::pi<float>() * (float)(i + 1) / verticalSegments);
			float segmentRatio = ratio * glm::sin(glm::pi<float>() * (float)(i + 1) / verticalSegments);

			for (size_t j = 0; j < horizontalSegments; j++)
			{
				glm::vec3 newPoint( 
					glm::sin(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio,
					newYCoordinate,
					glm::cos(glm::pi<float>() * 2 * j / horizontalSegments) * segmentRatio
				);

				sphereVertexBufferData->push_back(newPoint.x);
				sphereVertexBufferData->push_back(newPoint.y);
				sphereVertexBufferData->push_back(newPoint.z);

				glm::vec3 newPointNormal = glm::normalize(newPoint);

				sphereVertexBufferData->push_back(newPointNormal.x);
				sphereVertexBufferData->push_back(newPointNormal.y);
				sphereVertexBufferData->push_back(newPointNormal.z);
			}
		}

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(-ratio);
		sphereVertexBufferData->push_back(0.0f);

		sphereVertexBufferData->push_back(0.0f);
		sphereVertexBufferData->push_back(-1.0f);
		sphereVertexBufferData->push_back(0.0f);
	}

	void SphereGeometry::GenerateIndexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments)
	{
		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBufferData->push_back(0);
			sphereIndexBufferData->push_back(1 + x);
			sphereIndexBufferData->push_back(1 + (x + 1) % horizontalSegments);
		}

		for (size_t y = 0; y < verticalSegments - 1; y++)
		{
			for (size_t x = 0; x < horizontalSegments; x++)
			{
				sphereIndexBufferData->push_back(1 + y * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);

				sphereIndexBufferData->push_back(1 + y * horizontalSegments + (x + 1) % horizontalSegments);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + x);
				sphereIndexBufferData->push_back(1 + (y + 1) * horizontalSegments + (x + 1) % horizontalSegments);
			}
		}

		for (size_t x = 0; x < horizontalSegments; x++)
		{
			sphereIndexBufferData->push_back(1 + (verticalSegments - 1) * horizontalSegments + x);
			sphereIndexBufferData->push_back(1 + verticalSegments * horizontalSegments);
			sphereIndexBufferData->push_back(1 + (verticalSegments - 1) * horizontalSegments + (x + 1) % horizontalSegments);
		}
	}

	SphereGeometry::SphereGeometry(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments) :
		sphereVertexBufferData(new std::vector<float>),
		sphereIndexBufferData(new std::vector<unsigned int>)
	{
		GenerateVertexBufferData(ratio, verticalSegments, horizontalSegments);
		GenerateIndexBufferData(ratio, verticalSegments, horizontalSegments);
		GenerateLayout();

		geometryData.CreateVertexArray(sphereVertexBufferData->data(), sphereVertexBufferData->size() * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(sphereIndexBufferData->data(), sphereIndexBufferData->size());
	}
}