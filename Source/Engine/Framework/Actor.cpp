#include "Actor.h"
#include "Components/RenderComponent.h"

void kiko::Actor::Update(float dt)
{
	if (m_lifespan != -1.0f)
	{
		m_lifespan -= dt;
		m_destroyed = (m_lifespan <= 0);

	}

	for (auto& component : m_components)
	{
		component->Update(dt);
	}
}

void kiko::Actor::Draw(kiko::Renderer& renderer)
{
	//m_model->Draw(renderer, m_transform);
	for (auto& component : m_components)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent)
		{
			renderComponent->Draw(renderer);
		}
	}
}

void kiko::Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->m_owner = this;
	m_components.push_back(std::move(component));
}
