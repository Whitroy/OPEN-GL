#pragma once

#include "GL/glew.h"
class VertexBuffer
{
private:
	unsigned int m_renderer_id;

public:
	VertexBuffer(const void* data, unsigned int size,GLenum mode);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

};