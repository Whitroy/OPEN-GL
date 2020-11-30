#pragma once
#include "test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test{
	
	class DynamicBatachRenderer : public Test
	{
	public:
		DynamicBatachRenderer();
		~DynamicBatachRenderer();
		
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:		
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_Tex1;
		std::unique_ptr<Texture> m_Tex2;

		glm::mat4 m_Proj;
		glm::mat4 m_View;

		glm::vec3 cameraMovement;
	};
}