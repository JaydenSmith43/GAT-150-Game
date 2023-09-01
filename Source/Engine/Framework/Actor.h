#pragma once
#include "Object.h"

#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace kiko
{
	class Actor : public Object //Actor is abstract
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;

		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}

		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		//float GetRadius() { return 30.0f; } // bigger functions are less likely to be inlined //return (m_model) ? m_model->GetRadius() * transform.scale : -10000;
		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		class Scene* m_scene = nullptr; //forward declaration, also should probably be protected but isn't working
		friend class Scene;

		class Game* m_game = nullptr;



	public:
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;
	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get()); //tries to cast data to type provided
			if (result) return result; // if not nullptr
		}

		return nullptr;
	}
}
