#include "rook.h"
#include "SDL.h"


rook::rook(color col, sprites& sprites, coordinates pos) : piece(col, pos) {

	SDL_Texture* texture = col == color::black ? sprites.black_rook : sprites.white_rook;

	m_sprite = texture;

}

std::vector<possible_move> rook::get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) {

	std::vector<possible_move> possible_moves = get_possible_moves_straight_line(board);

	return possible_moves;

}