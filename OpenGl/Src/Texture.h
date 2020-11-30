#include "Renderer.h"
#include <string>

class Texture
{
private:
	unsigned int m_RendererId;
	const std::string& m_filePath;
	int m_height, m_width, m_BPP;
	unsigned char* m_LocalBuffer;

public:
	Texture(const std::string& Path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline float GetWidth() const { return m_width; }
	inline float GetHeight() const { return m_height; }
};