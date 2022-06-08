#include "CyclidicCubeScene.h"
#include <vendor/imgui/imgui.h>
#include <vendor/MathCalculations.h>

scenes::CyclidicCubeScene::CyclidicCubeScene() :
    plain(30),
    cyclideCubeSideShader("res/shaders/CyclideCubeSide.shader"),
    v1(-1.0f, 0.0f, 0.0f),
    v2(0.0f, 0.0f, -1.0f),
    p3Slider(0.126f),
    p5Slider(0.874f),
    p6Slider(0.374f)
{
}

void scenes::CyclidicCubeScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
{
	glm::mat4& view = camera.GetView();
	view = newView;

    glm::vec3 viewPos = newView[3];
    glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 16.0f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    RenderGizmo(renderer, newView);


    mathCalc::CircleData sideA = mathCalc::GetCircleDataFrom3Points(p0, p2, p4);
    mathCalc::CircleData sideB = mathCalc::GetCircleDataFrom3Points(p0, p1, p2);
    mathCalc::CircleData sideC = mathCalc::GetCircleDataFrom3Points(p0, p4, p1);

    p6 = mathCalc::CalculatePointInCircle(sideA, p6Slider * glm::pi<float>() * 2);
    p3 = mathCalc::CalculatePointInCircle(sideB, p3Slider * glm::pi<float>() * 2);
    p5 = mathCalc::CalculatePointInCircle(sideC, p5Slider * glm::pi<float>() * 2);

    mathCalc::CircleData sideF = mathCalc::GetCircleDataFrom3Points(p1, p3, p5);
    mathCalc::CircleData sideE = mathCalc::GetCircleDataFrom3Points(p4, p5, p6);
    mathCalc::CircleData sideD = mathCalc::GetCircleDataFrom3Points(p2, p3, p6);

    mathCalc::Plane planeF = mathCalc::GetPlaneFromCircleData(sideF);
    mathCalc::Plane planeE = mathCalc::GetPlaneFromCircleData(sideE);
    mathCalc::Plane planeD = mathCalc::GetPlaneFromCircleData(sideD);

    p7 = mathCalc::IntersectionPointFrom3Planes(
        planeF,
        planeE,
        planeD
    );

    renderer.ToggleWireFrame(wireframeToggle);

    //Side A
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p0);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p4);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p2);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p6);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(0.0f, -1.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(-1.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    //Side B
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p0);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p2);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p1);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p3);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(-1.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(0.0f, 0.0f, -1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    //Side C
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p0);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p1);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p4);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p5);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(0.0f, 0.0f, -1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(0.0f, -1.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    //Side D
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p2);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p3);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p6);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p7);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(0.0f, 0.0f, -1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(0.0f, -1.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    //Side E
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p4);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p6);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p5);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p7);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(-1.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(0.0f, 0.0f, -1.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    //Side F
    {
        cyclideCubeSideShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        cyclideCubeSideShader.SetUnifromMat4f("MVP", mvp);
        cyclideCubeSideShader.SetUnifromVec3f("p1", p1);
        cyclideCubeSideShader.SetUnifromVec3f("p2", p3);
        cyclideCubeSideShader.SetUnifromVec3f("p3", p5);
        cyclideCubeSideShader.SetUnifromVec3f("p4", p7);
        cyclideCubeSideShader.SetUnifromVec3f("v1", glm::vec3(-1.0f, 0.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("v2", glm::vec3(0.0f, -1.0f, 0.0f));
        cyclideCubeSideShader.SetUnifromVec3f("lightPos", lightPos);
        cyclideCubeSideShader.SetUnifromVec3f("viewPos", viewPos);
        cyclideCubeSideShader.SetUnifromVec3f("lightColor", lightColor);
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", glm::vec3(1.0f, 0.3f, 1.0f));
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    renderer.ToggleWireFrame(false);

    ImGui::Begin("Cyclidic Cube Controls");
    //ImGui::SliderFloat3("v1", &v1.x, -1.0f, 1.0f);
    //ImGui::SliderFloat3("v2", &v2.x, -1.0f, 1.0f);
    ImGui::SliderFloat("Point p3", &p3Slider, 0.0f, 1.0f);
    ImGui::SliderFloat("Point p5", &p5Slider, 0.0f, 1.0f);
    ImGui::SliderFloat("Point p6", &p6Slider, 0.0f, 1.0f);
    //ImGui::SliderFloat("Point p4", &p4Slider, 0.0f, 1.0f);
    //ImGui::SliderInt("Size", &size, -10, 10);
    //ImGui::SliderFloat("Angle", &angle, -5.0f, 5.0f);
    ImGui::Checkbox("Wireframe", &wireframeToggle);
    ImGui::End();
}
