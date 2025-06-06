#pragma once

#include "Chill/Renderer/RenderCommand.h"

#include "Chill/Renderer/OrthographicCamera.h"
#include "Chill/Renderer/Shader.h"

namespace Chill {

	class Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void ResizeWindow(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};


}

