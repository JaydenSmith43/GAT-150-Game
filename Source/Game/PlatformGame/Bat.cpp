#include "Bat.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Enemy.h"

namespace kiko
{
	CLASS_DEFINITION(Bat);

	bool Bat::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Bat::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		Enemy* enemy = m_scene->GetActor<Enemy>();

		if (enemy && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_Q) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			//check if player is in front
			if (m_fireTimer <= 0.0f)
			{
				/*auto weapon = INSTANTIATE(Weapon, "Rocket")
				weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));*/
 				//g_renderer.DrawLine(this->transform.position.x, this->transform.position.y, enemy->transform.position.x, enemy->transform.position.y);

				//IF MORE TIME SHOOT "WEAPON" LASER THAT AUTO DELETES ITSELF

				m_fireTimer = m_fireRate;
			}
		}
		//m_fireTimer -= dt;
	}

	void Bat::OnCollisionEnter(Actor* other)
	{
		//if (other->tag == "Ground") groundCount++;
	}

	void Bat::OnCollisionExit(Actor* other)
	{
		//if (other->tag == "Ground") groundCount--;
	}

	void Bat::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}
