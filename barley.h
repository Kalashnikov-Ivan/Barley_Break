#ifndef stdint.h
	#include <stdint.h> //For uint8_t and so on...
#endif

//-----------------Types-------------------
typedef enum CONTROL_KEYBOARD
{ 
    UP = KEY_UP, DOWN = KEY_DOWN, LEFT = KEY_LEFT, RIGHT = KEY_RIGHT, EXIT = 'q', RESTART = 'r'
} KEYBOARD;

typedef struct 
{
	int16_t ** restrict barley;
	size_t size_x, position_x;
	size_t size_y, position_y;
} __attribute__((packed)) barley_field_t;

//---------------Functions-----------------

//----------Field------------
barley_field_t* init_field
    (const size_t size_x,
     const size_t size_y);

void free_field
    (barley_field_t * restrict field);

void print_field
	(const barley_field_t * restrict field);

bool barley_move
    (barley_field_t * restrict field,
     const KEYBOARD dir);

bool check_win
	(const barley_field_t * restrict field);

//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);

void print_welcome();
void print_instruction();
void print_win
    (const uint32_t moves);