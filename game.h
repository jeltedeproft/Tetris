#ifndef GAME_H_
#define GAME_H_

#include "field.h"


/*
 * Het aantal generaties dat het programma moet blijven draaien.
 * Je mag dit getal aanpassen om het spel langer of minder lang te laten draaien.
 */
#define NUMBER_OF_GENERATIONS 100

enum Keyboard{
	KEY_NONE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};

extern int score;


/*
 * Dit is de functie waarin de basislogica van het spel wordt vastgelegd.
 * Deze functie bepaalt hoe elke cel moet evolueren naar de volgende generatie:
 * voor elke positie in het grid moet nagegaan worden of de cel op die positie
 * van staat moet veranderen of ongewijzigd moet blijven.
 */
void do_next_generation();

void move_stukje(enum Keyboard toets);
void remove_line(int line_number);
void check_volle_lijn();
void wissel_stukje();
void schuif_blok_links();
void schuif_blok_rechts();
void roteer_blok(int j, int k,enum Group group,enum Orientation orientation);

int get_living_cells_around(int i, int j);

enum Group get_group_most_neighbours(int i, int j);

#endif /* GAME_H_ */
