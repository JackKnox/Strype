#pragma once

extern Strype::Application* Strype::CreateApplication();

int main(int argc, char** argv)
{
	Strype::Log::Init();

	STY_PROFILE_BEGIN_SESSION("Startup", "StrypeProfile-Startup.json");
	auto app = Strype::CreateApplication();
	STY_PROFILE_END_SESSION();

	STY_PROFILE_BEGIN_SESSION("Runtime", "StrypeProfile-Runtime.json");
	app->Run();
	STY_PROFILE_END_SESSION();
	
	STY_PROFILE_BEGIN_SESSION("Startup", "StrypeProfile-Shutdown.json");
	delete app;
	STY_PROFILE_END_SESSION();

	return 0;
}