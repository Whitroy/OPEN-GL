#pragma once
class IndexBuffer
{
private:
	unsigned int m_renderer_id;
	unsigned int m_count;
public:
	IndexBuffer(const void* indices, unsigned int cout);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_count ; }
};