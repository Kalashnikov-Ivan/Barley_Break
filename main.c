#include <stdio.h>


#include "barley.h"


int main(void) 
{
	
	barley_field_t * restrict field = init_field(4, 4);

	if (NULL == field)
		return 1;

	print_field(field);

	free_field(field);

	return 0;
}