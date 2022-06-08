#include "PlaneGeometry.h"

namespace geometry
{
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
				planeVertexBufferData->push_back( - 1 + 2 / static_cast<float>(segments - 1) * x);
				planeVertexBufferData->push_back(0);
				planeVertexBufferData->push_back(-1 + 2 / static_cast<float>(segments - 1) * y);

				//normal
				planeVertexBufferData->push_back(0);
				planeVertexBufferData->push_back(1);
				planeVertexBufferData->push_back(0);

				//UV
				planeVertexBufferData->push_back(0 + 1 / static_cast<float>(segments - 1) * x);
				planeVertexBufferData->push_back(0 + 1 / static_cast<float>(segments - 1) * y);
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
				planeIndexBufferData->push_back(y * segments + x);
				planeIndexBufferData->push_back((y + 1) * segments + x);
				planeIndexBufferData->push_back(y * segments + x + 1);
				polygonCount++;

				//second quad polygon
				planeIndexBufferData->push_back((y + 1) * segments + x);
				planeIndexBufferData->push_back((y + 1) * segments + x + 1);
				planeIndexBufferData->push_back(y * segments + x + 1);
				polygonCount++;
			}
		}
	}

	PlaneGeometry::PlaneGeometry(const unsigned int segments):
		planeVertexBufferData(new std::vector<float>),
		planeIndexBufferData(new std::vector<unsigned int>)
	{
		GenerateVertexBufferData(segments);
		GenerateIndexBufferData(segments);
		GenerateLayout();

		geometryData.CreateVertexArray(planeVertexBufferData->data(), planeVertexBufferData->size() * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(planeIndexBufferData->data(), planeIndexBufferData->size());
	}
	PlaneGeometry::~PlaneGeometry()
	{
		delete planeVertexBufferData;
		delete planeIndexBufferData;
	}
}