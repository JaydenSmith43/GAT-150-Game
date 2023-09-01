#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Player.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		if (health <= 0)
		{
			kiko::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
			destroyed = true;
		}

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			//tranform.position
			kiko::vec2 direction = player->transform.position - (transform.position);
			if (direction.x != 0)
			{
				m_spriteAnimComponent->flipH = (direction.x > 0);
			}
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Hitbox")
		{
			health--;
		}
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		//if (other->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
