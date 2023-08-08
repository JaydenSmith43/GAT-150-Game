#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>
#include "Components/Component.h"

namespace kiko
{
	class Actor //abstract
	{
	public:
		Actor() = default; // This automatically exists without typing

		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; } // bigger functions are less likely to be inlined //return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000;
		virtual void OnCollision(Actor* other) {}

		class Scene* m_scene = nullptr; //forward declaration, also should probably be protected but isn't working
		friend class Scene;

		class Game* m_game = nullptr;

		kiko::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get()); //tries to cast data to type provided
			if (result) return result; // if not nullptr
		}

		return nullptr;
	}
}
