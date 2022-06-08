#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class PlaneGeometry
	{
	private:
		std::vector<float>* planeVertexBufferData;
		std::vector<unsigned int>* planeIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(int segments);

		void GenerateIndexBufferData(int segments);

	public:
		PlaneGeometry(const unsigned int segments);
		~PlaneGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}