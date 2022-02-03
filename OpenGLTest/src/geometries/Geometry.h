#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"

namespace geometry
{
	class Geometry
	{
	protected:
		VertexArray vertexArray;
		IndexBuffer indexBuffer;

		Geometry(const unsigned int indexBufferData[], const unsigned int indexBufferDataSize) :
			vertexArray(), indexBuffer(indexBufferData, indexBufferDataSize)
		{ 
		};
	public:

		inline const VertexArray GetVertexArray() { return vertexArray; };
		inline const IndexBuffer GetIndexBuffer() { return indexBuffer; };
	};
}