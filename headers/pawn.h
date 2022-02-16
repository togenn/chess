#pragma once


#include "piece.h"
#include "sprites.h"


class pawn : public piece {

public:

	bool possible_en_passant = false;

	pawn(color col, coordinates pos, sprites& sprites);
	
	std::vector<possible_move> get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) override;

	static void clear_possible_en_pasants(std::array<std::unique_ptr<piece>, 64>& board, color col);

private:

	
};