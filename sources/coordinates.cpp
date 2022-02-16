#include "coordinates.h"


int coordinates::get_board_index() {

	return 8 * y + x;
}

coordinates coordinates::operator+(const coordinates& pos) const {

	return { x + pos.x, y + pos.y };
}

int get_board_index(coordinates pos) {

	return 8 * pos.y + pos.x;
}