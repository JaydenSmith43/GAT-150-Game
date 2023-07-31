#include "ParticleSystem.h"

namespace kiko
{
	kiko::ParticleSystem g_particleSystem(100);

	void kiko::ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Update(dt);
		}
	}

	void kiko::ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Draw(renderer);
		}
	}

	kiko::Particle* kiko::ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.m_isActive) return &particle;
		}
		return nullptr;
	}
}