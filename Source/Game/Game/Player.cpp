#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
//renderer? 

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1.5;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1.5;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon
		kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1.0f };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(600.0f, transform1, m_model);
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon)); //moving ownership to parameter we are passing

		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), 1.0f };
		weapon = std::make_unique<Weapon>(600.0f, transform2, m_model);
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon)); 
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T))
	{
		kiko::g_time.SetTimeScale(0.5f);
	}
	else  kiko::g_time.SetTimeScale(1.0f);

	m_transform.position.x +=  kiko::randomf(-1.0f, 1.0f);
	m_transform.position.y += kiko::randomf(-1.0f, 1.0f);

	if (kiko::g_inputSystem.GetMouseButtonDown(0) || kiko::g_inputSystem.GetMouseButtonDown(1) || kiko::g_inputSystem.GetMouseButtonDown(2))
	{
		kiko::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = kiko::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = kiko::Color{ 1, 0, 0, 1 };

		kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	
	
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);

		kiko::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = kiko::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.0f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;

		data.color = kiko::Color{ 1, 1, 0, 1 };


		kiko::Transform transform{ {m_transform.position.x, m_transform.position.y}, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
		
	}
}