#include "PerspectiveCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

camera::PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far, glm::mat4 view) :
	fov(fov),
	aspectRatio(aspectRatio),
	near(near),
	far(far),
	Camera(glm::perspective(fov, aspectRatio, near, far), view)
{
}

void camera::PerspectiveCamera::UpdateProjectionMatrix()
{
	projection = glm::perspective(fov, aspectRatio, near, far);
}