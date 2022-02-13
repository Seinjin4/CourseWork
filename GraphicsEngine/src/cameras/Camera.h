#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace camera
{
	class Camera
	{
	private:
		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera(glm::mat4 pMat, glm::mat4 vmat);

		glm::mat4 GetProjectionView();

		void SetView(glm::mat4 view);
	};
}