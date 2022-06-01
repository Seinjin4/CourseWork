#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class BezierIntervalGeometry
	{
	private:
		std::vector<float> *intervalVertexBufferData;
		std::vector<unsigned int> *intervalIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(int size);

		void GenerateIndexBufferData(int size);


	public:
		BezierIntervalGeometry(const unsigned int size);
		~BezierIntervalGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}