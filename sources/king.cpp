#include "king.h"
#include "SDL.h"
#include "chess.h"


const std::array<coordinates, 8> king::king_possible_moves = {

	coordinates{ 1 , 1 },
	coordinates{ 1 , 0 },
	coordinates{ 1 , -1 },
	coordinates{ 0 , -1 },
	coordinates{ -1 , -1 },
	coordinates{ -1 , 0 },
	coordinates{ -1 , 1 },
	coordinates{ 0 , 1 },

};

king::king(color col, sprites& sprites, coordinates pos) : piece(col, pos) {

	SDL_Texture* texture = col == color::black ? sprites.black_king : sprites.white_king;

	m_sprite = texture;

}

std::vector<possible_move> king::get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) {

	std::vector<possible_move> possible_moves;

	for (const coordinates& move : king_possible_moves) {

		if (m_position.x + move.x > 7 || m_position.x + move.x < 0) {
			continue;
		}

		if (m_position.y + move.y > 7 || m_position.y + move.y < 0) {
			continue;
		}

		if (board[(m_position + move).get_board_index()]) {

			if (board[(m_position + move).get_board_index()]->get_color() == m_color) {
				continue;
			}
		}

		possible_moves.push_back({ m_position + move });

	}

	


	return possible_moves;

}

