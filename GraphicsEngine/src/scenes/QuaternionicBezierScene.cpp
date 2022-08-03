#include "QuaternionicBezierScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    QuaternionicBezierScene::QuaternionicBezierScene() :
        quaternionShader("res/shaders/QuaternionicBezier.shader"),
        shadedColor("res/shaders/ShadedColor.shader"),
        line(1000),
        sphere(1.0f,10, 10),
        u_q(0.0f, 1.0f, 0.0f, 0.0f),
        u_Pq0(1.0f, 0.0f, 0.0f, 0.0f),
        u_Pq1(-1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    void QuaternionicBezierScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;
        viewPos = newView[3];
        RenderGizmo(renderer, newView);

        {
            quaternionShader.Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            quaternionShader.SetUnifromMat4f("u_MVP", mvp);
            quaternionShader.SetUnifrom4f("Pq0", u_Pq0.x, u_Pq0.y, u_Pq0.z, u_Pq0.w);
            quaternionShader.SetUnifrom4f("Pq1", u_Pq1.x, u_Pq1.y, u_Pq1.z, u_Pq1.w);
            quaternionShader.SetUnifrom4f("Q", u_q.x, u_q.y, u_q.z, u_q.w);
            renderer.DrawLineStrip(line.GetVertexArray(), line.GetIndexBuffer(), quaternionShader, 10.0f);
        }

        glm::vec3 pointBallSize = glm::vec3(0.05f, 0.05f, 0.05f);

        {
            shadedColor.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_Pq0.x, u_Pq0.y, u_Pq0.z)), pointBallSize);
            glm::mat4 mvp = camera.GetProjectionView() * model;
            shadedColor.SetUnifromMat4f("MVP", mvp);
            shadedColor.SetUnifromVec3f("lightPos", lightPos);
            shadedColor.SetUnifromVec3f("viewPos", viewPos);
            shadedColor.SetUnifromVec3f("lightColor", lightColor);
            shadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.3f, 1.0f, 0.3f));
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        }

        {
            shadedColor.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_Pq1.x, u_Pq1.y, u_Pq1.z)), pointBallSize);
            glm::mat4 mvp = camera.GetProjectionView() * model;
            shadedColor.SetUnifromMat4f("MVP", mvp);
            shadedColor.SetUnifromVec3f("lightPos", lightPos);
            shadedColor.SetUnifromVec3f("viewPos", viewPos);
            shadedColor.SetUnifromVec3f("lightColor", lightColor);
            shadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.3f, 1.0f, 0.3f));
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        }

        {
            shadedColor.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_q.x, u_q.y, u_q.z)), pointBallSize);
            glm::mat4 mvp = camera.GetProjectionView() * model;
            shadedColor.SetUnifromMat4f("MVP", mvp);
            shadedColor.SetUnifromVec3f("lightPos", lightPos);
            shadedColor.SetUnifromVec3f("viewPos", viewPos);
            shadedColor.SetUnifromVec3f("lightColor", lightColor);
            shadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.3f, 0.3f, 1.0f));
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
        }

        ImGui::Begin("Quaternionic Bezier Controls");
        ImGui::SliderFloat3("P0", &u_Pq0.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("P1", &u_Pq1.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("Q", &u_q.x, -2.0f, 2.0f);
        ImGui::End();
    }
}

