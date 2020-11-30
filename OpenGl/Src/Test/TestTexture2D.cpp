#include "TestTexture2D.h"
#include "Renderer.h"
#include "im_gui/imgui.h"

namespace test {

	TestTexture2D::TestTexture2D()
		:m_Proj(glm::ortho(-8.0f, 8.0f, -3.0f, 3.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		m_Trans(0.0f, 0.0f, 0.0f),
		m_Rot(0.0f, 0.0f, 0.0f),
		m_Scale(1.0f, 1.0f, 1.0f)
	{
		float positions[] = {
			-0.5f, -0.5f,  0.0f, 0.0f,//0
			 0.5f, -0.5f,  1.0f, 0.0f,//1
			 0.5f,  0.5f,  1.0f, 1.0f,//2
			-0.5f,  0.5f,  0.0f, 1.0f//3
		};

		// indcies to draw square
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float),GL_STATIC_DRAW);

		//attrib pointer layout
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VBO, layout);

		//ibo
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		//shaders
		m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
		m_Shader->Bind();

		//for blending purpose
		//GLCall(glEnable(GL_BLEND));
		//GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));


		//texture
		m_Texture = std::make_unique<Texture>("res/textures/tex.jpeg");
		std::cout << "\n Texture 2D " << m_Shader->GetID() << std::endl;
		m_Texture->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D() {

	}

	void TestTexture2D::OnUpdate(float deltaTime) {

	}

	void TestTexture2D::OnRender() {

		GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		//shader.SetUniform4f("u_color", r, 0.3f, 0.2f, 0.5f);
		renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		
		glm::mat4 tranlatioMat = glm::translate(glm::mat4(1.0f), m_Trans);
		
		glm::mat4 ScaleMat = glm::scale(glm::mat4(1.0f), m_Scale);

		//glm::mat4 rotz = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
		//glm::mat4 rotx = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//glm::mat4 roty = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rot.y), glm::vec3(0.0f, 1.0f, 0.0f));

		//glm::mat4 rotMat = rotz * roty * rotx;

		glm::vec3 u(glm::radians(m_Rot));

		glm::quat Quaternion = glm::quat(u);

		glm::mat4 RotationMat = glm::toMat4(Quaternion);

		glm::mat4 model = tranlatioMat * RotationMat * ScaleMat;

		//glm::mat4 model = tranlatioMat * rotMat * ScaleMat;

		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("mvp", mvp);

	}

	void TestTexture2D::OnImGuiRender() {
		
		ImGui::Text("Translation");
		ImGui::SliderFloat3("Transform", &m_Trans.x,-8.0f,8.0f);
		ImGui::SliderFloat3("Scale", &m_Scale.x, -8.0f, 8.0f);
		ImGui::SliderFloat3("Rotation", &m_Rot.x, 0.0f , 360.0f);
	}
}