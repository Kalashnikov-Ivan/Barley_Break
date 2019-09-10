#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#include "barley.h"

int main(void) 
{
	size_t size_y = 4, size_x = 4;

	print_welcome();

	printf("Enter any key to start...");
	KEYBOARD control = _getch();

	if (control == EXIT)
		return 0;

	bool correct_input = false;
	while (!correct_input)
	{
		printf("\nEnter height of field (3, 4, 5): ");
		scanf("%d", &size_y);
		printf("\nEnter width of field (3, 4, 5, 6, 7): ");
		scanf("%d", &size_x);

		if ((size_y < 3 || size_y > 5) || (size_x < 3 || size_x > 7))
			printf("\nPlease, enter correct value!");
		else
			correct_input = true;
	}

	bool new_game;
	do
	{
		new_game = false;
		barley_field_t * field = init_field(size_y, size_x);
		if (NULL == field)
			return 1;

		while (check_win(field))
			field = init_field(size_y, size_x);

		uint32_t move_counter = 0;

		while (!check_win(field))
		{
			system("cls");
			print_field(field);

			print_instruction();

			printf("\nQuantity of moves: %d\n", move_counter);

			control = _getch();

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
			system("cls");
			print_field(field);

			print_win(move_counter);
			printf("\nEnter any key to continue...");

			//Start music
			Beethoven();

			_getch();
		}

		if (control != EXIT)
		{
			char answer = 0;
			while (answer != 'y' && answer != 'n')
			{
				printf("Do you want play again? (y/n)");
				answer = _getch();
			}
		}

		free_field(field);
	} while (new_game);

	return 0;
}