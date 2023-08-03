#include "Texture.h"
#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_image.h"
#include "Core/Logger.h"
namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			// LOG_WARNING
			WARNING_LOG("Null surface");
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING
			WARNING_LOG("Null texture");
			return false;
		}
		return true;
	}

	vec2 Texture::GetSize()
	{
		// ASSERT texture is not null
		ASSERT_LOG(this->m_texture != NULL, "Texture can not be null");

		SDL_Point point;

		SDL_QueryTexture(this->m_texture, NULL, NULL, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}
}