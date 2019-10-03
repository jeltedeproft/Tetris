/*
 * allocate_field.h
 *
 *  Created on: 09 Oct 2015
 *      Author: mvdcamme
 */

#ifndef ALLOCATE_FIELD_H_
#define ALLOCATE_FIELD_H_

#include "cell.h"



/*
 * Alloceert dynamisch het speelveld. Dit speelveld is een tweedimensionale array van pointers naar Cellen.
 * De array moet als breedte field_width en als hoogte field_height hebben. Met andere woorden, de lengte
 * van de eerste array is gelijk aan field_width en de lengte van de tweede array is gelijk aan field_height;
 */
struct Cell ***allocate_field(int field_width, int field_height);

#endif /* ALLOCATE_FIELD_H_ */
