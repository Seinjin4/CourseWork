#pragma once

#include "Geometry.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace geometry
{
	const float planeVertexBufferData[24] =
	{
		// 1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		// 1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		//-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		//-1.0f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		// 1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		//-1.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	const unsigned int planeIndexBufferData[6] =
	{
		0,2,1,
		1,2,3
	};

	class PlaneGeometry : public Geometry
	{
	private:
		VertexBufferLayout GenerateLayout()
		{
			vbLayout.Push<float>(3);
			vbLayout.Push<float>(3);

			return vbLayout;
		}
	public:
		PlaneGeometry() :
			Geometry(
				planeVertexBufferData,
				4 * (6 * sizeof(float)),
				GenerateLayout(),
				planeIndexBufferData,
				(const unsigned int)6)
		{
		};
	};
}