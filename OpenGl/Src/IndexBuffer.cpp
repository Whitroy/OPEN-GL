#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const void* indices, unsigned int count) : m_count(count) {

    Assert(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_renderer_id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void IndexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id));
}

void IndexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
