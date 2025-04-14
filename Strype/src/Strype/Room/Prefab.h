#pragma once

#include "Object.h"

namespace Strype {

	class Prefab : public Asset
	{
	public:
		Prefab() = default;
		Prefab(const Prefab& other) = default;
		Prefab(entt::entity handle)
			: m_Object(handle, s_PrefabRoom.get())
		{
		}

		void ConnectObject(Object obj) { m_ConnectedObjects.emplace_back(obj); }
		std::vector<Object>& GetConnectedObjects() { return m_ConnectedObjects; }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) { return m_Object.AddComponent<T>(std::forward<Args>(args)...); }

		template<typename T>
		T& GetComponent() { return m_Object.GetComponent<T>(); }

		template<typename T>
		bool HasComponent() { return m_Object.HasComponent<T>(); }

		template<typename T>
		void RemoveComponent() { m_Object.RemoveComponent<T>(); }

		Object GetObject() { return m_Object; }
		void SetObject(Object obj) { m_Object = obj; }

		static AssetType GetStaticType() { return AssetType::Prefab; }
		virtual AssetType GetType() const override { return GetStaticType(); }
	private:
		Object m_Object;

		std::vector<Object> m_ConnectedObjects;
	};

}