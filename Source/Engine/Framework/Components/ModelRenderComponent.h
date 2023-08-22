#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace kiko
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_model->GetRadius(); }
	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}