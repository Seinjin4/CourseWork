#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class GizmoGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		void GenerateLayout();

	public:

		GizmoGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}