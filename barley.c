#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	barley_field_t * restrict result_field = (barley_field_t*)malloc(sizeof(barley_field_t));
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
	bool * restrict free_num = (bool*)malloc(sizeof(bool) * (square - 1)); //"-1" for one free cell

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

	//For missimg always losing situation
	uint16_t chaos = 0; //Quantity of chaos in field
	for (size_t row = 0; row < size_y; row++)
	{
		for (size_t col = 0; col < size_x; col++)
		{
			for (size_t i = 0; i < size_y; i++)
			{
				for (size_t j = col + 1; j < size_x; j++)
				{
					//to avoid looping in the case of the last empty cell 
					if (((row == size_y - 1) && (j > size_x - 1)))
						break;
					if (result_field->barley[row][col] > result_field->barley[i][j])
						chaos++;
				}
			}
		}
	}

	if (chaos % 2) //If total amount is odd, swap 14 and 15 position (4x4)
	{
		int16_t tmp = result_field->barley[size_y - 1][size_x - 3];
		result_field->barley[size_y - 1][size_x - 3] = result_field->barley[size_y - 1][size_x - 2];
		result_field->barley[size_y - 1][size_x - 2] = tmp;
	}

	//Init first position
	result_field->position_x = size_x - 1;
	result_field->position_y = size_y - 1;

	//Emptying initial position
	result_field->barley[result_field->position_y][result_field->position_x] = 0;

	return result_field;
}


void free_field
    (barley_field_t * restrict field)
{
    for (size_t row = 0; row < field->size_y; row++)
        free(field->barley[row]);
    
    free(field->barley);
    free(field);
}

void print_field
	(const barley_field_t * restrict field)
{
	for (size_t row = 0; row < field->size_y; row++)
	{
		for (size_t col = 0; col < field->size_x; col++) //Print top of cell
		{
			if (field->barley[row][col] == 0)
				printw("      ");
			else
				printw(" ---  ");
		}
		printw("\n");

		for (size_t col = 0; col < field->size_x; col++) //Print middle of cell
		{
			if (field->barley[row][col] == 0)
				printw("      ");
			else
				printw("| %-2d| ", field->barley[row][col]);
		}
		printw("\n");

		for (size_t col = 0; col < field->size_x; col++) //Print bottom of cell
		{
			if (field->barley[row][col] == 0)
				printw("      ");
			else
				printw(" ---  ");
		}
		printw("\n");

		refresh();
	}
}

void barley_move
    (barley_field_t * restrict field,
     const KEYBOARD dir)
{
	if (dir == UP && field->position_y != field->size_y - 1)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y + 1][field->position_x];

		field->position_y += 1;

		field->barley[field->position_y][field->position_x] = 0;
	}
	if (dir == DOWN && field->position_y != 0)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y - 1][field->position_x];

		field->position_y -= 1;

		field->barley[field->position_y][field->position_x] = 0;
	}
	if (dir == LEFT && field->position_x != field->size_x- 1)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y][field->position_x + 1];

		field->position_x += 1;

		field->barley[field->position_y][field->position_x] = 0;
	}
	if (dir == RIGHT && field->position_x != 0)
	{
		field->barley[field->position_y][field->position_x] = field->barley[field->position_y][field->position_x - 1];

		field->position_x -= 1;

		field->barley[field->position_y][field->position_x] = 0;
	}
}

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max)
{
   return (min + rand() % (min - (max + 1)));
}