#include "BatchTexRendererTest.h"

namespace test {

	BatchTexRendererTest::BatchTexRendererTest() :
		m_Proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
	{
		float positions[] = {

			150.0f,  250.0f,   0.9f,  0.8f,  0.5f,  1.0f,   0.0f, 0.0f,   0.0f,
			400.0f,  250.0f,   0.9f,  0.8f,  0.5f,  1.0f,   1.0f, 0.0f,   0.0f,
			400.0f,  450.0f,   0.9f,  0.8f,  0.5f,  1.0f,   1.0f, 1.0f,   0.0f,
			150.0f,  450.0f,   0.9f,  0.8f,  0.5f,  1.0f,   0.0f, 1.0f,   0.0f,

			600.0f,  250.0f,   0.6f,  0.2f,  0.8f,  1.0f,   0.0f, 0.0f,   1.0f,
			950.0f,  250.0f,   0.6f,  0.2f,  0.8f,  1.0f,   1.0f, 0.0f,   1.0f,
			950.0f,  450.0f,   0.6f,  0.2f,  0.8f,  1.0f,   1.0f, 1.0f,   1.0f,
			600.0f,  450.0f,   0.6f,  0.2f,  0.8f,  1.0f,   0.0f, 1.0f,   1.0f
		};

		unsigned int indices[] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4
		};

		m_VBO = std::make_unique<VertexBuffer>(positions, 9 * 8 * sizeof(float), GL_STATIC_DRAW);
		m_VAO = std::make_unique<VertexArray>();

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(indices, 12);

		m_ShaderInstance = std::make_unique<Shader>("res/shaders/basicShader3.shader");

		m_Tex1 = std::make_unique<Texture>("res/textures/tex.jpeg");
		m_Tex2 = std::make_unique<Texture>("res/textures/tex2.png");
		
		m_Tex1->Bind();
		m_Tex2->Bind(1);

		int sampler[2] = { 0,1 };
		//std::cout << "\n Batch Texture " << m_ShaderInstance->GetID() << std::endl;
		m_ShaderInstance->Bind();
		//std::cout << "\n" << m_ShaderInstance->GetID() << std::endl;
		
		m_ShaderInstance->SetUniform1iv("u_textArr", 2, sampler);
		
		//m_ShaderInstance->SetUniform4f("c", 1.0f, 0.5f, 0.7f, 0.5f);
		//m_ShaderInstance->SetUniform1i("u_tex", 1);
		//std::cout << glGetUniformLocation(m_ShaderInstance->GetID(), "c");
		//std::cout << glGetUniformLocation(m_ShaderInstance->GetID(), "u_tex");
		//std::cout << glGetUniformLocation(m_ShaderInstance->GetID(), "u_textArr");
		//std::cout << glGetUniformLocation(m_ShaderInstance->GetID(), "c");
	}

	BatchTexRendererTest::~BatchTexRendererTest()
	{
	}

	void BatchTexRendererTest::OnUpdate(float deltaTime) {

	}


	void BatchTexRendererTest::OnRender() {

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		renderer.Draw(*m_VAO, *m_IBO, *m_ShaderInstance);

		glm::mat4 mvp = m_Proj * m_View;

		m_ShaderInstance->Bind();
		m_ShaderInstance->SetUniformMat4f("mvp", mvp);
	}

	void test::BatchTexRendererTest::OnImGuiRender() {

	}
}