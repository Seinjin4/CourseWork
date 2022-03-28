#pragma once

#include "GeometryData.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	float vertexBufferData[100] = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };

	unsigned int indexBufferData[100] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	class BezierIntervalGeometry
	{
	private:
		GeometryData geometryData;
		VertexBufferLayout vbLayout;

		VertexBufferLayout GenerateLayout()
		{
			vbLayout.Push<float>(1);

			return vbLayout;
		}

		void GenerateVertexBufferData(int size)
		{
			for (int i = 0; i < size; i++)
			{
				vertexBufferData[i] = i * (1.0f / size);
			}
		}

		void GenerateIndexBufferData(int size)
		{
			for (int i = 0; i < size; i++)
			{
				indexBufferData[i] = i;
			}
		}


	public:
		BezierIntervalGeometry(const unsigned int size) {
			GenerateVertexBufferData(size);
			GenerateIndexBufferData(size);

			geometryData.CreateVertexArray(vertexBufferData, size * sizeof(float), GenerateLayout());
			geometryData.CreateIndexBuffer(indexBufferData, (const unsigned int) size);
		}

		const VertexArray& GetVertexArray() { return geometryData.GetVertexArray(); };
		const IndexBuffer& GetIndexBuffer() { return geometryData.GetIndexBuffer(); };
	};
}