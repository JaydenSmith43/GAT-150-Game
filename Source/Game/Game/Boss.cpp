//#pragma once
//#include "Boss.h"
//#include "Player.h"
//#include "SpaceGame.h"
//#include "Framework/Scene.h"
//#include "Framework/Emitter.h"
//#include "Renderer/Renderer.h"
//#include "Weapon.h"

//void Boss::Update(float dt)
//{
//	Actor::Update(dt);
//
//	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
//	Player* player = m_scene->GetActor<Player>();
//
//	if (player)
//	{
//		kiko::Vector2 direction = player->transform.position - transform.position; // could make a getter
//
//		//turn towards player
//		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
//		transform.rotation += turnAngle * dt; // * 5
//
//		//check if player is in front
//		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
//		{
//			if (m_fireTimer <= 0.0f)
//			{
//				//kiko::Transform m_transform{ transform.position, transform.rotation, 2.0f };
//				//std::unique_ptr<WeaponComponent> weapon = std::make_unique<WeaponComponent>(400.0f, transform); //kiko::g_manager.Get("ship.txt")
//				//weapon->tag = "Enemy";
//				//m_scene->Add(std::move(weapon));
//
//				//m_fireTimer = m_fireRate;
//			}
//		}
//	}
//
//	transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
//	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
//	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());
//
//	if (lifespan != -1.0f)
//	{
//		lifespan -= dt;
//		destroyed = (lifespan <= 0);
//	}
//
//	m_fireTimer -= dt;
//
//}
//
//void Boss::OnCollisionEnter(Actor* other)
//{
//	//could also use a dynamic cast
//	//Player* p = dynamic_cast<Player*>(other);
//
//	if (other->tag == "Player" && destroyed != true)
//	{
//		health--;
//		if (health == 0)
//		{
//			m_game->AddPoints(200);
//			m_game->AddKills(3);
//			destroyed = true;
//
//			//create explosion
//			kiko::EmitterData data;
//			data.burst = true;
//			data.burstCount = 100;
//			data.spawnRate = 300;
//			data.angle = 0;
//			data.angleRange = kiko::Pi;
//			data.lifetimeMin = 0.5f;
//			data.lifetimeMin = 1.5f;
//			data.speedMin = 50;
//			data.speedMax = 250;
//			data.damping = 0.5f;
//
//			data.color = kiko::Color{ 0.96078431372f, 0.51372549019f, 0, 1 };
//
//			kiko::Transform m_transform{ {transform.position.x, transform.position.y}, 0, 1 };
//			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
//			emitter->lifespan = 1.0f;
//			m_scene->Add(std::move(emitter));
//		}
//	}
//}