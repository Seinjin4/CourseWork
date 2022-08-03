#include "PlaneTestScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    PlaneTestScene::PlaneTestScene() :
        singularityTexture("res/shaders/SingularityTexture.shader"),
        plane(30),
        uvTest("res/shaders/UVTest.shader")
    {
    }

    void PlaneTestScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;

        float UvScale = 50.0f;

        RenderGizmo(renderer, newView);

        {
            singularityTexture.Bind();
            glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(UvScale, UvScale, UvScale));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            singularityTexture.SetUnifromMat4f("MVP", mvp);
            singularityTexture.SetUnifrom1f("UvScale", UvScale);
            singularityTexture.SetUnifrom1f("a", a);
            singularityTexture.SetUnifrom1f("b", b);
            singularityTexture.SetUnifrom1f("c", c);
            renderer.DrawTriangles(plane.GetVertexArray(), plane.GetIndexBuffer(), singularityTexture);
        }

        ImGui::Begin("Plane Test Controls");
        ImGui::SliderFloat("Mag", &mag, 0.0f, 1.0f);
        ImGui::SliderFloat("a", &a, 0.0f, 1.0f);
        ImGui::SliderFloat("b", &b, 0.0f, 1.0f);
        ImGui::SliderFloat("c", &c, 0.0f, 1.0f);
        ImGui::End();
    }
}