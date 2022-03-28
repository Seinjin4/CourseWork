#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class GeometryData
	{
	private:
		VertexBuffer* vb;

		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;

	public:
		GeometryData() {
			vb = new VertexBuffer();
			vertexArray = new VertexArray();
			indexBuffer = new IndexBuffer();
		};

		~GeometryData()
		{
			delete vb;
			delete vertexArray;
			delete indexBuffer;
		}

		void CreateVertexArray (
			const float cubeVertexBufferData[],
			const unsigned int cubeVertexBufferDataSize,
			const VertexBufferLayout& layout
		);

		void CreateIndexBuffer (
			const unsigned int indices[],
			const unsigned int indicesSize
		);

		const VertexArray& GetVertexArray() { return *vertexArray; };
		const IndexBuffer& GetIndexBuffer() { return *indexBuffer; };
	};
}