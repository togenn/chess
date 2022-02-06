#include <iostream>
#include "sprites.h"
#include "SDL_image.h"

sprites::sprites(SDL_Renderer* renderer) {

	load_all_sprites(renderer);
}



SDL_Texture* sprites::load_sprite(const char* path, SDL_Renderer* renderer) {

	SDL_Surface* surface = IMG_Load(path);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {

		std::cout << "ERROR: " << SDL_GetError() << std::endl;

	}

	SDL_FreeSurface(surface);
	
	
	return texture;

}


void sprites::load_all_sprites(SDL_Renderer* renderer) {

	dark_square = load_sprite("sprites/dark_square.png", renderer);
	light_square = load_sprite("sprites/light_square.png", renderer);

	black_pawn = load_sprite("sprites/black_pawn.png", renderer);
	light_square = load_sprite("sprites/white_pawn.png", renderer);

}