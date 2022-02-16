#pragma once

#include "SDL.h"
#include "all_pieces.h"
#include "sprites.h"
#include <array>
#include <memory>


struct board_sprites {
	SDL_Texture* dark_square;
	SDL_Texture* light_square;

	SDL_Texture* get_next(SDL_Texture*& square);

};


//singleton
class chess {

public:

	static chess& getInstance();

	void start_game();

	chess(const chess&) = delete;
	void operator=(const chess&) = delete;

private:

	int height = 512;
	int width = 512;
	int x_offset;
	int y_offset;
	bool running = true;
	std::array<std::unique_ptr<piece>, 64> board;
	std::unique_ptr<sprites> m_sprites;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	king* black_king;
	king* white_king;
	color turn;
	

	chess();

	~chess();


	void create_window();
	void set_pieces();
	void draw_board();
	void wait_for_events();
	coordinates get_square_coordinates(coordinates pixel_pos);
	void check_moves_for_check(std::vector<possible_move>& moves, std::unique_ptr<piece>& grabbed_piece);
	std::vector<possible_move> get_all_moves_of_enemy();
	bool is_square_in_moves(std::vector<possible_move>& moves, coordinates square);
	bool square_under_attack(std::vector<possible_move>& enemy_moves, coordinates square);
	void check_for_castling(std::vector<possible_move>& moves, king& king);
	void check_for_win();

};


