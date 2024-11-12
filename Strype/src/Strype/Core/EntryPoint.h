#pragma once

extern Strype::Application* Strype::CreateApplication();

int main(int argc, char** argv)
{
	Strype::Log::Init();
	STY_CORE_INFO("Initialized Log!");
	
	auto app = Strype::CreateApplication();
	app->Run();
	delete app;

	return 0;
}