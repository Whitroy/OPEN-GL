#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size,GLenum mode) {
    
    GLCall(glGenBuffers(1, &m_renderer_id));
    //select buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
    //adding data to buffer as static
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, mode));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_renderer_id));
}

void VertexBuffer::Bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id));
}

void VertexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
