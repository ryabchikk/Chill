#include "chpch.h"
#include "RenderCommand.h"

#include "Chill/Renderer/RenderCommand.h"

namespace Chill 
{

    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
