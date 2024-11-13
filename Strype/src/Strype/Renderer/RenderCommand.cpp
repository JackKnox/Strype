#include "stypch.h"
#include "RenderCommand.h"

#include "API/OpenGL/OpenGLRendererAPI.h"

namespace Strype {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}