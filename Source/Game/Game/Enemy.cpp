#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Framework.h"

bool Enemy::Initialize()
{
	Actor::Initialize();

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

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
	Player* player = m_scene->GetActor<Player>();

	if (player)
	{
		kiko::Vector2 direction = player->transform.position - transform.position; // could make a getter

		//turn towards player
		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
		transform.rotation += turnAngle * dt; // * 5

		//check if player is in front
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			if (m_fireTimer <= 0.0f)
			{
				//kiko::Transform m_transform{ transform.position, transform.rotation, 0.5f };
				//std::unique_ptr<WeaponComponent> weapon = std::make_unique<WeaponComponent>(400.0f, transform); //model
				//weapon->tag = "Enemy";

				//auto renderComponent = std::make_unique<kiko::SpriteComponent>();
				//renderComponent->m_texture = GET_RESOURCE( kiko::Texture, "rocket.png", kiko::g_renderer); //get texture
				//weapon->AddComponent(std::move(renderComponent));

				//auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				//collisionComponent->m_radius = 30.0f;
				//weapon->AddComponent(std::move(collisionComponent));

				//weapon->Initialize();
				//m_scene->Add(std::move(weapon));

				//m_fireTimer = m_fireRate;
			}
		}
	}

	transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (lifespan != -1.0f)
	{
		lifespan -= dt;
		destroyed = (lifespan <= 0);
	}

	m_fireTimer -= dt;

}

void Enemy::OnCollision(Actor* other)
{
	//could also use a dynamic cast
	//Player* p = dynamic_cast<Player*>(other);

	if (other->tag == "Player" && destroyed != true)
	{
		m_game->AddPoints(100.0f);
		m_game->AddKills(1);
		destroyed = true;

		//create explosion
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

		data.color = kiko::Color{ 1, 1, 0, 1 };

		kiko::Transform m_transform{ {this->transform.position.x, this->transform.position.y}, 0, 1 };
		auto emitter = std::make_unique<kiko::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}