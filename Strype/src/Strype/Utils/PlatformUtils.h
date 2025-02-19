#pragma once

namespace Strype {

	class FileDialogs
	{
	public:
		static std::filesystem::path OpenFile(const char* filter);
		static std::filesystem::path SaveFile(const char* filter);
			   
		static std::filesystem::path OpenFolder();
	};

	class Time
	{
	public:
		static float GetTime();
	};

}