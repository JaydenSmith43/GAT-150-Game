#include "Hitbox.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Player.h"

namespace kiko
{
	CLASS_DEFINITION(Hitbox);

	bool Hitbox::Initialize()
	{
		Actor::Initialize();

		//m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		//m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Hitbox::Update(float dt)
	{
		Actor::Update(dt);
		timer -= dt;

		if (timer <= 0) destroyed = true;

		//kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		//Player* player = m_scene->GetActor<Player>();

	}

	void Hitbox::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
		}
	}

	void Hitbox::OnCollisionExit(Actor* other)
	{
		//if (other->tag == "Ground") groundCount--;
	}

	void Hitbox::Read(const json_t& value)
	{
		Actor::Read(value);

		//READ_DATA(value, speed);
		//READ_DATA(value, jump);
	}
}
