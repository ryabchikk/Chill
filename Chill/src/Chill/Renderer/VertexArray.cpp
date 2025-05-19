#include "chpch.h"
#include "Chill/Renderer/VertexArray.h"

#include "Chill/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Chill {

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    CH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        CH_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
