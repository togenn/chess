#pragma once

#include "piece.h"
#include "sprites.h"


class bishop : public piece {

public:


	bishop(color col, sprites& sprites, coordinates pos);
	std::vector<possible_move> get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board);

};
