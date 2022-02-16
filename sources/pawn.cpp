#include "pawn.h"
#include "SDL.h"
#include <cmath>

pawn::pawn(color col, coordinates pos, sprites& sprites) : piece(col, pos) {

	SDL_Texture* texture = col == color::black ? sprites.black_pawn : sprites.white_pawn;
	m_sprite = texture;

}

void pawn::clear_possible_en_pasants(std::array<std::unique_ptr<piece>, 64>& board, color col) {

	for (auto& piece : board) {

		pawn* pawn_obj = dynamic_cast<pawn*>(piece.get());

		if (pawn_obj) {

			if (pawn_obj->get_color() == col) {

				pawn_obj->possible_en_passant = false;
			}
		}

	}

}


std::vector<possible_move> pawn::get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) {

	std::vector<possible_move> possible_moves;

	int var = m_color == color::white ? -1 : 1;

	//check for moving forward
	if (!board[(m_position.y + var) * 8 + m_position.x]) {

		if (m_position.y == 1 && m_color == color::white) {
			possible_moves.push_back({ m_position.x, m_position.y + var, move_type::promotion });
		}
		else if (m_position.y == 6 && m_color == color::black) {
			possible_moves.push_back({ m_position.x, m_position.y + var, move_type::promotion });
		}
		else {
			possible_moves.push_back({ m_position.x, m_position.y + var });
		}

	}


	//check for capturing enemy
	if (board[(m_position.y + var) * 8 + m_position.x + 1] && m_position.x != 7) {

		if (board[(m_position.y + var) * 8 + m_position.x + 1]->get_color() != m_color) {

			if (m_position.y == 1 && m_color == color::white) {
				possible_moves.push_back({ m_position.x + 1, m_position.y + var, move_type::promotion });
			}
			else if (m_position.y == 6 && m_color == color::black) {
				possible_moves.push_back({ m_position.x + 1, m_position.y + var, move_type::promotion });
			}
			else {
				possible_moves.push_back({ m_position.x + 1, m_position.y + var });
			}

		}

	}

	if (board[(m_position.y + var) * 8 + m_position.x - 1] && m_position.x > 0) {


		if (board[(m_position.y + var) * 8 + m_position.x - 1]->get_color() != m_color) {

			if (m_position.y == 1 && m_color == color::white) {
				possible_moves.push_back({ m_position.x - 1, m_position.y + var, move_type::promotion });
			}
			else if (m_position.y == 6 && m_color == color::black) {
				possible_moves.push_back({ m_position.x - 1, m_position.y + var, move_type::promotion });
			}
			else {
				possible_moves.push_back({ m_position.x - 1, m_position.y + var });
			}

		}

	}


	//check for first move
	if (!moved && !board[(m_position.y + var) * 8 + m_position.x]) {

		if (!board[(m_position.y + 2 * var) * 8 + m_position.x]) {
			possible_moves.push_back({ m_position.x, m_position.y + 2 * var });
		}

	}
	


	//check for en passant
	if (board[m_position.y * 8 + m_position.x + 1] && (m_position.x < 7)) {

		pawn* enemy_pawn = dynamic_cast<pawn*>(board[m_position.y * 8 + m_position.x + 1].get());
		if (enemy_pawn && enemy_pawn->possible_en_passant) {

			possible_moves.push_back({ m_position.x + 1, m_position.y + var, move_type::en_pasant});

		}
	}

	if (board[m_position.y * 8 + m_position.x - 1] && (m_position.x > 0)) {

		pawn* enemy_pawn = dynamic_cast<pawn*>(board[m_position.y * 8 + m_position.x - 1].get());
		if (enemy_pawn && enemy_pawn->possible_en_passant) {

			possible_moves.push_back({ m_position.x - 1, m_position.y + var, move_type::en_pasant });

		}
	}
	

	return possible_moves;

}

