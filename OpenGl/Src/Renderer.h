#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <GL/glew.h>

//debugging
#define Assert(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    Assert(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:

public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int count=0) const;
    void Clear() const;
};