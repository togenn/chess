#include "queen.h"
#include "SDL.h"


queen::queen(color col, sprites& sprites, coordinates pos) : piece(col, pos) {

	SDL_Texture* texture = col == color::black ? sprites.black_queen : sprites.white_queen;

	m_sprite = texture;

}

std::vector<possible_move> queen::get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) {

	std::vector<possible_move> possible_moves;

	auto possible_moves_straight = get_possible_moves_straight_line(board);

	auto possible_moves_diagonal = get_possible_moves_diagonal(board);

	possible_moves.reserve(possible_moves_straight.size() + possible_moves_diagonal.size());

	possible_moves.insert(possible_moves.end(), possible_moves_straight.begin(), possible_moves_straight.end());
	possible_moves.insert(possible_moves.end(), possible_moves_diagonal.begin(), possible_moves_diagonal.end());


	return possible_moves;

}