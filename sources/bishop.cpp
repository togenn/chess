#include "bishop.h"
#include "SDL.h"


bishop::bishop(color col, sprites& sprites, coordinates pos) : piece(col, pos) {

	SDL_Texture* texture = col == color::black ? sprites.black_bishop : sprites.white_bishop;

	m_sprite = texture;

};

std::vector<possible_move> bishop::get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) {

	return get_possible_moves_diagonal(board);

}