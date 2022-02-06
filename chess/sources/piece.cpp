#include "piece.h"

SDL_Texture* piece::get_sprite() const {
	
	return m_sprite;
}

color piece::get_color() const {

	return m_color;
}