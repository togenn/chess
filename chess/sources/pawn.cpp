#include "pawn.h"
#include "SDL.h"


pawn::pawn(color col, sprites* sprites) : piece(col) {

	SDL_Texture* texture = col == color::black ? sprites->black_pawn : sprites->white_pawn;

	m_sprite = texture;

}