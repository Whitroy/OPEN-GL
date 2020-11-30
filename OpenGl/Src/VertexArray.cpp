#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {

    GLCall(glGenVertexArrays(1, &m_vao_id));
    GLCall(glBindVertexArray(m_vao_id));

}

VertexArray::~VertexArray(){

    GLCall(glDeleteVertexArrays(1, &m_vao_id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const {
	
    Bind();
	vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        //enable and set attribute pointer to tell the gpu what data is actually containing the array(positions,texture cor,normals,etc)
        GLCall(glEnableVertexAttribArray(i));
        //index is , size is no of element in each vertex,  stride is gap b/w ur vertices, pointer where to start for positon
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type
            , elements[i].normalized, layout.GetStride() , (const void*)offset));

        offset += elements[i].count * VertexBufferElement::GetSizeOfType(elements[i].type);
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_vao_id));
}

void VertexArray::UnBind() const {
    GLCall(glBindVertexArray(0));
}
