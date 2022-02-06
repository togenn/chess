#pragma once

#include "piece.h"
#include <array>
#include <memory>

class chess_board {
	
public:
	std::array<std::unique_ptr<piece>, 64> board;


private:

	

};
