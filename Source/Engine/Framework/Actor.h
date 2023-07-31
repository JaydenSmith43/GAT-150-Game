#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include <memory>

namespace kiko
{
	class Actor //abstract
	{
	public:
		Actor() = default; // This automatically exists without typing

		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; } // bigger functions are less likely to be inlined
		virtual void OnCollision(Actor* other) {}

		void AddForce(const vec2& force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr; //forward declaration, also should probably be protected but isn't working
		friend class Scene;

		class Game* m_game = nullptr;

		kiko::Transform m_transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

	protected:
		bool m_destroyed = false;
		
		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};
}
