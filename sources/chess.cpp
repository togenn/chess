#include "chess.h"
#include "sprites.h"
#include <iostream>
#include <algorithm>

chess& chess::getInstance() {

	static chess instance;

	return instance;
}

SDL_Texture* board_sprites::get_next(SDL_Texture*& square) {

	square = square == dark_square ? light_square : dark_square;

	return square;
}


chess::chess() {

	SDL_Init(SDL_INIT_EVERYTHING);

	create_window();

	m_sprites = std::make_unique<sprites>(m_renderer);

}

chess::~chess() {
	
	SDL_DestroyRenderer(m_renderer);

	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void chess::set_pieces() {
	
	for (int i = 8; i < 16; ++i) {
		board[i] = std::make_unique<pawn>(color::black, coordinates{ i - 8, 1 }, *m_sprites);
	}

	for (int i = 8 * 6; i < 8 * 7; ++i) {
		board[i] = std::make_unique<pawn>(color::white, coordinates{ i - 8 * 6, 6 }, *m_sprites);
	}

	board[0] = std::make_unique<rook>(color::black, *m_sprites, coordinates{ 0, 0 });
	board[1] = std::make_unique<knight>(color::black, *m_sprites, coordinates{ 1, 0 });
	board[2] = std::make_unique<bishop>(color::black, *m_sprites, coordinates{ 2, 0 });
	board[3] = std::make_unique<queen>(color::black, *m_sprites, coordinates{ 3, 0 });
	board[4] = std::make_unique<king>(color::black, *m_sprites, coordinates{ 4, 0 });	
	board[5] = std::make_unique<bishop>(color::black, *m_sprites, coordinates{ 5, 0 });
	board[6] = std::make_unique<knight>(color::black, *m_sprites, coordinates{ 6, 0 });
	board[7] = std::make_unique<rook>(color::black, *m_sprites, coordinates{ 7, 0 });

	board[56] = std::make_unique<rook>(color::white, *m_sprites, coordinates{ 0, 7 });
	board[57] = std::make_unique<knight>(color::white, *m_sprites, coordinates{ 1, 7 });
	board[58] = std::make_unique<bishop>(color::white, *m_sprites, coordinates{ 2, 7 });
	board[60] = std::make_unique<king>(color::white, *m_sprites, coordinates{ 4, 7 });
	board[59] = std::make_unique<queen>(color::white, *m_sprites, coordinates{ 3, 7 });
	board[61] = std::make_unique<bishop>(color::white, *m_sprites, coordinates{ 5, 7 });
	board[62] = std::make_unique<knight>(color::white, *m_sprites, coordinates{ 6, 7 });
	board[63] = std::make_unique<rook>(color::white, *m_sprites, coordinates{ 7, 7 });

	for (int i = 16; i < 8 * 6; ++i) {
		board[i] = nullptr;
	}

	black_king = dynamic_cast<king*>(board[4].get());
	white_king = dynamic_cast<king*>(board[60].get());

		
}

void chess::start_game() {

	turn = color::white;

	set_pieces();

	SDL_ShowWindow(m_window);
	
	draw_board();

	wait_for_events();

	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void chess::create_window() {

	m_window = SDL_CreateWindow("chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
}


void chess::draw_board() {

	board_sprites board_sprites = { m_sprites->dark_square, m_sprites->light_square };

	int min = std::min(height, width);

	SDL_Rect dest_rect;
	dest_rect.h = min / 8;
	dest_rect.w = dest_rect.h;

	SDL_Texture* next_texture = board_sprites.light_square;

	SDL_RenderClear(m_renderer);

	min -= min % 8;

	if (!min) {
		return;
	}

	x_offset = (width - min) / 2;
	y_offset = (height - min) / 2;

	for (int i = 0; i < 64; ++i) {
		dest_rect.x = i * (min / 8) % min + x_offset;
		dest_rect.y = i / 8 * (min / 8) + y_offset;

		next_texture = i % 8 == 0 ? next_texture : board_sprites.get_next(next_texture);

		SDL_RenderCopy(m_renderer, next_texture, NULL, &dest_rect);

		if (!board[i]) {
			continue;
		}

		SDL_RenderCopy(m_renderer, board[i]->get_sprite(), NULL, &dest_rect);
	}

	SDL_RenderPresent(m_renderer);

}

void chess::wait_for_events() {

	SDL_Event event;
	
	std::unique_ptr<piece> piece_grabbed;

	std::cout << "white's turn\n";

	while (SDL_WaitEvent(&event) && running) {

		switch (event.type) {

		case SDL_MOUSEBUTTONDOWN:
		{
			coordinates mouse_down = get_square_coordinates({ event.button.x, event.button.y });

			if (board[mouse_down.get_board_index()]) {

				if (board[mouse_down.get_board_index()]->get_color() != turn) {
					break;
				}

				piece_grabbed = std::move(board[mouse_down.get_board_index()]);

			}
			else {
				piece_grabbed = nullptr;
			}
		}

			break;

		case SDL_MOUSEBUTTONUP:
		
		{

			if (piece_grabbed) {

				coordinates button_up = get_square_coordinates({ event.button.x, event.button.y });
				auto possible_moves = piece_grabbed->get_possible_moves(board);
				king* if_king = dynamic_cast<king*>(piece_grabbed.get());

				if (if_king) {

					check_for_castling(possible_moves, *if_king);
				}

				check_moves_for_check(possible_moves, piece_grabbed);
				
				possible_move move;

				if (std::find_if(possible_moves.begin(), possible_moves.end(), [&button_up, &move](const possible_move& possible_move) {
					move = possible_move;
					return (possible_move.pos.x == button_up.x) && (possible_move.pos.y == button_up.y);
					}) != possible_moves.end()) {

					board[button_up.get_board_index()] = std::move(piece_grabbed);
					board[button_up.get_board_index()]->set_position(button_up);

					if (move._move_type == move_type::en_pasant) {

						if (turn == color::white) {
							board[get_board_index({ button_up.x, button_up.y + 1 })] = nullptr;
						}
						else {
							board[get_board_index({ button_up.x, button_up.y - 1 })] = nullptr;
						}
					}
					else if (move._move_type == move_type::promotion) {

						board[button_up.get_board_index()] = std::make_unique<queen>(turn, *m_sprites, coordinates{ button_up.x, button_up.y });

					}
					else if (move._move_type == move_type::castle) {

						if (move.pos.x == 6) {
							//kingside
							board[get_board_index({ 5, move.pos.y })] = std::move(board[get_board_index({ 7, move.pos.y })]);
							board[get_board_index({ 5, move.pos.y })]->set_position({ 5, move.pos.y });
						}
						else {
							//queenside
							board[get_board_index({ 3, move.pos.y })] = std::move(board[get_board_index({ 0, move.pos.y })]);
							board[get_board_index({ 3, move.pos.y })]->set_position({ 0, move.pos.y });
						}

					}

					check_for_win();

					turn = turn == color::white ? color::black : color::white;

					pawn::clear_possible_en_pasants(board, turn);

					if (turn == color::white) {

						std::cout << "white's turn\n";

					}
					else {
						std::cout << "black's turn\n";
					}

				}
				else {

					board[piece_grabbed->get_position().get_board_index()] = std::move(piece_grabbed);

				}

				piece_grabbed = nullptr;

				draw_board();

			}

		}
	
			break;


		case SDL_MOUSEMOTION:

		{
			if (piece_grabbed) {

				int x = event.motion.x;
				int y = event.motion.y;

				draw_board();

				SDL_Rect dest_rect;
				int square_size = std::min(height, width) / 8;
				dest_rect.h = square_size;
				dest_rect.w = square_size;
				dest_rect.x = x - 32;
				dest_rect.y = y - 32;

				
				SDL_RenderCopy(m_renderer, piece_grabbed->get_sprite(), NULL, &dest_rect);
				
				SDL_RenderPresent(m_renderer);
				
				
			}

		}

			break;

		case SDL_WINDOWEVENT:

			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {

				SDL_GetWindowSize(m_window, &width, &height);
				draw_board();

			}

			break;

		case SDL_QUIT:

			running = false;
			break;
		}
		

	}

}

coordinates chess::get_square_coordinates(coordinates pixel_pos) {

	int board_width = width - 2 * x_offset;
	int board_height = height - 2 * y_offset;

	return { (pixel_pos.x - x_offset) / (board_width / 8), (pixel_pos.y + y_offset) / (board_height / 8)};
}


void chess::check_moves_for_check(std::vector<possible_move>& moves, std::unique_ptr<piece>& grabbed_piece) {

	coordinates original_pos = grabbed_piece->get_position();

	color col = grabbed_piece->get_color();

	for (int i = 0; i < moves.size(); ++i) {

		possible_move move = moves[i];

		std::unique_ptr<piece> original_piece = std::move(board[move.pos.y * 8 + move.pos.x]);
		grabbed_piece->set_position({ move.pos.x, move.pos.y }, false);

		std::unique_ptr<piece> en_pasant_pawn;
		if (move._move_type == move_type::en_pasant) {

			if (col == color::white) {
				en_pasant_pawn = std::move(board[get_board_index({ move.pos.x, move.pos.y + 1 })]);
			}
			else {
				en_pasant_pawn = std::move(board[get_board_index({ move.pos.x, move.pos.y - 1 })]);
			}
		}

		board[move.pos.get_board_index()] = std::move(grabbed_piece);

		auto enemy_moves = get_all_moves_of_enemy();
		king* own_king = turn == color::white ? white_king : black_king;

		if (is_square_in_moves(enemy_moves, own_king->get_position())) {

			moves.erase(moves.begin() + i);
			--i;

		}

		grabbed_piece = std::move(board[move.pos.get_board_index()]);
		board[move.pos.get_board_index()] = std::move(original_piece);
		grabbed_piece->set_position({ original_pos.x, original_pos.y }, false);
		
		
		if (move._move_type == move_type::en_pasant) {


			if (col == color::white) {
				board[get_board_index({ move.pos.x, move.pos.y + 1 })] = std::move(en_pasant_pawn);
			}
			else {
				board[get_board_index({ move.pos.x, move.pos.y - 1 })] = std::move(en_pasant_pawn);
			}
		}
	
	}

}

std::vector<possible_move> chess::get_all_moves_of_enemy() {

	std::vector<possible_move> moves;

	for (auto& piece_ptr : board) {

		if (!piece_ptr) {
			continue;
		}

		if (piece_ptr->get_color() == turn) {
			continue;
		}

		auto moves_for_piece = piece_ptr->get_possible_moves(board);

		moves.reserve(moves_for_piece.size() + moves.size());

		moves.insert(moves.end(), moves_for_piece.begin(), moves_for_piece.end());

	}

	return moves;

}

bool chess::is_square_in_moves(std::vector<possible_move>& moves, coordinates square) {

	bool found = false;

	if (std::find_if(moves.begin(), moves.end(),
		[&square](const possible_move& check_move) {
			bool x_same = check_move.pos.x == square.x;
			bool y_same = check_move.pos.y == square.y;

			return x_same && y_same;

		}) != moves.end()) {

		found = true;

	}

	return found;

}


void chess::check_for_castling(std::vector<possible_move>& moves, king& king) {

	if (king.has_moved()) {
		return;
	}

	std::vector<possible_move> enemy_moves;
 

	//kingside
	if (board[get_board_index({ 7, king.get_position().y})]) {

		if (!board[get_board_index({ 7, king.get_position().y })]->has_moved()) {

			enemy_moves = get_all_moves_of_enemy();

			bool requirements = true;
			for (int i = 4; i < 7; ++i) {

				if (board[get_board_index({ i, king.get_position().y })]) {
					requirements = false;
					break;
				}

				if (square_under_attack(enemy_moves, coordinates{ i, king.get_position().y })) {
					requirements = false;
					break;
				}
			}

			if (requirements) {

				moves.push_back({ { 6, king.get_position().y }, move_type::castle });
			}
		}
	}

	//queenside
	if (board[get_board_index({ 0, king.get_position().y })]) {

		if (!board[get_board_index({ 0, king.get_position().y })]->has_moved()) {

			if (enemy_moves.empty()) {
				enemy_moves = get_all_moves_of_enemy();
			}

			bool requirements = true;
			for (int i = 1; i < 4; ++i) {

				if (board[get_board_index({ i, king.get_position().y })]) {
					requirements = false;
					break;
				}

				if (square_under_attack(enemy_moves, coordinates{ i, king.get_position().y })) {
					requirements = false;
					break;
				}
			}

			if (requirements) {

				moves.push_back({ { 2, king.get_position().y }, move_type::castle });
			}
		}
	}
}

bool chess::square_under_attack(std::vector<possible_move>& enemy_moves, coordinates square) {


	bool under_attack = false;

	for (possible_move& move : enemy_moves) {

		if (is_square_in_moves(enemy_moves, square)) {

			under_attack = true;

		}


	}

	return under_attack;

}

void chess::check_for_win() {

	//Inverse turn, because check_moves_for_check() checks moves for the player whose
	//turn it is.

	turn = turn == color::white ? color::black : color::white;

	for (auto& square : board) {

		if (!square) {
			continue;
		}

		if (square->get_color() != turn) {
			continue;
		}

		auto piece_moves = square->get_possible_moves(board);
		check_moves_for_check(piece_moves, square);

		if (!piece_moves.empty()) {
			turn = turn == color::white ? color::black : color::white;
			return;
		}

	}

	draw_board();
	turn = turn == color::white ? color::black : color::white;
	std::string turn_str = turn == color::white ? "white" : "black";

	std::cout << turn_str << " won!\n";
	
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {

		if (event.type == SDL_MOUSEBUTTONDOWN) {

			start_game();

		}
	}

}


