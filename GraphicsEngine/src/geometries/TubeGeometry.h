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
		std::vector<float>* tubeVertexBufferData;
		std::vector<unsigned int>* tubeIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(const std::vector<glm::vec3>& path, int segments, float radius, bool loop);

		void GenerateIndexBufferData(int pathPartCount, int segments, bool loop);

	public:
		TubeGeometry(const std::vector<glm::vec3>& path, int segments, float radius, bool loop = false);
		~TubeGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}