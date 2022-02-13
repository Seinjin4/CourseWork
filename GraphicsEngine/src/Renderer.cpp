#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function << " " << file << ":" << line << std::endl; //search for the error code in glew.h
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    //shader.SetUnifrom4f("u_Color", 0.3f, 0.3f, 0.8f, 1.0f);
    va.Bind();
    ib.Bind();

    GLCall(glEnable(GL_CULL_FACE));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}