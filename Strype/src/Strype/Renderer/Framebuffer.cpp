#include "stypch.h"
#include "Framebuffer.h"

#include "Strype/Renderer/Renderer.h"

#include "API/OpenGL/OpenGLFramebuffer.h"

namespace Strype {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    STY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		STY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
