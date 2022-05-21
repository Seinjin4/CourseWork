#pragma once
#include <Renderer.h>
#include "cameras/PerspectiveCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "geometries/GizmoGeometry.h"

namespace scenes
{
    class IScene {
    protected:
        glm::mat4 view;
        camera::PerspectiveCamera camera;

        Shader gizmoShader;

        geometry::GizmoGeometry gizmo;

        IScene();

        void RenderGizmo(const Renderer& renderer, glm::mat4 newView);
    public:
        virtual void RenderScene(const Renderer& renderer, glm::mat4 newView) = 0;
    };
}