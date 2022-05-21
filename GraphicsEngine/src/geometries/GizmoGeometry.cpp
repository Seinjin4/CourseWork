#include "GizmoGeometry.h"

namespace geometry {
	float gizmoVertexBufferData[216] =
	{
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};

	const unsigned int gizmoIndexBufferData[36] =
	{
		0, 1,
		2, 3,
		4, 5
	};

	void GizmoGeometry::GenerateLayout()
	{
		vbLayout.Push<float>(3);
		vbLayout.Push<float>(3);
	}

	GizmoGeometry::GizmoGeometry() {
		GenerateLayout();

		geometryData.CreateVertexArray(gizmoVertexBufferData, 6 * (6 * sizeof(float)), vbLayout);
		geometryData.CreateIndexBuffer(gizmoIndexBufferData, (const unsigned int)6);
	};
}