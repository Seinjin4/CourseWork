#include "TubeTestScene.h"

std::vector<glm::vec3> scenes::TubeTestScene::generateCircularPoints(unsigned int pointCount)
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

scenes::TubeTestScene::TubeTestScene():
	tube(generateCircularPoints(30), 10, 0.03f, true),
	basicColorShader("res/shaders/ShadedColor.shader")
{
}

void scenes::TubeTestScene::RenderScene(const Renderer& renderer, glm::mat4 newView)
{
    glm::mat4& view = camera.GetView();
    view = newView;

    RenderGizmo(renderer, newView);

    {
        basicColorShader.Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = camera.GetProjectionView() * model;
        basicColorShader.SetUnifromMat4f("MVP", mvp);
        basicColorShader.SetUnifromVec3f("lightPos", glm::vec3(0.0f, 5.0f, 0.0f));
        basicColorShader.SetUnifromVec3f("viewPos", view[3]);
        basicColorShader.SetUnifromVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        basicColorShader.SetUnifromVec3f("objectColor", glm::vec3(0.55f, 0.55f, 0.55f));
        renderer.DrawTriangles(tube.GetVertexArray(), tube.GetIndexBuffer(), basicColorShader);
    }
}
