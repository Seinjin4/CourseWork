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

void Renderer::Bind(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
}

void Renderer::DrawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    Bind(va, ib, shader);

    GLCall(glEnable(GL_CULL_FACE));
    //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

    EnableDepthTest();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const float lineWidth) const
{
    Bind(va, ib, shader);

    GLCall(glEnable(GL_CULL_FACE));

    EnableDepthTest();

    glLineWidth((GLfloat)lineWidth);

    GLCall(glDrawElements(GL_LINE_STRIP, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const float lineWidth) const
{
    Bind(va, ib, shader);

    GLCall(glEnable(GL_CULL_FACE));

    EnableDepthTest();

    glLineWidth((GLfloat)lineWidth);

    GLCall(glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::EnableDepthTest() const
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LEQUAL));
}