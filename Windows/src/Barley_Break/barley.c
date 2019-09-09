#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include <stddef.h> //For size_t, ptrdiff_t and so on...
#include <stdint.h> //For uint8_t and so on...
#include <stdbool.h>

#include "barley.h"

barley_field_t* init_field
    (const size_t size_x,
     const size_t size_y)
{
	srand(time(NULL));

	//-----------ALOC MEMORY-------------
	barley_field_t * result_field = (barley_field_t*)malloc(sizeof(barley_field_t));
    if (NULL == result_field)
        return NULL;

	//--------INIT SIZE OF FIELD---------
    result_field->size_x = size_x;
    result_field->size_y = size_y;

    result_field->barley = (int16_t**)malloc(sizeof(int16_t*) * size_y);
    if (NULL == result_field->barley)
        return NULL;

    for (size_t row = 0; row < size_y; row++)
    {
        result_field->barley[row] = (int16_t*)malloc(sizeof(int16_t) * size_x);
        if (NULL == result_field->barley[row])
            return NULL;
    }

	//----------INIT OF BARLEY------------
    size_t square = size_x * size_y;

    //Array of flags occupied nums
	bool * free_num = (bool*)malloc(sizeof(bool) * (square - 1)); //"-1" for one free cell

	do 
	{
		for (size_t i = 0; i < square; i++) //Init this array
			free_num[i] = true;


		int rand_num = 0;
		bool is_correct_num;

		for (size_t row = 0; row < size_y; row++)
		{
			for (size_t	col = 0; col < size_x; col++) //traversing a mult array as a one
			{
				is_correct_num = false;
				while (!is_correct_num) //Loop of checking correct (not repeating) num
				{
					rand_num = get_rand_in_range(1, square - 1);
					if (free_num[rand_num - 1]) //"-1" for taking into account index numeration
						is_correct_num = true;
				}

				result_field->barley[row][col] = rand_num; //Put correct rand num in barley array
				free_num[rand_num - 1] = false; //Set current num flag - occupied

				//to avoid looping in the case of the last empty cell 
				if (((row == size_y - 1) && (col == size_x - 2)))
					break;
			}
		}
	} while(check_chaos2(result_field));

	//Init first position
	result_field->position_x = size_x - 1;
	result_field->position_y = size_y - 1;

	//Emptying initial position
	result_field->barley[result_field->position_y][result_field->position_x] = 0;

	return result_field;
}


void free_field
    (barley_field_t * field)
{
    for (size_t row = 0; row < field->size_y; row++)
        free(field->barley[row]);
    
    free(field->barley);
    free(field);
}

bool check_chaos
    (barley_field_t * field)
{
	//For missimg always losing situation
	uint16_t chaos = 0; //Quantity of chaos in field
	for (size_t row = 0; row < field->size_y; row++)
	{
		for (size_t col = 0; col < field->size_x; col++)
		{
			for (size_t i = row; i < field->size_y; i++)
			{
				for (size_t j = col; j < field->size_x; j++)
				{
					if ((i == field->size_y - 1) && (j == field->size_x - 1))
						break;
					//to avoid looping in the case of the last empty cell 
					if (field->barley[row][col] > field->barley[i][j])
						chaos++;
				}
			}
			if ((row == field->size_y - 1) && (col > field->size_x - 1))
				break;
		}
	}

	field->chaos = chaos;

	if (chaos % 2 == 1) //If total chaos is odd
		return true;

	return false;
}

bool check_chaos2
    (barley_field_t * field)
{
	size_t row = field->size_y;
	size_t col = field->size_x;

	uint16_t *probe = (uint16_t*)malloc(sizeof(uint16_t) * (row * col));

	for (size_t i = 0, k = 0; i < row; i++)
		for (size_t j = 0; j < col; j++, k++)
			probe[k] = field->barley[i][j];

	uint16_t chaos = 0; 
	uint16_t current_num;

	for (size_t i = 0; i < row * col - 2; i++)
	{
		current_num = probe[i];
		for (size_t j = i + 1; j < row * col - 1; j++)
			if (current_num > probe[j])
				chaos++;
	}

	field->chaos = chaos;

	if (chaos % 2 == 1) //If total chaos is odd
		return true;

	return false;
}

bool barley_move
    (barley_field_t * field,
     const KEYBOARD dir)
{
	if (dir == UP && field->position_y != field->size_y - 1)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y + 1][field->position_x];

		field->position_y += 1;

		field->barley[field->position_y][field->position_x] = 0;

		return true;
	}
	if (dir == DOWN && field->position_y != 0)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y - 1][field->position_x];

		field->position_y -= 1;

		field->barley[field->position_y][field->position_x] = 0;

		return true;
	}
	if (dir == LEFT && field->position_x != field->size_x- 1)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y][field->position_x + 1];

		field->position_x += 1;

		field->barley[field->position_y][field->position_x] = 0;

		return true;
	}
	if (dir == RIGHT && field->position_x != 0)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y][field->position_x - 1];

		field->position_x -= 1;

		field->barley[field->position_y][field->position_x] = 0;

		return true;
	}

	return false;
}


bool check_win
	(const barley_field_t * field)
{
	uint16_t control = 1;
	for (size_t i = 0; i < field->size_y; i++)
	{
		for (size_t j = 0; j < field->size_x; j++)
		{
			if (field->barley[i][j] != control % (field->size_y * field->size_x))
				return false;
			control++;
		}
	}
	return true;
}

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max)
{
   return (min + rand() % (min - (max + 1)));
}

void print_field
	(const barley_field_t* field)
{
	for (size_t row = 0; row < field->size_y; row++)
	{
		for (size_t col = 0; col < field->size_x; col++) //Print top of cell
		{
			if (field->barley[row][col] == 0)
				printf("      ");
			else
				printf(" ---  ");
		}
		printf("\n");

		for (size_t col = 0; col < field->size_x; col++) //Print middle of cell
		{
			if (field->barley[row][col] == 0)
				printf("      ");
			else
				printf("| %-2d| ", field->barley[row][col]);
		}
		printf("\n");

		for (size_t col = 0; col < field->size_x; col++) //Print bottom of cell
		{
			if (field->barley[row][col] == 0)
				printf("      ");
			else
				printf(" ---  ");
		}
		printf("\n");
	}
}

void print_welcome()
{
	printf("Welcome to the Barley Break game!\n\n");

	printf("To control, use the arrows on the keyboard: UP, DOWN, LEFT, RIGHT\n");
	printf("Additional keys:\n 'r' - restart\n 'q' - exit\n");

	printf("\nThe goal of the game is to arrange all cells in ascending order as few moves as possible.\n");

	printf("\nGood luck!\n");
}

void print_instruction()
{
	printf("\nUse the arrows on keyboard for control: UP, DOWN, LEFT, RIGHT\n");
	printf("Press 'q' for exit\nPress 'r' for restart\n");
}

void print_win
    (const uint32_t moves)
{
	printf("\nCongratulations!!! You win!");

	printf("\nUsing: %d moves!\n", moves);
}

/* <----MUSIC---->*/
void Beethoven()
{
	Beep(659, 120);
	Sleep(130);
	Beep(622, 120);
	Sleep(130);

	Beep(659, 120);
	Sleep(130);
	Beep(622, 120);
	Sleep(130);
	Beep(659, 120);
	Sleep(130);
	Beep(494, 120);
	Sleep(130);
	Beep(587, 120);
	Sleep(130);
	Beep(523, 120);
	Sleep(130);

	Beep(440, 120);
	Sleep(150);
	Beep(262, 120);
	Sleep(130);
	Beep(330, 120);
	Sleep(130);
	Beep(440, 120);
	Sleep(130);

	Beep(494, 120);
	Sleep(150);
	Beep(330, 120);
	Sleep(130);
	Beep(415, 120);
	Sleep(130);
	Beep(494, 120);
	Sleep(130);

	Beep(523, 120);
	Sleep(150);
	Beep(330, 120);
	Sleep(130);
	Beep(659, 120);
	Sleep(130);
	Beep(622, 120);
	Sleep(130);

	Beep(659, 120);
	Sleep(130);
	Beep(622, 120);
	Sleep(130);
	Beep(659, 120);
	Sleep(130);
	Beep(494, 120);
	Sleep(130);
	Beep(587, 120);
	Sleep(130);
	Beep(523, 120);
	Sleep(130);

	Beep(440, 120);
	Sleep(150);
	Beep(262, 120);
	Sleep(130);
	Beep(330, 120);
	Sleep(130);
	Beep(440, 120);
	Sleep(130);

	Beep(494, 120);
	Sleep(150);
	Beep(330, 120);
	Sleep(130);
	Beep(523, 120);
	Sleep(130);
	Beep(494, 120);
	Sleep(150);
	Beep(440, 120);
}