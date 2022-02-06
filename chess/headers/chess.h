#pragma once

#include "SDL.h"
#include "piece.h"
#include "sprites.h"
#include <array>
#include <memory>


struct board_sprites {
	SDL_Texture* dark_square;
    SDL_Texture* light_square;

	SDL_Texture* get_next(SDL_Texture*& square);

};


//make this singleton
class chess {

public:

	chess();

	void start_game();

private:
	
	std::array<std::unique_ptr<piece>, 64> board;
	std::unique_ptr<sprites> m_sprites;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	void create_window();
	void draw_board();
	void wait_for_events();
	void update_board();
	

};


