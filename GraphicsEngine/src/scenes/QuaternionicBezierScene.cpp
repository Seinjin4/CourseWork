#include "QuaternionicBezierScene.h"
#include <vendor/imgui/imgui.h>

namespace scenes
{
    QuaternionicBezierScene::QuaternionicBezierScene() :
        quaternionShader("res/shaders/QuaternionicBezier.shader"),
        normalVisualization("res/shaders/NormalVisualization.shader"),
        line(90),
        u_q(0.0f, 1.0f, 0.0f, 0.0f),
        u_Pq0(1.0f, 0.0f, 0.0f, 0.0f),
        u_Pq1(-1.0f, 0.0f, 0.0f, 0.0f)
    {
    }

    void QuaternionicBezierScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
    {
        glm::mat4& view = camera.GetView();
        view = newView;

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

        {
            normalVisualization.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_Pq0.x, u_Pq0.y, u_Pq0.z)), glm::vec3(0.02f, 0.02f, 0.02f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            normalVisualization.SetUnifromMat4f("u_MVP", mvp);
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), normalVisualization);
        }

        {
            normalVisualization.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_Pq1.x, u_Pq1.y, u_Pq1.z)), glm::vec3(0.02f, 0.02f, 0.02f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            normalVisualization.SetUnifromMat4f("u_MVP", mvp);
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), normalVisualization);
        }

        {
            normalVisualization.Bind();
            glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(u_q.x, u_q.y, u_q.z)), glm::vec3(0.02f, 0.02f, 0.02f));
            glm::mat4 mvp = camera.GetProjectionView() * model;
            normalVisualization.SetUnifromMat4f("u_MVP", mvp);
            renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), normalVisualization);
        }

        ImGui::Begin("Quaternionic Bezier Controls");
        ImGui::SliderFloat3("P0", &u_Pq0.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("P1", &u_Pq1.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("Q", &u_q.x, -2.0f, 2.0f);
        ImGui::End();
    }
}

