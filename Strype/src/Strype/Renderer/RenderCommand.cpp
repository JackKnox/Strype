#include "stypch.h"
#include "RenderCommand.h"

#include "API/OpenGL/OpenGLRendererAPI.h"

namespace Strype {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}