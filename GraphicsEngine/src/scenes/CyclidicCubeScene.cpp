#include "CyclidicCubeScene.h"
#include <vendor/imgui/imgui.h>
#include <vendor/MathCalculations.h>

void scenes::CyclidicCubeScene::RenderCube(const Renderer& renderer)
{
    glm::vec3 staticSideColor = glm::vec3(0.0f, 0.42f, 0.46f);
    glm::vec3 dinamicSideColor = glm::vec3(0.51f, 0.77f, 0.74f);

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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", staticSideColor);
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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", staticSideColor);
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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", staticSideColor);
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    renderer.ToggleWireFrame(wireframeToggle);

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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", dinamicSideColor);
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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", dinamicSideColor);
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
        cyclideCubeSideShader.SetUnifromVec3f("objectColor", dinamicSideColor);
        renderer.DrawTriangles(plain.GetVertexArray(), plain.GetIndexBuffer(), cyclideCubeSideShader);
    }

    renderer.ToggleWireFrame(false);
}

void scenes::CyclidicCubeScene::RenderPoints(const Renderer& renderer)
{
    glm::vec3 pointBallSize = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 staticPointBallColor = glm::vec3(0.88f, 0.58f, 0.47f);
    glm::vec3 danamicPointBallColor = glm::vec3(0.92f, 0.96f, 0.97f);
    glm::vec3 calculatedPointBallColor = glm::vec3(0.51f, 0.86f, 0.43f);

    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p0), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", staticPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p1), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", staticPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p2), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", staticPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p3), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", danamicPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p4), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", staticPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p5), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", danamicPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p6), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", danamicPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
    {
        shadedColor.Bind();
        glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), p7), pointBallSize);
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", lightPos);
        shadedColor.SetUnifromVec3f("viewPos", viewPos);
        shadedColor.SetUnifromVec3f("lightColor", lightColor);
        shadedColor.SetUnifromVec3f("objectColor", calculatedPointBallColor);
        renderer.DrawTriangles(sphere.GetVertexArray(), sphere.GetIndexBuffer(), shadedColor);
    }
}

void scenes::CyclidicCubeScene::RenderCircles(const Renderer& renderer)
{
    glm::mat4 rotationMatrix;
    glm::mat4 translationMatrix;
    glm::mat4 scaleMatrix;
    glm::vec3 rotationAxis;
    float rotationAngle;
    mathCalc::CircleData circles[] = { sideA , sideB, sideC, sideD, sideE, sideF };

    for(int i = 0; i < 6; i++)
    {
        shadedColor.Bind();
        rotationAxis = glm::cross(circles[i].direction, glm::vec3(0.0f, 1.0f, 0.0f));
        
        if (glm::length(rotationAxis) == 0)
        {
            rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
            rotationAngle = 0.0f;
        }
        else
        {
            rotationAxis = glm::normalize(rotationAxis);
            rotationAngle = glm::acos(glm::dot(circles[i].direction, glm::vec3(0.0f, 1.0f, 0.0f)));
        }

        translationMatrix = glm::translate(glm::mat4(1.0f), circles[i].centerPosition);;

        rotationMatrix = glm::rotate(glm::mat4(1.0f), -rotationAngle, rotationAxis);

        float circleSizeDiff = circles[i].radius / 1.0f;

        scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(circleSizeDiff));

        glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
        glm::mat4 mvp = camera.GetProjectionView() * model;
        shadedColor.SetUnifromMat4f("MVP", mvp);
        shadedColor.SetUnifromVec3f("lightPos", glm::vec3(0.0f, 5.0f, 0.0f));
        shadedColor.SetUnifromVec3f("viewPos", view[3]);
        shadedColor.SetUnifromVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shadedColor.SetUnifromVec3f("objectColor", glm::vec3(0.55f, 0.55f, 0.55f));
        renderer.DrawTriangles(tube.GetVertexArray(), tube.GetIndexBuffer(), shadedColor);
    }
}

void scenes::CyclidicCubeScene::CalculatePoints()
{
    p6 = mathCalc::CalculatePointInCircle(sideA, (p6Slider * 0.99f + 0.25f) * glm::pi<float>());
    p3 = mathCalc::CalculatePointInCircle(sideB, (p3Slider * 0.99f - 0.249f) * glm::pi<float>());
    p5 = mathCalc::CalculatePointInCircle(sideC, (p5Slider * 0.99f - 0.75f) * glm::pi<float>());

    sideF = mathCalc::GetCircleDataFrom3Points(p1, p3, p5);
    sideE = mathCalc::GetCircleDataFrom3Points(p4, p6, p5);
    sideD = mathCalc::GetCircleDataFrom3Points(p2, p6, p3);

    mathCalc::Plane planeF = mathCalc::GetPlaneFromCircleData(sideF);
    mathCalc::Plane planeE = mathCalc::GetPlaneFromCircleData(sideE);
    mathCalc::Plane planeD = mathCalc::GetPlaneFromCircleData(sideD);

    p7 = mathCalc::IntersectionPointFrom3Planes(
        planeF,
        planeE,
        planeD
    );
}

scenes::CyclidicCubeScene::CyclidicCubeScene() :
    plain(30),
    sphere(1, 10, 10),
    tube(mathCalc::GenerateCircularPoints(30), 10, 0.02f, true),
    cyclideCubeSideShader("res/shaders/CyclideCubeSide.shader"),
    shadedColor("res/shaders/ShadedColor.shader"),
    p3Slider(0.505f),
    p5Slider(0.505f),
    p6Slider(0.505f),
    sideA(mathCalc::GetCircleDataFrom3Points(p0, p2, p4)),
    sideB(mathCalc::GetCircleDataFrom3Points(p0, p1, p2)),
    sideC(mathCalc::GetCircleDataFrom3Points(p0, p4, p1))
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

    CalculatePoints();

    if (cubeToggle)
    {
        RenderCube(renderer);
    }

    if (pointToggle)
    {
        RenderPoints(renderer);
    }

    if (circleToggle)
    {
        RenderCircles(renderer);
    }

    ImGui::Begin("Cyclidic Cube Controls");
    ImGui::SliderFloat("Point p3", &p3Slider, 0.0f, 1.0f);
    ImGui::SliderFloat("Point p5", &p5Slider, 0.0f, 1.0f);
    ImGui::SliderFloat("Point p6", &p6Slider, 0.0f, 1.0f);
    ImGui::Checkbox("Wireframe", &wireframeToggle);
    ImGui::Checkbox("Render points", &pointToggle);
    ImGui::Checkbox("Render cube", &cubeToggle);
    ImGui::Checkbox("Render circles", &circleToggle);
    ImGui::End();
}
