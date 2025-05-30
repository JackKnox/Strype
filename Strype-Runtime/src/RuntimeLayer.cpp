#include "RuntimeLayer.h"

namespace Strype {

	RuntimeLayer::RuntimeLayer(const std::filesystem::path& path)
	{
		//FileDialogs::OpenFile("Strype Project (.sproj)\0*.sproj\0")
		OpenProject(path);
		m_Room->StartRuntime();
	}

	RuntimeLayer::~RuntimeLayer()
	{
		m_Room->StopRuntime();
	}

	void RuntimeLayer::OnUpdate(Timestep ts)
	{
		m_Room->OnUpdate(ts);
	}

	void RuntimeLayer::OpenProject(const std::filesystem::path& path)
	{
		Ref<Project> project = CreateRef<Project>();
		ProjectSerializer serializer(project);
		serializer.Deserialize(path);

		Project::SetActive(project);

		m_Room = Project::GetAsset<Room>(Project::GetAssetHandle(project->GetStartRoom()));

	}

}