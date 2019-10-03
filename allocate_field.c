/*
 * allocate_field.c

 *
 *  Created on: Dec 12, 2015
 *      Author: jelte
 */

#include <stdlib.h>
#include <stdio.h>

#include "allocate_field.h"
#include "field.h"



//niet veel verschillend hier met vorige versie

struct Cell ***allocate_field(int field_width, int field_height){
	struct Cell*** kolommen = malloc(field_width * sizeof *kolommen);

	int i;
	int j;

	for(i=0;i < field_width;i++){
		kolommen[i] = malloc(field_height * sizeof (struct Cell**));
		for(j=0;j < field_height;j++){
			kolommen[i][j] = malloc( sizeof (struct Cell*));
			kolommen[i][j]->state = EMPTY;
			kolommen[i][j]->group = H;
		}
	}
	return kolommen;
}


