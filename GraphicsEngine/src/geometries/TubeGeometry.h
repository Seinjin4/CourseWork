#pragma once

#include <array>

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class TubeGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(int segments);

		void GenerateIndexBufferData(std::vector<glm::vec3> path, int segments, bool loop);

	public:
		TubeGeometry(std::vector<glm::vec3> path, int segments, bool loop = false);

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}