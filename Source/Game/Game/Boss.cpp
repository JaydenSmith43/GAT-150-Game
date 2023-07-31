#pragma once
#include "Boss.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Renderer/ModelManager.h"

void Boss::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();

	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position; // could make a getter

		//turn towards player
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		m_transform.rotation += turnAngle * dt; // * 5

		//check if player is in front
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			if (m_fireTimer <= 0.0f)
			{
				kiko::Transform transform{ m_transform.position, m_transform.rotation, 2.0f };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, kiko::g_manager.Get("ship.txt"));
				weapon->m_tag = "Enemy";
				m_scene->Add(std::move(weapon));

				m_fireTimer = m_fireRate;
			}
		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (m_lifespan != -1.0f)
	{
		m_lifespan -= dt;
		m_destroyed = (m_lifespan <= 0);
	}

	m_fireTimer -= dt;

}

void Boss::OnCollision(Actor* other)
{
	//could also use a dynamic cast
	//Player* p = dynamic_cast<Player*>(other);

	if (other->m_tag == "Player" && m_destroyed != true)
	{
		health--;
		if (health == 0)
		{
			m_game->AddPoints(200);
			m_game->AddKills(3);
			m_destroyed = true;

			//create explosion
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 300;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = kiko::Color{ 0.96078431372f, 0.51372549019f, 0, 1 };

			kiko::Transform transform{ {m_transform.position.x, m_transform.position.y}, 0, 1 };
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
	}
}