#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Enemy : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)
		//Enemy(float speed, float turnRate, const kiko::Transform& transform) :
		//	Actor{ transform },
		//	m_speed{ speed },
		//	m_turnRate{ turnRate }
		//{
		//	m_fireRate = 2.0f;
		//	m_fireTimer = m_fireRate;
		//}
		bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	public:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		float health = 10;
	};
}
