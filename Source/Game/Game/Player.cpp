#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/EnginePhysicsComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Components/CircleCollisionComponent.h"
//renderer? 

bool Player::Initialize()
{
	Actor::Initialize();

	//cache off
	m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale * 0.75f;
		}
	}

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1.5;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1.5;
	transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	//transform.position += forward * speed * thrust * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket")
		weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		////create weapon
		//kiko::Transform transform1{ transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1.0f };
		//std::unique_ptr<WeaponComponent> weapon = std::make_unique<WeaponComponent>(600.0f, transform1); //dont add model, we specify it with the component system
		//weapon->tag = "Player";

		//auto renderComponent = std::make_unique<kiko::SpriteComponent>();
		//renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "rocket.png", kiko::g_renderer); // get texture
		//weapon->AddComponent(std::move(renderComponent));

		//auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		//collisionComponent->m_radius = 30.0f;
		//weapon->AddComponent(std::move(collisionComponent));

		//weapon->Initialize();
		//m_scene->Add(std::move(weapon)); //moving ownership to parameter we are passing

		//kiko::Transform transform2{ transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1.0f };
		//weapon = std::make_unique<WeaponComponent>(600.0f, transform2);
		//weapon->tag = "Player";

		//renderComponent = std::make_unique<kiko::SpriteComponent>();
		//renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "rocket.png", kiko::g_renderer); //get texture
		//weapon->AddComponent(std::move(renderComponent));

		//collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		//collisionComponent->m_radius = 30.0f;
		//weapon->AddComponent(std::move(collisionComponent));

		//weapon->Initialize();
		//m_scene->Add(std::move(weapon)); 
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T))
	{
		kiko::g_time.SetTimeScale(0.5f);
	}
	else  kiko::g_time.SetTimeScale(1.0f);

	transform.position.x +=  kiko::randomf(-1.0f, 1.0f);
	transform.position.y += kiko::randomf(-1.0f, 1.0f);

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
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	
	
}

void Player::OnCollision(Actor* other)
{
	if (other->tag == "Enemy")
	{
		kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		destroyed = true;
		//m_game->SetLives(m_game->GetLives() - 1);
		//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);

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


		kiko::Transform m_transform{ {transform.position.x, transform.position.y}, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
		
	}
}