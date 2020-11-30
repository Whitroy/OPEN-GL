#include "BatchRendererTest.h"
#include "im_gui/imgui.h"

namespace test {

	BatchRendererTest::BatchRendererTest() :
		m_Proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -100.0f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		cameraMovement(0.0f, 0.0f, 0.0f)
	{
		float positions[] = {

			150.0f,  250.0f,    0.2f,  0.8f,  0.5f,  1.0f,
			400.0f, 250.0f,    0.2f,  0.8f,  0.5f,  1.0f,
			400.0f, 450.0f,   0.2f,  0.8f,  0.5f,  1.0f,
			150.0f,  450.0f,   0.2f,  0.8f,  0.5f,  1.0f,

			600.0f,  250.0f,   0.6f,  0.2f,  0.8f,  1.0f,
			950.0f,  250.0f,   0.6f,  0.2f,  0.8f,  1.0f,
			950.0f,  450.0f,  0.6f,  0.2f,  0.8f,  1.0f,
			600.0f,  450.0f,  0.6f,  0.2f,  0.8f,  1.0f
		};

		unsigned int indices[] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4
		};

		m_VBO = std::make_unique<VertexBuffer>(positions, 6 * 8 * sizeof(float), GL_STATIC_DRAW);
		m_VAO = std::make_unique<VertexArray>();

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(4);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(indices, 12);

		m_shader = std::make_unique<Shader>("res/shaders/basicShader2.shader");
		std::cout << "\n Batch Color " << m_shader->GetID() << std::endl;
		m_shader->Bind();
	}

	BatchRendererTest::~BatchRendererTest()
	{
	}

	void BatchRendererTest::OnUpdate(float deltaTime) {

	}


	void BatchRendererTest::OnRender() {

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		renderer.Draw(*m_VAO, *m_IBO, *m_shader);
		m_View = glm::translate(glm::mat4(1.0f), cameraMovement);
		glm::mat4 mvp = m_Proj * m_View;

		m_shader->Bind();
		m_shader->SetUniformMat4f("mvp", mvp);
	}

	void test::BatchRendererTest::OnImGuiRender() {

		ImGui::SliderFloat3("Camera", &cameraMovement.x, -90.0f, 90.0f);
	}
}