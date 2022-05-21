#include "DupinPatchScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    DupinPatchScene::DupinPatchScene() :
        uvTest("res/shaders/UVTest.shader"),
        //dupin("res/shaders/dupin.shader"),
        p(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
        plane(30)
    {
    }

    void DupinPatchScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;

        RenderGizmo(renderer, newView);

        {
            uvTest.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            uvTest.SetUnifromMat4f("MVP", mvp);
            /*dupin.SetUnifrom3f("p", p.x, p.y, p.z);
            dupin.SetUnifrom1i("size", 6);
            dupin.SetUnifrom1f("angle", 1.0f);*/
            renderer.DrawTriangles(plane.GetVertexArray(), plane.GetIndexBuffer(), uvTest);
        }

        ImGui::Begin("Dupin Patch Controls");
        ImGui::SliderFloat3("p", &p.x, -2.0f, 2.0f);
        ImGui::End();
    }
}