#pragma once

#include "Strype/Project/Project.h"

#include "Strype/Core/UUID.h"
#include "Strype/Core/Hash.h"

#include "CSharpObject.h"

#include <Coral/HostInstance.hpp>
#include <Coral/Assembly.hpp>
#include <Coral/Type.hpp>

namespace Strype {

	using ScriptID = UUID;

	class ScriptEngine
	{
	public:
		ScriptEngine(Ref<Project> proj);
		~ScriptEngine();

		static void Initialize();
		static void Shutdown();

		template<typename... TArgs>
		CSharpObject CreateInstance(ScriptID type, TArgs&&... args)
		{
			auto* type = m_CachedTypes[type];
			auto instance = type->CreateInstance(std::forward<TArgs>(args)...);
			auto [index, handle] = m_ManagedObjects.Insert(std::move(instance));

			CSharpObject result;
			result.m_Handle = &handle;
			return result;
		}

		Coral::Type* GetTypeByName(const std::string& name)
		{
			return m_CachedTypes[Hash::GenerateFNVHash(name)];
		}
	private:
		void BuildTypeCache(const Ref<Coral::ManagedAssembly>& assembly);
	private:
		inline static std::unique_ptr<Coral::HostInstance> s_Host;
		inline static std::unique_ptr<Coral::AssemblyLoadContext> s_LoadContext;
		inline static Ref<Coral::ManagedAssembly> s_CoreAssembly;

		Coral::StableVector<Coral::ManagedObject> m_ManagedObjects;
		std::unordered_map<ScriptID, Coral::Type*> m_CachedTypes;
		Ref<Coral::ManagedAssembly> m_AppAssembly;
	};

}