#include "IScene.h"

namespace scenes {

    IScene::IScene() :
        view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        camera(glm::radians(45.0f), (GLfloat)1080.0f / (GLfloat)1080.0f, 0.1f, 150.0f, view),
        gizmoShader("res/shaders/BasicColor.shader")
    {
    }

    void IScene::RenderGizmo(const Renderer & renderer, glm::mat4 newView) {
        gizmoShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        gizmoShader.SetUnifromMat4f("u_MVP", mvp);
        renderer.DrawLines(gizmo.GetVertexArray(), gizmo.GetIndexBuffer(), gizmoShader, 1.0f);
    }
}