#pragma once

#include "SDL.h"


enum class color {
	white, black
};


class piece {

public:

	piece(color col) : m_color(col) {}

	SDL_Texture* get_sprite() const;

	color get_color() const;

protected:

	color m_color;
	SDL_Texture* m_sprite = nullptr;
	
};
