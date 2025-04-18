#include "stypch.h"
#include "PrefabSerializer.h"

#include "Components.h"

#include "Strype/Utils/YamlHelpers.h"
#include "Strype/Project/Project.h"

#include <fstream>

namespace Strype {

	void PrefabSerializer::SaveAsset(Ref<Asset> asset, const std::filesystem::path& path)
	{
		//HACK: Assume asset is prefab 
		Prefab* prefab = (Prefab*)asset.get();

		YAML::Emitter out;
		out << YAML::BeginMap;
		{
			out << YAML::Key << "Prefab" << YAML::Value << YAML::BeginMap;

			if (prefab->HasComponent<SpriteRenderer>())
			{
				out << YAML::Key << "SpriteRenderer" << YAML::Value;
				out << YAML::BeginMap;

				SpriteRenderer& s = prefab->GetComponent<SpriteRenderer>();
				out << YAML::Key << "Colour" << YAML::Value << s.Colour;
				out << YAML::Key << "TexturePath" << YAML::Value << (s.Texture ? Project::GetFilePath(s.Texture) : "");

				out << YAML::EndMap;
			}

			if (prefab->HasComponent<ScriptComponent>())
			{
				out << YAML::Key << "ScriptComponent" << YAML::Value;
				out << YAML::BeginMap;

				ScriptComponent& sc = prefab->GetComponent<ScriptComponent>();
				out << YAML::Key << "ClassName" << YAML::Value << Project::GetScriptEngine()->GetScriptName(sc.ClassID);

				out << YAML::EndMap;
			}

			out << YAML::EndMap;
		}
		out << YAML::EndMap;
		std::ofstream fout(path);
		fout << out.c_str();
	}

	Ref<Asset> PrefabSerializer::LoadAsset(const std::filesystem::path& path)
	{
		Ref<Prefab> prefab = CreateRef<Prefab>();

		std::ifstream fstream(path);
		STY_CORE_ASSERT(fstream.is_open(), "Error opening file");

		std::stringstream stream;
		stream << fstream.rdbuf();

		YAML::Node data = YAML::Load(stream.str())["Prefab"];
		STY_CORE_ASSERT(data, "Could not load prefab")

		STY_CORE_TRACE("Deserializing prefab '{0}'", path.stem().string());

		Object newobj = s_PrefabRoom->CreateObject();
			
		YAML::Node sprite = data["SpriteRenderer"];
		if (sprite)
		{
			SpriteRenderer& src = newobj.AddComponent<SpriteRenderer>();
			src.Colour = sprite["Colour"].as<glm::vec4>();
		
			const std::filesystem::path& path = sprite["TexturePath"].as<std::filesystem::path>();
		
			if (!path.empty())
			{
				AssetHandle handle = Project::ImportAsset(path);
				src.Texture = handle;
			}
		}

		YAML::Node script = data["ScriptComponent"];
		if (script)
		{
			ScriptComponent& sc = newobj.AddComponent<ScriptComponent>();
			sc.ClassID = Project::GetScriptEngine()->GetIDByName(script["ClassName"].as<std::string>());
		}

		prefab->SetObject(newobj);

		return prefab;
	}

}


