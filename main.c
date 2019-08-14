#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#include "barley.h"

int main(void) 
{
	if (NULL == initscr())
		return 1;

	size_t size_y = 4, size_x = 4;

	print_welcome();

	printw("Enter any key to start...");
	getch();

	erase();

	bool correct_input = false;
	while (!correct_input)
	{
		printw("\nEnter height of field (3, 4, 5): ");
		scanw("%d", &size_y);
		printw("\nEnter width of field (3, 4, 5, 6, 7): ");
		scanw("%d", &size_x);

		if ((size_y < 3 || size_y > 5) || (size_x < 3 || size_x > 7))
			printw("\nPlease, enter correct value!");
		else
			correct_input = true;
	}
	

	curs_set(0);
	keypad (stdscr, TRUE);
	noecho();

	barley_field_t * restrict field = init_field(size_y, size_x);
	if (NULL == field)
		return 1;

	while (check_win(field))
        field = init_field(size_y, size_x);

	KEYBOARD control;
	uint32_t move_counter = 0;

	while (!check_win(field))
	{
		erase();
		print_field(field);

		print_instruction();

		printw("\nQuantity of moves: %d\n", move_counter);

		control = getch();

		if (control == EXIT)
			break;

		if (control == RESTART)
		{
			field = init_field(size_y, size_x);

			while (check_win(field))
				field = init_field(size_y, size_x);

			move_counter = 0;
			continue;
		}

		if (barley_move(field, control))
			move_counter++;
	}

	if (check_win(field))
	{
		erase();
		print_field(field);

		print_win(move_counter);
		printw("\nEnter any key to continue...");

		getch();
	}

	endwin();

	free_field(field);

	return 0;
}