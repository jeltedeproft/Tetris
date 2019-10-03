#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "field.h"

//we moeten deze variabelen nog definieren aangezien ze enkel gedeclareerd zijn in field.h
int FIELD_WIDTH;
int FIELD_HEIGHT;
int HIGHSCORES[10] = {0,0,0,0,0,0,0,0,0,0};

//deze functie zorgt voor het "neerslagen" van de blokjes die geland zijn, itereert over het veld en verandert alle levende blokjes in dode
void dood_gelande_cellen(){
	int j = 0;
	while(j < FIELD_WIDTH){
		int k = 0;
		while(k < FIELD_HEIGHT ){
			enum Group group = get_group(j, k);
			enum State state = get_state(j, k);
			enum Orientation orientation = get_orientation(j, k);
			if (state == ALIVE ) {
				kill_cell(j,k,group,orientation);
			}
			k = k + 1;
		}
		j = j + 1;
	}
}

//deze functie controleert of het spel ten einde is, namelijk : 1) is het blokje geland en 2) bevind een onderdeel van dat blokje zich op de bovenste lijn(0)
int check_eindconditie(int field_width, int field_height){
	int j = 0;
	while(j < field_width){
		int k = 0;
		while(k < field_height ){
			enum State state = get_state(j, k);
			if ((state == DEAD ) && (k == 0)) {
				return 0;
			}
			k = k + 1;
		}
		j = j + 1;
	}
	return 1;
}

//checkt of het stukje geland is, een stukje is geland als het zelf levend is en onder hem een dood blokje zit
int stukje_niet_geland(int field_width, int field_height){
	int j = 0;
	while(j < field_width){
		int k = 0;
		while(k < field_height ){
			enum State state = get_state(j, k);
			if (state == ALIVE ) {
				if (k == field_height - 1){
					return 1;
				}
				else{
					enum State state_volgende_lijn = get_state(j, k + 1);
					if (state_volgende_lijn == DEAD){
						return 1;
					}
				}

			}
			k = k + 1;
		}
		j = j + 1;
	}
	return 0;
}

//deze functie leest de highscores in van de externe file
void load_highscores(const char *file_path){
	//eerst creeeren we een buffer voor het opslagen van de ingelezen lijnen/karakters
	char buff[255];

	//vervolgens openen we het tekstbestand en stoppen het in de file *VELDTEKST
	FILE *VELDTEKST = fopen("highscores.txt", "r");

	int i = 0;
	while(fgets(buff, 255, (FILE*) VELDTEKST ) != NULL){
		HIGHSCORES[i] = atoi(buff);  //vul de aray highscores met de waarden uit het tekstbestand
	}
	if (feof((FILE*) VELDTEKST)){
		fclose(VELDTEKST);
	}
}


/*
 * Aan onderstaande twee variabelen moet je nu geen aandacht besteden.
 */
static struct Cell ***field;
static struct Cell ***next_field;

/*
 * Onderstaande twee functies vinden beide de cel op de gegeven positie (x,y) in het veld terug.
 * Jullie hebben deze functies nodig om de nog niet geïmplementeerde functies in deze file af te werken.
 * Het verschil tussen beide functies is niet belangrijk voor jullie. In de vier functies die jullie
 * in deze file moeten implementeren (get_group, get_state, resurrect_cell en kill_cell) werd al aangegeven
 * welke van deze twee functies gebruikt moet worden.
 */
static struct Cell *get_cell(int x, int y) {
	struct Cell **column = field[x];
	struct Cell *cell = column[y];
	return cell;
}

static struct Cell *get_cell_next(int x, int y) {
	struct Cell **column = next_field[x];
	struct Cell *cell = column[y];
	return cell;
}

enum Group get_group(int x, int y) {
	return get_cell(x, y)->group;
}

enum State get_state(int x, int y) {
    return get_cell(x, y)->state;
}

enum State get_orientation(int x, int y) {
    return get_cell(x, y)->orientation;
}

void set_orientation(int x, int y, enum Orientation orientation) {
	struct Cell *cell = get_cell_next(x, y);
    cell->orientation = orientation;
}

void resurrect_cell(int x, int y, enum Group group, enum Orientation orientation) {
	struct Cell *cell = get_cell_next(x, y);
	cell->state = ALIVE;
	cell->group = group;
	cell->orientation = orientation;
}

void kill_cell(int x, int y,enum Group group, enum Orientation orientation) {
	struct Cell *cell = get_cell_next(x, y);
	cell->state = DEAD;
	cell->group = group;
	cell->orientation = orientation;
}

void empty_cell(int x, int y) {
	struct Cell *cell = get_cell_next(x, y);
	cell->state = EMPTY;
	cell->group = H;
}

void initialize_field(FIELD_WIDTH, FIELD_HEIGHT) {
	field = allocate_field(FIELD_WIDTH, FIELD_HEIGHT);
	next_field = allocate_field(FIELD_WIDTH, FIELD_HEIGHT);

	//Onderstaande lijn moet blijven staan.
	field_end_generation();
}

/*
 * Aan de onderstaande drie functies moet je nu geen aandacht besteden, die doen enkel wat interne boekhouding.
 */
static void copy_field(struct Cell ***from_field, struct Cell ***to_field) {
	int x, y;
	for (x = 0; x < FIELD_WIDTH; x++) {
		for (y = 0; y < FIELD_HEIGHT; y++) {
			to_field[x][y]->group = from_field[x][y]->group;
			to_field[x][y]->state = from_field[x][y]->state;
			to_field[x][y]->orientation = from_field[x][y]->orientation;
		}
	}
}

void field_start_generation() {
	copy_field(field, next_field);
}

void field_end_generation() {
	copy_field(next_field, field);
}

//deze functie free't het geheuge dat gealloceerd werd met malloc
void cleanup_cells(){
	int i;
	int j;

	for(i=0;i < FIELD_WIDTH;i++){
		for(j=0;j < FIELD_HEIGHT;j++){
			free(field[i][j]);
			free(next_field[i][j]);
		}
		free(field[i]);
		free(next_field[i]);
	}
	free(field);
	free(next_field);
}




















