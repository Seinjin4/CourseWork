#include "GeometryData.h"

namespace geometry {
	void GeometryData::CreateVertexArray(
		const float cubeVertexBufferData[],
		const unsigned int cubeVertexBufferDataSize,
		const VertexBufferLayout& layout)
	{
		vb->Createbuffer(cubeVertexBufferData, cubeVertexBufferDataSize);
		vertexArray->AddBuffer(*vb, layout);
	}
	void GeometryData::CreateIndexBuffer(const unsigned int indices[], const unsigned int indicesSize)
	{
		indexBuffer->CreateBuffer(indices, indicesSize);
	}
}

