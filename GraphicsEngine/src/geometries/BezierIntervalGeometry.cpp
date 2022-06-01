#include "BezierIntervalGeometry.h"

namespace geometry {
	VertexBufferLayout BezierIntervalGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(1);

		return vbLayout;
	}

	void BezierIntervalGeometry::GenerateVertexBufferData(int size)
	{
		for (int i = 0; i < size; i++)
		{
			intervalVertexBufferData->push_back(i * (1.0f / size));
		}
	}

	void BezierIntervalGeometry::GenerateIndexBufferData(int size)
	{
		for (int i = 0; i < size; i++)
		{
			intervalIndexBufferData->push_back(i);
		}
	}

	BezierIntervalGeometry::BezierIntervalGeometry(const unsigned int size) :
		intervalVertexBufferData(new std::vector<float>),
		intervalIndexBufferData(new std::vector<unsigned int>)
	{
		GenerateVertexBufferData(size);
		GenerateIndexBufferData(size);
		GenerateLayout();

		geometryData.CreateVertexArray(intervalVertexBufferData->data(), intervalVertexBufferData->size() * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(intervalIndexBufferData->data(), intervalVertexBufferData->size());
	}

	BezierIntervalGeometry::~BezierIntervalGeometry()
	{
		delete intervalVertexBufferData;
		delete intervalIndexBufferData;
	}
}