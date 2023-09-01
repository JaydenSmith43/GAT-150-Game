#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Hitbox.h"

namespace kiko
{
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();
		defaultJump = jump;

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		float dir = 0;
		bool onGround = (groundCount > 0);

		vec2 velocity = m_physicsComponent->m_velocity;

		if (attackTimerActive) attackTimer -= dt;
		if (hurtTimerActive) hurtTimer -= dt;

		switch (m_state)
		{
		case playerState::Hurt:
			velocity.x += (speed / 4) * facing;
			velocity.x = Clamp(velocity.x, -maxSpeed / 2, maxSpeed / 2);
			m_physicsComponent->SetVelocity(velocity);

			

			if (hurtTimer <= 0)
			{
				hurtTimerActive = false;
				hurtTimer = 1;
				m_state = playerState::Idle;
			}

			break;

		case playerState::Attack:
			if (attackTimer <= 0)
			{
				attackTimerActive = false;
				attackTimer = 1;
				m_state = playerState::Idle;
			}
			break;

		case playerState::Crouch:
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A))
			{
				dir = -1; 
				facing = 1;
			}
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D))
			{
				dir = 1; 
				facing = -1;
			}
			if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);

			if (onGround && !kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S))
			{
				m_state = playerState::Idle;
			}

			break;

		case playerState::Idle:
			//movement
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A))
			{
				dir = -1;
				facing = 1;
			}
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D))
			{
				dir = 1;
				facing = -1;
			}

			if (dir)
			{
				//kiko::vec2 forward = kiko::vec2{ 1, 0 };
				velocity.x += speed * dir * ((onGround) ? 1 : 0.5f) * dt;
				velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
				m_physicsComponent->SetVelocity(velocity);

				//m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.25f));
			}

			// jump
			if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			{
				kiko::vec2 up = kiko::vec2{ 0, -1 };
				m_physicsComponent->SetVelocity(velocity + (up * jump));
			}

			m_physicsComponent->SetGravityScale((velocity.y > 0) ? 2 : 1);

			// animation
			if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_E) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_E))
			{
				m_spriteAnimComponent->SetSequence("attack");
				attackTimerActive = true;

				int xPos = 60 * facing;
				auto hitbox = INSTANTIATE(Hitbox, "Hitbox")
				hitbox->transform = { vec2 {transform.position.x - xPos,transform.position.y - 50}, 0, 1 };
				hitbox->Initialize();
				m_scene->Add(std::move(hitbox));

				m_state = playerState::Attack;
				break;
			}


			if (onGround == false)
			{
				//if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
				m_spriteAnimComponent->SetSequence("jump");
			}
			else
			{
				if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S))
				{
					if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
					m_spriteAnimComponent->SetSequence("crouch");

					m_state = playerState::Crouch;
				}
				else
				{
					if (std::fabs(velocity.x) > 0.2f)
					{
						if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
						m_spriteAnimComponent->SetSequence("run");
					}
					else
					{
						m_spriteAnimComponent->SetSequence("idle");
					}
				}
			}

			break;
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Bounce")
		{
			vec2 velocity = m_physicsComponent->m_velocity;

			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump) * 3);
		}

		if (other->tag == "Ground")
		{
			groundCount++;
			jump = defaultJump;
		}

		if (other->tag == "Enemy" && m_state == playerState::Idle || other->tag == "Enemy" && m_state == playerState::Crouch)
		{
			hurtTimerActive = true;
			m_spriteAnimComponent->SetSequence("hurt");
			health -= 10;
			m_state = playerState::Hurt;
			
		}
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}
}
