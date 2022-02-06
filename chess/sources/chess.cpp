#include "chess.h"
#include "sprites.h"
#include "piece.h"
#include "pawn.h"
#include <iostream>



SDL_Texture* board_sprites::get_next(SDL_Texture*& square) {

	square = square == dark_square ? light_square : dark_square;

	return square;
}


chess::chess() {

	SDL_Init(SDL_INIT_EVERYTHING);

	create_window();

	m_sprites = std::make_unique<sprites>(m_renderer);

	for (int i = 8; i < 16; ++i) {
		board[i] = std::make_unique<pawn>(color::black, m_sprites.get());
	}

	SDL_ShowWindow(m_window);

}

void chess::start_game() {
	
	update_board();

	wait_for_events();

	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void chess::create_window() {

	m_window = SDL_CreateWindow("chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, SDL_WINDOW_HIDDEN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}

void chess::draw_board() {

	board_sprites board_sprites = { m_sprites->dark_square, m_sprites->light_square };

	SDL_Rect dest_rect;
	dest_rect.h = 128;
	dest_rect.w = 128;

	SDL_Texture* next_texture = board_sprites.light_square;

	for (int i = 0; i < 64; ++i) {
		dest_rect.x = i * 128 % 1024;
		dest_rect.y = i / 8 * 128;

		next_texture = dest_rect.x == 0 ? next_texture : board_sprites.get_next(next_texture);

		SDL_RenderCopy(m_renderer, next_texture, NULL, &dest_rect);

		if (!board[i]) {
			continue;
		}

		SDL_RenderCopy(m_renderer, board[i]->get_sprite(), NULL, &dest_rect);
	}

}

void chess::wait_for_events() {

	while (1) {

	}

}

void chess::update_board() {

	draw_board();

	SDL_RenderPresent(m_renderer);

}
