#ifndef stdint.h
	#include <stdint.h> //For uint8_t and so on...
#endif

//-----------------Types-------------------
typedef enum CONTROL_KEYBOARD
{ 
    UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, EXIT = 113, RESTART = 114
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
	(barley_field_t * restrict field);


//----------Support------------
int32_t get_rand_in_range
    (const int32_t min, 
     const int32_t max);

//----------Field------------

/*void print_instructions
    (void);

//Initialization of field
void initField(int *barley, int lines, int columns, int *posX, int *posY);

//Logic functions
void move(int *barley, int lines, int columns, DIR dir, int *posX, int *posY, int *movesCount);
bool boolCheckWin(int *barley, int lines, int columns);

//Support function
int safeInputNum(int min, int max);*/