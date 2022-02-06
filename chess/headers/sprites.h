#pragma once

#include "SDL.h"

class sprites {

public:
	
	sprites(SDL_Renderer* renderer);


	SDL_Texture* dark_square;
	SDL_Texture* light_square;

	SDL_Texture* black_pawn;
	SDL_Texture* white_pawn;


private:

	SDL_Renderer* renderer;

	SDL_Texture* load_sprite(const char* path, SDL_Renderer* renderer);
	void load_all_sprites(SDL_Renderer* renderer);
};
