#pragma once


#include "SDL.h"
#include <type_traits>

class sprites {

public:
	
	sprites(SDL_Renderer* renderer);

	~sprites();


	SDL_Texture* dark_square;
	SDL_Texture* light_square;

	SDL_Texture* black_pawn;
	SDL_Texture* white_pawn;

	SDL_Texture* black_rook;
	SDL_Texture* white_rook;

	SDL_Texture* black_bishop;
	SDL_Texture* white_bishop;

	SDL_Texture* black_king;
	SDL_Texture* white_king;

	SDL_Texture* black_queen;
	SDL_Texture* white_queen;

	SDL_Texture* black_knight;
	SDL_Texture* white_knight;



private:

	SDL_Renderer* renderer;

	SDL_Texture* load_sprite(const char* path, SDL_Renderer* renderer);
	void load_all_sprites(SDL_Renderer* renderer);
};
