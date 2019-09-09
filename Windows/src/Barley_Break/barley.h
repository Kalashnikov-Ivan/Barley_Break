#pragma once

#ifndef _GCC_WRAP_STDINT_H
	#include <stdint.h> //For uint8_t and so on...
#endif

//-----------------Types-------------------
typedef enum CONTROL_KEYBOARD
{ 
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, EXIT = 'q', RESTART = 'r'
} KEYBOARD;

typedef struct 
{
	int16_t ** barley;
	size_t size_x, position_x;
	size_t size_y, position_y;

    uint16_t chaos;
} barley_field_t;

//---------------Functions-----------------

//----------Field------------
barley_field_t* init_field
    (const size_t size_x,
     const size_t size_y);

void free_field
    (barley_field_t * field);

bool check_chaos
    (const barley_field_t * field);

bool check_chaos2
    (const  barley_field_t * field);

bool barley_move
    (barley_field_t * field,
     const KEYBOARD dir);

bool check_win
	(const barley_field_t * field);

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);

void print_field
	(const barley_field_t* field);

void print_welcome();
void print_instruction();
void print_win
    (const uint32_t moves);

/* <----MUSIC---->   */
void Beethoven();