#include "stypch.hpp"
#include "RoomSerializer.hpp"

#include "Object.hpp"
#include "Prefab.hpp"
#include "Components.hpp"

#include "Strype/Utils/YamlHelpers.hpp"
#include "Strype/Project/Project.hpp"

#include <fstream>

namespace Strype {

	static void SerializeObject(Object obj, YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Object" << YAML::Value << (uint32_t)obj;

		if (PrefabComponent* p = obj.TryGetComponent<PrefabComponent>())
		{
			out << YAML::Key << "PrefabComponent";
			out << YAML::BeginMap;

			out << YAML::Key << "PrefabPath" << YAML::Value << Project::GetFilePath(p->Handle);

			out << YAML::EndMap;
		}

		if (Transform* t = obj.TryGetComponent<Transform>())
		{
			out << YAML::Key << "Transform";
			out << YAML::BeginMap;

			out << YAML::Key << "Position" << YAML::Value << t->Position;
			out << YAML::Key << "Scale" << YAML::Value << t->Scale;
			out << YAML::Key << "Rotation" << YAML::Value << t->Rotation;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void RoomSerializer::SaveAsset(Ref<Asset> asset, const std::filesystem::path& path)
	{
		//HACK: Assume asset is prefab 
		Room* room = (Room*)asset.get();

		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Room" << YAML::Value << YAML::BeginMap;

		out << YAML::Key << "Width" << YAML::Value << room->m_Width;
		out << YAML::Key << "Height" << YAML::Value << room->m_Height;
		out << YAML::Key << "BackgroundColour" << YAML::Value << room->m_BackgroundColour;

		out << YAML::Key << "Objects" << YAML::Value << YAML::BeginSeq;

		auto view = room->m_Registry.view<entt::entity>();
		for (entt::entity id : view)
		{
			Object obj{ id, room };

			SerializeObject(obj, out);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();
	}

	Ref<Asset> RoomSerializer::LoadAsset(const std::filesystem::path& path)
	{
		Ref<Room> room = CreateRef<Room>();

		std::ifstream fstream(path);
		STY_CORE_VERIFY(fstream.is_open(), "Error opening file");

		std::stringstream stream;
		stream << fstream.rdbuf();

		YAML::Node data = YAML::Load(stream.str())["Room"];

		STY_CORE_VERIFY(data, "Could not load room")
		STY_CORE_VERIFY(data["Objects"], "Could not load room");
		STY_CORE_VERIFY(data["BackgroundColour"], "Could not load room");

		YAML::Node width = data["Width"];
		YAML::Node height = data["Height"];
		if (width && height)
		{
			room->m_Width = data["Width"].as<uint64_t>();
			room->m_Height = data["Height"].as<uint64_t>();
		}

		room->m_BackgroundColour = data["BackgroundColour"].as<glm::vec3>();

		room->Clear();

		YAML::Node objects = data["Objects"];
		for (auto obj : objects)
		{
			uint32_t id = obj["Object"].as<uint32_t>();

			STY_CORE_VERIFY(obj["PrefabComponent"], "Object ({0}) is not a valid Strype Object", id);
			STY_CORE_VERIFY(obj["Transform"], "Object ({0}) is not a valid Strype Object", id);
			
			YAML::Node prefab = obj["PrefabComponent"];
			const std::filesystem::path& path = prefab["PrefabPath"].as<std::filesystem::path>();

			if (std::filesystem::exists(Project::GetProjectDirectory() / path))
			{
				AssetHandle handle = Project::ImportAsset(path);
				Object newobj = Object::Copy(Project::GetAsset<Prefab>(handle)->GetObject(), room);
				newobj.AddComponent<PrefabComponent>(handle);

				Project::GetAsset<Prefab>(handle)->ConnectObject(newobj);

				YAML::Node transform = obj["Transform"];
				if (transform)
				{
					Transform& tc = newobj.AddComponent<Transform>();

					tc.Position = transform["Position"].as<glm::vec2>();
					tc.Scale = transform["Scale"].as<glm::vec2>();
					tc.Rotation = transform["Rotation"].as<float>();
				}
			}
			else
			{
				STY_CORE_WARN("Could not find specifed path: \"{}\" ", path);
			}
		}
	
		return room;
	}

}