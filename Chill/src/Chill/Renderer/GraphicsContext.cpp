#include "chpch.h"
#include "Chill/Renderer/GraphicsContext.h"

#include "Chill/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Chill {

    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    CH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        CH_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}