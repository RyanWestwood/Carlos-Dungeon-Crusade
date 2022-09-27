#include "Font.h"
#include "Renderer.h"

namespace Font {

	namespace {
		const std::string g_FontDirectory = "C:/Users/Ryan/Documents/Git/Artificial-Intelligence/assets/font/";
	}

	bool InitializeFont()
	{
		if (TTF_Init() < 0) {
			std::cout << "SDL_TTF could not initialize! SDL_TTF error: " << TTF_GetError() << "\n";
			return false;
		}
#ifdef LOGGING
		std::cout << "Font Initialized!\n";
#endif
		return true;
	}

	void UnInitializeFont()
	{
		TTF_Quit();
	}

	Font::FontData LoadFont(const char* filename, int fontsize, const char* message, const SDL_Color& color, const SDL_Point& position)
	{
#ifdef LOGGING
		std::cout << "Loading font: " << filename << "\n";
#endif
		try {
			TTF_Font* font = TTF_OpenFont((g_FontDirectory + std::string(filename)).c_str(), fontsize);
			if (font == nullptr) throw FontError();
			SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
			if (surface == nullptr) throw FontError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), surface);
			SDL_Rect dimensions = { position.x, position.y, surface->w, surface->h };
			SDL_FreeSurface(surface);
			return { font, texture, dimensions };
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
			return {};
		}
	}

	void Draw(SDL_Texture* texture, const SDL_Rect& dimensions)
	{
		SDL_RenderCopy(Renderer::GetRenderer(), texture, 0, &dimensions);
	}
}

Text::Text()
{
	m_Colour = { 60,60,60,255 };
	m_Position = { 0,0 };
	m_FontSize = 18;
	m_Dimensions = { 0,0,0,0 };
	m_Message = nullptr;
	m_Font = nullptr;
	m_Texture = nullptr;
}

void Text::Initalize(const char* filename, const char* message)
{
	auto font_data = Font::LoadFont(filename, m_FontSize, message, m_Colour, m_Position);
	m_Message = message;
	m_Font = font_data.m_Font;
	m_Texture = font_data.m_Texture;
	m_Dimensions = font_data.m_Dimensions;
}

void Text::Draw()
{
	Font::Draw(m_Texture, m_Dimensions);
}