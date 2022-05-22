#include "DupinPatchScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    DupinPatchScene::DupinPatchScene() :
        uvTestShader("res/shaders/UVTest.shader"),
        dupinPatchShader("res/shaders/DupinPatch.shader"),
        plane(30),
        p1Slider(0.0f),
        p2Slider(0.25f),
        p3Slider(0.75f),
        p4Slider(0.5f),
        size(1),
        angle(1.0f)
    {
    }

    void DupinPatchScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;

        glm::vec3 p1(
            glm::cos(glm::radians(360.0f) * p1Slider),
            glm::sin(glm::radians(360.0f) * p1Slider),
            0.0f
        );

        glm::vec3 p2(
            glm::cos(glm::radians(360.0f) * p2Slider),
            glm::sin(glm::radians(360.0f) * p2Slider),
            0.0f
        );

        glm::vec3 p3(
            glm::cos(glm::radians(360.0f) * p3Slider),
            glm::sin(glm::radians(360.0f) * p3Slider),
            0.0f
        );

        glm::vec3 p4(
            glm::cos(glm::radians(360.0f) * p4Slider),
            glm::sin(glm::radians(360.0f) * p4Slider),
            0.0f
        );

        RenderGizmo(renderer, newView);

        {
            dupinPatchShader.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            dupinPatchShader.SetUnifromMat4f("MVP", mvp);
            dupinPatchShader.SetUnifromVec3f("p1", p1);
            dupinPatchShader.SetUnifromVec3f("p2", p2);
            dupinPatchShader.SetUnifromVec3f("p3", p3);
            dupinPatchShader.SetUnifromVec3f("p4", p4);
            dupinPatchShader.SetUnifrom1i("size", size);
            dupinPatchShader.SetUnifrom1f("angle", angle);
            renderer.DrawTriangles(plane.GetVertexArray(), plane.GetIndexBuffer(), dupinPatchShader);
        }

        {
            uvTestShader.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            uvTestShader.SetUnifromMat4f("MVP", mvp);
            //renderer.DrawTriangles(plane.GetVertexArray(), plane.GetIndexBuffer(), uvTestShader);
        }

        ImGui::Begin("Dupin Patch Controls");
        ImGui::SliderFloat("Point p1", &p1Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p2", &p2Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p3", &p3Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p4", &p4Slider, 0.0f, 1.0f);
        ImGui::SliderInt("Size", &size, -10, 10);
        ImGui::SliderFloat("Angle", &angle, -5.0f, 5.0f);
        ImGui::End();
    }
}