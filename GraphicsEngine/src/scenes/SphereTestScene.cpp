#include "SphereTestScene.h"

namespace scenes
{
    SphereTestScene::SphereTestScene() :
        ShadedColor("res/shaders/ShadedColor.shader"),
        sphere(1.0f, 100, 100)
    {
    }

    void SphereTestScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;

        RenderGizmo(renderer, newView);

        {
            ShadedColor.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            ShadedColor.SetUnifromMat4f("MVP", mvp);
            ShadedColor.SetUnifromVec3f("lightPos", glm::vec3(0.0f, 5.0f, 0.0f));
            ShadedColor.SetUnifromVec3f("viewPos", view[3]);
            ShadedColor.SetUnifromVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            ShadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.55f, 0.55f, 0.55f));
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), ShadedColor);
        }
    }
}
