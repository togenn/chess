#pragma once

struct coordinates {

	int x = -1;
	int y = -1;

	int get_board_index();

	coordinates operator+(const coordinates& rhs) const;

};

int get_board_index(coordinates pos);

