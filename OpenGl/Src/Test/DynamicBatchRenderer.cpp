#include "DynamicBatchRenderer.h"
#include <array>
#include "im_gui/imgui.h"
namespace test {
	
	struct vec3
	{
		float x, y, z;
	};

	struct vec2
	{
		float x, y;
	};

	struct vec4
	{
		float x, y, z, w;
	};

	struct Vertex {
		vec3 Position;
		vec4 Color;
		vec2 TexCord;
		float TexIndex;
	};

	static const size_t MaxQuad = 1000;
	static const size_t MaxIndex = MaxQuad * 6;
	static const size_t MaxVertex = MaxQuad * 4;
	
	DynamicBatachRenderer::DynamicBatachRenderer()
		:
		m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1280.0f, -100.0f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		cameraMovement(0.0f, 0.0f, 0.0f)
	{
		uint32_t indices[MaxIndex];
		uint32_t offset = 0;
		for (size_t i = 0; i < MaxIndex; i+=6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		m_VBO = std::make_unique<VertexBuffer>(nullptr, MaxVertex * sizeof(Vertex), GL_DYNAMIC_DRAW);
		m_VAO = std::make_unique<VertexArray>();

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		m_VAO->AddBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<IndexBuffer>(indices, MaxIndex);

		m_shader = std::make_unique<Shader>("res/shaders/basicShader3.shader");

		m_Tex1 = std::make_unique<Texture>("res/textures/tex.jpeg");
		m_Tex2 = std::make_unique<Texture>("res/textures/tex2.png");

		m_Tex1->Bind();
		m_Tex2->Bind(1);

		int sampler[2] = { 0,1 };
		m_shader->Bind();
		m_shader->SetUniform1iv("u_textArr", 2, sampler);
	}

	DynamicBatachRenderer::~DynamicBatachRenderer()
	{
	}

	static Vertex* CreateQuad(Vertex* target ,float x, float y, float texId)
	{
		float size = 200.0f;
		
		target->Position = { x, y, 0.0f };
		target->Color = { 0.9f,  0.8f,  0.5f,  1.0f };
		target->TexCord = { 0.0f,0.0f };
		target->TexIndex = texId;
		target++;

		target->Position = { x+size, y, 0.0f };
		target->Color = { 0.9f,  0.8f,  0.5f,  1.0f };
		target->TexCord = { 1.0f, 0.0f };
		target->TexIndex = texId;
		target++;

		target->Position = { x+size,  y+size, 0.0f };
		target->Color = { 0.9f,  0.8f,  0.5f,  1.0f };
		target->TexCord = { 1.0f, 1.0f };
		target->TexIndex = texId;
		target++;

		target->Position = { x,  y+size, 0.0f };
		target->Color = { 0.9f,  0.8f,  0.5f,  1.0f };
		target->TexCord = { 0.0f, 1.0f };
		target->TexIndex = texId;
		target++;

		return target;
	}

	void DynamicBatachRenderer::OnUpdate(float deltaTime) {
		//set dynamic vertex buffer

		//auto q0 = CreateQuad(150.0f, 250.0f, 0.0f);
		//auto q1 = CreateQuad(400.0f, 250.0f, 1.0f);
		
		std::array<Vertex,1000> positions;
		uint32_t indexcounter = 0;
		Vertex* buffer = positions.data();
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				buffer = CreateQuad(buffer, i*200 , j*200 , (float)((i + j) % 2));
				indexcounter += 6;
			}
		}
		//memcpy(positions, q0.data(), q0.size() * sizeof(Vertex));
		//memcpy(positions + 4, q1.data(), q1.size() * sizeof(Vertex));
		m_VBO->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(Vertex), positions.data());

		Renderer renderer;
		renderer.Draw(*m_VAO, *m_IBO, *m_shader, indexcounter);
	}

	void DynamicBatachRenderer::OnRender() {

		GLCall(glClearColor(0.0f, 0.26f, 0.41f, 0.5f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_shader->Bind();
		m_View = glm::translate(glm::mat4(1.0f), cameraMovement);
		glm::mat4 mvp = m_Proj * m_View;
		m_shader->SetUniformMat4f("mvp", mvp);
	}

	void test::DynamicBatachRenderer::OnImGuiRender() {

		ImGui::SliderFloat3("Camera", &cameraMovement.x, -1280.0f, 1280.0f);
	}
}