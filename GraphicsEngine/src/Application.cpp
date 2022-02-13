#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"

#include "geometries/CubeGeometry.h"
#include "geometries/PlaneGeometry.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "cameras/Camera.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Graphics Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        geometry::CubeGeometry cube;

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (GLfloat)960.0f / (GLfloat)540.0f, 0.1f, 1500.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        camera::Camera camera(proj, view);

        Shader shader("res/shaders/NormalVisualization.shader");
        shader.Bind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::StyleColorsDark();

        glm::vec3 translation = glm::vec3(0.0f, 0.0f, -20.0f);
        glm::vec1 rotation = glm::vec1(0.0f);
        while (!glfwWindowShouldClose(window))
        {

            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
                glm::mat4 mvp = camera.GetProjectionView() * model;
                shader.SetUnifromMat4f("u_MVP", mvp);
                renderer.Draw(cube.GetVertexArray(), cube.GetIndexBuffer(), shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation) * glm::rotate(glm::mat4(1.0f), rotation.x, glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));
                glm::mat4 mvp = camera.GetProjectionView() * model;
                shader.SetUnifromMat4f("u_MVP", mvp);
                renderer.Draw(cube.GetVertexArray(), cube.GetIndexBuffer(), shader);
            }

            {
                ImGui::Begin("Panel");
                ImGui::SliderFloat3("TranslationA", &translation.x, -20.0f, 20.0f);
                ImGui::SliderFloat("Rotation", &rotation.x, -6.0f, 6.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glEnd();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}