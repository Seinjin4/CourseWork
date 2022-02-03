#pragma once

#include "Geometry.h"
#include "VertexBufferLayout.h"

namespace geometry
{
	class CubeGeometry : public Geometry
	{
	private:
		// 3 - position, 3 - normal
		const float vertexBufferData[216] = 
		{
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,


			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,


			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,


			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,

			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,


			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,

			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,


			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,

			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		};

		const unsigned int indexBufferData[72] = 
		{
			 0,  1,  2,
		 	 3,  4,  5,

			 6,  7,  8,
			 9, 10, 11,


			12, 13, 14,
			15, 16, 17,

			18, 19, 20,
			21, 22, 23,


			24, 25, 26,
			27, 28, 29,

			30, 31, 32,
			33, 34, 35,


			36, 37, 38,
			39, 40, 41,

			42, 43, 44,
			45, 46, 47,


			48, 49, 50,
			51, 52, 53,

			54, 55, 56,
			57, 58, 59,


			60, 61, 62,
			63, 64, 65,

			66, 67, 68,
			69, 70, 71
		};

	public:
		CubeGeometry():
			Geometry(indexBufferData, 72)
		{
			VertexBuffer vb(vertexBufferData, 36 * (6 * sizeof(float)));
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			vertexArray.AddBuffer(vb, layout);
		};
	};
}