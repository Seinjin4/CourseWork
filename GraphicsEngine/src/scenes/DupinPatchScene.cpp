#include "DupinPatchScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    std::vector<glm::vec3> DupinPatchScene::generateCircularPoints(unsigned int pointCount)
    {
        std::vector<glm::vec3> points;

        for (size_t i = 0; i < pointCount; i++)
        {
            points.push_back(
                glm::vec3(
                    glm::cos(glm::pi<float>() * 2 * i / pointCount),
                    glm::sin(glm::pi<float>() * 2 * i / pointCount),
                    0
                ));
        }

        return points;   
    }

    DupinPatchScene::DupinPatchScene() :
        uvTestShader("res/shaders/UVTest.shader"),
        dupinPatchShader("res/shaders/DupinPatch.shader"),
        shadedColor("res/shaders/ShadedColor.shader"),
        tube(generateCircularPoints(50), 10, 0.02f, true),
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

        glm::vec3 viewPos = newView[3];
        glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        
        glm::vec3 pointBallSize = glm::vec3(0.05f, 0.05f, 0.05f);

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
            shadedColor.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            shadedColor.SetUnifromMat4f("MVP", mvp);
            shadedColor.SetUnifromVec3f("lightPos", lightPos);
            shadedColor.SetUnifromVec3f("viewPos", viewPos);
            shadedColor.SetUnifromVec3f("lightColor", lightColor);
            shadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.55f, 0.55f, 0.55f));
            renderer.DrawTriangles(tube.GetVertexArray(), tube.GetIndexBuffer(), shadedColor);
        }

        //{
        //    shadedColor.Bind();
        //    glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p1), pointBallSize);
        //    glm::mat4 mvp = camera.GetProjectionView() * model;
        //    shadedColor.SetUnifromMat4f("MVP", mvp);
        //    shadedColor.SetUnifromVec3f("lightPos", lightPos);
        //    shadedColor.SetUnifromVec3f("viewPos", viewPos);
        //    shadedColor.SetUnifromVec3f("lightColor", lightColor);
        //    shadedColor.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
        //    renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        //}

        //{
        //    shadedColor.Bind();
        //    glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p2), pointBallSize);
        //    glm::mat4 mvp = camera.GetProjectionView() * model;
        //    shadedColor.SetUnifromMat4f("MVP", mvp);
        //    shadedColor.SetUnifromVec3f("lightPos", lightPos);
        //    shadedColor.SetUnifromVec3f("viewPos", viewPos);
        //    shadedColor.SetUnifromVec3f("lightColor", lightColor);
        //    shadedColor.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
        //    renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        //}

        //{
        //    shadedColor.Bind();
        //    glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p3), pointBallSize);
        //    glm::mat4 mvp = camera.GetProjectionView() * model;
        //    shadedColor.SetUnifromMat4f("MVP", mvp);
        //    shadedColor.SetUnifromVec3f("lightPos", lightPos);
        //    shadedColor.SetUnifromVec3f("viewPos", viewPos);
        //    shadedColor.SetUnifromVec3f("lightColor", lightColor);
        //    shadedColor.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
        //    renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        //}

        //{
        //    shadedColor.Bind();
        //    glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p4), pointBallSize);
        //    glm::mat4 mvp = camera.GetProjectionView() * model;
        //    shadedColor.SetUnifromMat4f("MVP", mvp);
        //    shadedColor.SetUnifromVec3f("lightPos", lightPos);
        //    shadedColor.SetUnifromVec3f("viewPos", viewPos);
        //    shadedColor.SetUnifromVec3f("lightColor", lightColor);
        //    shadedColor.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
        //    renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        //}

        ImGui::Begin("Dupin Patch Controls");
        ImGui::SliderFloat("Point p1", &p1Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p2", &p2Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p3", &p3Slider, 0.0f, 1.0f);
        ImGui::SliderFloat("Point p4", &p4Slider, 0.0f, 1.0f);
        ImGui::SliderInt("Size", &size, -10, 10);
        ImGui::SliderFloat("AngleA", &angle, -5.0f, 5.0f);
        ImGui::End();
    }
}