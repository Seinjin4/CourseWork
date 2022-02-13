#include "Camera.h"

camera::Camera::Camera(glm::mat4 pMat, glm::mat4 vmat)
	: projection(pMat), view(vmat)
{}

glm::mat4 camera::Camera::GetProjectionView()
{
	return projection * view;
}

void camera::Camera::SetView(glm::mat4 view)
{
}
