#include "BezierIntervalGeometry.h"

namespace geometry {
	float intervalVertexBufferData[100] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };

	unsigned int intervalIndexBufferData[100] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	VertexBufferLayout BezierIntervalGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(1);

		return vbLayout;
	}

	void BezierIntervalGeometry::GenerateVertexBufferData(int size)
	{
		for (int i = 0; i < size; i++)
		{
			intervalVertexBufferData[i] = i * (1.0f / size);
		}
	}

	void BezierIntervalGeometry::GenerateIndexBufferData(int size)
	{
		for (int i = 0; i < size; i++)
		{
			intervalIndexBufferData[i] = i;
		}
	}

	BezierIntervalGeometry::BezierIntervalGeometry(const unsigned int size) {
		GenerateVertexBufferData(size);
		GenerateIndexBufferData(size);
		GenerateLayout();

		geometryData.CreateVertexArray(intervalVertexBufferData, size * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(intervalIndexBufferData, size);
	}
}