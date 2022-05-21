#include "PlaneGeometry.h"

namespace geometry
{
	float planeVertexBufferData[1024] = {};

	unsigned int planeIndexBufferData[1024] = {};

	VertexBufferLayout PlaneGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(2);

		return vbLayout;
	}

	void PlaneGeometry::GenerateVertexBufferData(int segments)
	{
		for (size_t y = 0; y < segments; y++)
		{
			for (size_t x = 0; x < segments; x++)
			{
				int offset = y * segments * 8 + x * 8;

				//position
				planeVertexBufferData[offset + 0] = -1 + 2 / static_cast<float>(segments - 1) * x;
				planeVertexBufferData[offset + 1] = 0;
				planeVertexBufferData[offset + 2] = -1 + 2 / static_cast<float>(segments - 1) * y;

				//normal
				planeVertexBufferData[offset + 3] = 0;
				planeVertexBufferData[offset + 4] = 1;
				planeVertexBufferData[offset + 5] = 0;

				//UV
				planeVertexBufferData[offset + 6] = 0 + 1 / static_cast<float>(segments - 1) * x;
				planeVertexBufferData[offset + 7] = 0 + 1 / static_cast<float>(segments - 1) * y;
			}
		}
	}

	void PlaneGeometry::GenerateIndexBufferData(int segments)
	{
		size_t polygonCount = 0;

		for (size_t y = 0; y < segments - 1; y++)
		{
			for (size_t x = 0; x < segments - 1; x++)
			{
				//first quad polygon
				planeIndexBufferData[polygonCount * 3 + 0] = y * segments + x;
				planeIndexBufferData[polygonCount * 3 + 1] = (y + 1) * segments + x;
				planeIndexBufferData[polygonCount * 3 + 2] = y * segments + x + 1;
				polygonCount++;

				//second quad polygon
				planeIndexBufferData[polygonCount * 3 + 0] = (y + 1) * segments + x;
				planeIndexBufferData[polygonCount * 3 + 1] = (y + 1) * segments + x + 1;
				planeIndexBufferData[polygonCount * 3 + 2] = y * segments + x + 1;
				polygonCount++;
			}
		}
	}

	PlaneGeometry::PlaneGeometry(const unsigned int segments) {
		GenerateVertexBufferData(segments);
		GenerateIndexBufferData(segments);
		GenerateLayout();

		geometryData.CreateVertexArray(planeVertexBufferData, segments * segments * 8 * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(planeIndexBufferData, (segments - 1) * (segments - 1) * 2 * 3);
	}
}