#pragma once

#include "Strype/Core/Core.h"
#include <string>

namespace Strype {

	class Audio
	{
	protected:
		Audio() = default;
	public:
		Audio(const Audio&) = delete;
		Audio& operator=(const Audio&) = delete;

		inline static void Init() { return s_Instance->InitImpl(); }
		inline static void Shutdown() { return s_Instance->ShutdownImpl(); }

		inline static void PlaySound(std::string& filepath) { return s_Instance->PlaySoundImpl(filepath); }
	protected:
		virtual void PlaySoundImpl(std::string& filepath) = 0;

		virtual void InitImpl() = 0;
		virtual void ShutdownImpl() = 0;
	private:
		static Audio* s_Instance;
	};

}