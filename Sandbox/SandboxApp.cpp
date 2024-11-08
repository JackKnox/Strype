#include <Strype.h>

class ExampleLayer : public Strype::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Strype::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Strype::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Strype::VertexBuffer::Create(vertices, sizeof(vertices)));
		Strype::BufferLayout layout = {
			{ Strype::ShaderDataType::Float3, "a_Position" },
			{ Strype::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Strype::IndexBuffer> indexBuffer;
		indexBuffer.reset(Strype::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Strype::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Strype::VertexBuffer> squareVB;
		squareVB.reset(Strype::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Strype::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Strype::IndexBuffer> squareIB;
		squareIB.reset(Strype::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Strype::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Strype::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Strype::Timestep ts) override
	{
		if (Strype::Input::IsKeyPressed(STY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Strype::Input::IsKeyPressed(STY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Strype::Input::IsKeyPressed(STY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Strype::Input::IsKeyPressed(STY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Strype::Input::IsKeyPressed(STY_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Strype::Input::IsKeyPressed(STY_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Strype::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Strype::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Strype::Renderer::BeginScene(m_Camera);

		Strype::Renderer::Submit(m_BlueShader, m_SquareVA);
		Strype::Renderer::Submit(m_Shader, m_VertexArray);

		Strype::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Strype::Event& event) override
	{
	}
private:
	std::shared_ptr<Strype::Shader> m_Shader;
	std::shared_ptr<Strype::VertexArray> m_VertexArray;

	std::shared_ptr<Strype::Shader> m_BlueShader;
	std::shared_ptr<Strype::VertexArray> m_SquareVA;

	Strype::Camera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Strype::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Strype::Application* Strype::CreateApplication()
{
	return new Sandbox();
}