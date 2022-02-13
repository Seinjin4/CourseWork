#pragma once

#include "Camera.h"


namespace camera
{
	class PerspectiveCamera : public Camera
	{
	private:
		float near;
		float far;
		float fov; //in radians
		float aspectRatio;

	public:
		PerspectiveCamera(const float fov,const float aspectRatio,const float near,const float far,const glm::mat4 view);
		PerspectiveCamera(const PerspectiveCamera&) = delete;

		void UpdateProjectionMatrix();

		inline float& GetNear() { return near; }
		inline float& GetFar()  { return far; }
		inline float& GetFov()  { return fov; }
		inline float& GetAspectRatio()  { return aspectRatio; }
	};
}