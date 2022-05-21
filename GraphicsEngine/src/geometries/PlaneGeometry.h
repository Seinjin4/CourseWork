#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class PlaneGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(int segments);

		void GenerateIndexBufferData(int segments);

	public:
		PlaneGeometry(const unsigned int segments);

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}