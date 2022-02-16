#pragma once

#include "SDL.h"
#include "coordinates.h"
#include <vector>
#include <array>
#include <memory>


enum class color {
	white, black
};

enum class move_type {
	normal, en_pasant, promotion, castle
};

struct possible_move {
	coordinates pos;
	move_type move_type = move_type::normal;
};

class piece {

public:

	piece(color col, coordinates pos);

	SDL_Texture* get_sprite() const;

	color get_color() const;

	coordinates get_position() const;

	void set_position(coordinates pos, bool set_moved=true);

	bool has_moved() const;

	virtual std::vector<possible_move> get_possible_moves(std::array<std::unique_ptr<piece>, 64>& board) = 0;

protected:

	coordinates m_position;
	color m_color;
	bool moved = false;
	SDL_Texture* m_sprite = nullptr;

	std::vector<possible_move> get_possible_moves_straight_line(std::array<std::unique_ptr<piece>, 64>& board) const;

	std::vector<possible_move> get_possible_moves_diagonal(std::array<std::unique_ptr<piece>, 64>& board) const;

private:

	void get_possible_moves_to_direction(std::array<std::unique_ptr<piece>, 64>& board,
		std::vector<possible_move>& possible_moves, int d_x, int d_y) const;


	
};
