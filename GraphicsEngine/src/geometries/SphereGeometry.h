#pragma once

#include <array>

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class SphereGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

	public:
		SphereGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}