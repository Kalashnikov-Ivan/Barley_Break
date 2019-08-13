#include <stdio.h>
#include <ncursesw/ncurses.h>

#include "barley.h"


int main(void) 
{
	WINDOW *win_curses = initscr();
	if (NULL == win_curses)
		return 1;

	curs_set(0);

	barley_field_t * restrict field = init_field(4, 4);
	if (NULL == field)
		return 1;

	KEYBOARD dir;

	while (1)
	{
		system("clear");
		print_field(field);
		//refresh();

		dir = getch();

		barley_move(field, dir);
	}

	endwin();

	free_field(field);

	return 0;
}