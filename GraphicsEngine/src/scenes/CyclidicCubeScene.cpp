#include "CyclidicCubeScene.h"
#include <vendor/imgui/imgui.h>

scenes::CyclidicCubeScene::CyclidicCubeScene() :
	plain(30),
	cyclideCubeSideShader("res/shaders/CyclideCubeSide.shader"),
    v1(-1.0f, 0.0f, 0.0f),
    v2(0.0f, 0.0f, -1.0f)
{
}

void scenes::CyclidicCubeScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
{
	glm::mat4& view = camera.GetView();
	view = newView;

    glm::vec3 viewPos = newView[3];
    glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, 8.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    RenderGizmo(renderer, newView);

    renderer.ToggleWireFrame(wireframeToggle);

    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", glm::vec3(0.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("p2", glm::vec3(1.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("p3", glm::vec3(0.0f, 0.0f, 1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("p4", glm::vec3(1.0f, 0.0f, 1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v1", v1);
        cyclideCubeSideShader.SetUnifromVec3f("v2", v2);
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    renderer.ToggleWireFrame(false);

    ImGui::Begin("Cyclidic Cube Controls");
    ImGui::SliderFloat3("v1", &v1.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("v2", &v2.x, -1.0f, 1.0f);
    //ImGui::SliderFloat("Point p3", &p3Slider, 0.0f, 1.0f);
    //ImGui::SliderFloat("Point p4", &p4Slider, 0.0f, 1.0f);
    //ImGui::SliderInt("Size", &size, -10, 10);
    //ImGui::SliderFloat("Angle", &angle, -5.0f, 5.0f);
    ImGui::Checkbox("Wireframe", &wireframeToggle);
    ImGui::End();
}
