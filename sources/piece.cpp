#include "piece.h"


piece::piece(color col, coordinates pos) : m_color(col), m_position(pos) {}

SDL_Texture* piece::get_sprite() const {
	
	return m_sprite;
}

color piece::get_color() const {

	return m_color;
}

coordinates piece::get_position() const {

	return m_position;
}

void piece::set_position(coordinates pos, bool set_moved) {

	if (set_moved) {
		moved = true;
	}
	
	m_position = pos;

}

bool piece::has_moved() const {

	return moved;
}

std::vector<possible_move> piece::get_possible_moves_straight_line(std::array<std::unique_ptr<piece>, 64>& board) const {

	std::vector<possible_move> possible_moves;

	for (int i = 0; i < 4; ++i) {

		int d_x;
		int d_y;

		switch (i) {

		case 0:
			d_x = -1;
			d_y = 0;
			break;

		case 1:
			d_x = 0;
			d_y = -1;
			break;

		case 2:
			d_x = 1;
			d_y = 0;
			break;

		case 3:
			d_x = 0;
			d_y = 1;
			break;
		}

		get_possible_moves_to_direction(board, possible_moves, d_x, d_y);

	}

	return possible_moves;

}

std::vector<possible_move> piece::get_possible_moves_diagonal(std::array<std::unique_ptr<piece>, 64>& board) const {

	std::vector<possible_move> possible_moves;


	for (int i = 0; i < 4; ++i) {
		
		int d_x;
		int d_y;

		switch (i) {

		case 0:
			d_x = -1;
			d_y = -1;
			break;

		case 1:
			d_x = 1;
			d_y = 1;
			break;

		case 2:
			d_x = 1;
			d_y = -1;
			break;

		case 3:
			d_x = -1;
			d_y = 1;
			break;
		}

		int index = 0;
		get_possible_moves_to_direction(board, possible_moves, d_x, d_y);
	
	}

	return possible_moves;
	
}


void piece::get_possible_moves_to_direction(std::array<std::unique_ptr<piece>, 64>& board,
	std::vector<possible_move>& possible_moves, int d_x, int d_y) const {

	int index = 0;
	do {

		++index;
		int square_x = m_position.x + d_x * index;
		int square_y = m_position.y + d_y * index;
		coordinates square_to_test = { square_x, square_y };

		if (square_y > 7 || square_x > 7) {
			break;
		}

		if (square_y < 0 || square_x < 0) {
			break;
		}

		piece* piece_in_square = board[square_to_test.get_board_index()].get();

		if (piece_in_square && piece_in_square->get_color() == m_color) {
			break;
		}

		possible_moves.push_back({ square_to_test });

	} while (!board[(m_position + coordinates{ index * d_x, index * d_y }).get_board_index()]);

}
