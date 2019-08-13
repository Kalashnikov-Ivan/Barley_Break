#include <stdio.h>
#include <ncurses.h>

#include "barley.h"


int main(void) 
{

	barley_field_t * restrict field = init_field(4, 4);
	if (NULL == field)
		return 1;

	KEYBOARD dir;

	while (1)
	{
		system("clear");
		print_field(field);

		WINDOW *win_curses = initscr();
		if (NULL == win_curses)
			return 1;

		dir = getch();

		endwin();

		barley_move(field, dir);

	}

	free_field(field);

	return 0;
}