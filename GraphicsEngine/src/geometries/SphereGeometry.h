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
		std::vector<float>* sphereVertexBufferData;
		std::vector<unsigned int>* sphereIndexBufferData;

		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout();

		void GenerateVertexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments);

		void GenerateIndexBufferData(float ratio, unsigned int verticalSegments, unsigned int horizontalSegments);

	public:
		SphereGeometry(float ratio, unsigned int verticalSegments = 10, unsigned int horizontalSegments = 10);
		~SphereGeometry();

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}