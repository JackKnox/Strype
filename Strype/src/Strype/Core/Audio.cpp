#include "stypch.h"
#include "Audio.h"

#ifdef STY_PLATFORM_WINDOWS
#	include "API/OpenAL/OpenALAudio.h"
#endif

namespace Strype {

	Scope<Audio> Audio::s_Instance = Audio::Create();

	Scope<Audio> Audio::Create()
	{
	#ifdef STY_PLATFORM_WINDOWS
		return CreateScope<OpenALAudio>();
	#else
		STY_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}