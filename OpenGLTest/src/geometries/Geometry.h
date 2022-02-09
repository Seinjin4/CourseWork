#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class Geometry
	{
	protected:
		VertexBuffer vb;
		VertexBufferLayout vbLayout;

		VertexArray vertexArray;
		IndexBuffer indexBuffer;


		Geometry(const float cubeVertexBufferData[], const unsigned int cubeVertexBufferDataSize, const VertexBufferLayout& layout, const unsigned int indices[], const unsigned int indicesSize)
			:
			vb(cubeVertexBufferData, cubeVertexBufferDataSize),
			vertexArray(vb, layout),
			indexBuffer(indices, indicesSize)
		{
			vbLayout = layout;
		};
		~Geometry()
		{
		}
	public:

		const VertexArray& GetVertexArray() { return vertexArray; };
		const IndexBuffer& GetIndexBuffer() { return indexBuffer; };
	};
}