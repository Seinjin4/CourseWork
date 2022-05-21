#include "SphereGeometry.h"

namespace geometry
{
	float sphereVertexBufferData[100] = {
		 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 1.0f,  0.0f,  1.0f,  1.0f,  0.0f,  1.0f,
		 1.0f,  0.0f, -1.0f,  1.0f,  0.0f, -1.0f,
		-1.0f,  0.0f, -1.0f, -1.0f,  0.0f, -1.0f,
		-1.0f,  0.0f,  1.0f, -1.0f,  0.0f,  1.0f,

		 0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
	};

	unsigned int sphereIndexBufferData[100] = {
		0, 4, 1,
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,

		5, 1, 4,
		5, 2, 1,
		5, 3, 2,
		5, 4, 3,
	};

	VertexBufferLayout SphereGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);

		return vbLayout;
	}

	SphereGeometry::SphereGeometry() {
		GenerateLayout();

		geometryData.CreateVertexArray(sphereVertexBufferData, 36 * sizeof(float), vbLayout);
		geometryData.CreateIndexBuffer(sphereIndexBufferData, 24);

	}
}