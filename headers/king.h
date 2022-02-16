#pragma once

#include "piece.h"
#include "sprites.h"


class king : public piece {

public:

	bool in_check = false;

	king(color col, sprites& sprites, coordinates pos);
	std::vector<possible_move> get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board);

private:

	static const std::array<coordinates, 8> king_possible_moves;

};
