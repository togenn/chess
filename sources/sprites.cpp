#include <iostream>
#include "sprites.h"
#include "SDL_image.h"

sprites::sprites(SDL_Renderer* renderer) {

	load_all_sprites(renderer);
}

sprites::~sprites() {

	SDL_DestroyTexture(dark_square);
	SDL_DestroyTexture(light_square);
	SDL_DestroyTexture(black_pawn);
	SDL_DestroyTexture(white_pawn);
	SDL_DestroyTexture(black_rook);
	SDL_DestroyTexture(white_rook);
	SDL_DestroyTexture(black_bishop);
	SDL_DestroyTexture(white_bishop);
	SDL_DestroyTexture(black_king);
	SDL_DestroyTexture(white_king);
	SDL_DestroyTexture(black_queen);
	SDL_DestroyTexture(white_queen);
	SDL_DestroyTexture(black_knight);
	SDL_DestroyTexture(white_knight);
}

SDL_Texture* sprites::load_sprite(const char* path, SDL_Renderer* renderer) {

	SDL_Surface* surface = IMG_Load(path);
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {

		std::cout << "ERROR: " << SDL_GetError() << " path: " << path << std::endl;

	}

	SDL_FreeSurface(surface);
	
	
	return texture;

}


void sprites::load_all_sprites(SDL_Renderer* renderer) {

	dark_square = load_sprite("sprites/dark_square.png", renderer);
	light_square = load_sprite("sprites/light_square.png", renderer);

	black_pawn = load_sprite("sprites/black_pawn.png", renderer);
	white_pawn = load_sprite("sprites/white_pawn.png", renderer);

	black_rook = load_sprite("sprites/black_rook.png", renderer);
	white_rook = load_sprite("sprites/white_rook.png", renderer);

	black_bishop = load_sprite("sprites/black_bishop.png", renderer);
	white_bishop = load_sprite("sprites/white_bishop.png", renderer);

	black_king = load_sprite("sprites/black_king.png", renderer);
	white_king = load_sprite("sprites/white_king.png", renderer);

	black_queen = load_sprite("sprites/black_queen.png", renderer);
	white_queen = load_sprite("sprites/white_queen.png", renderer);

	black_knight = load_sprite("sprites/black_knight.png", renderer);
	white_knight = load_sprite("sprites/white_knight.png", renderer);

}