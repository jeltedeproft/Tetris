/*
 * field.h
 *
 *  Created on: 07 Oct 2015
 *      Author: mvdcamme
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "allocate_field.h"


/*
 * Zoals beschreven in de opgave zijn FIELD_WIDTH en FIELD_HEIGTH nu geen macro's meer,
 * maar zijn ze externe variabelen die in bv. field.c geïmplementeerd worden.
 */
extern int FIELD_WIDTH;
extern int FIELD_HEIGHT;
extern int HIGHSCORES[];
extern enum Group volgend_stukje;

/*
 * Initialiseert en populeert het veld met lege cellen.
 */
void initialize_field(int field_width, int field_height);


void load_highscores(const char *file_path);

int check_eindconditie();

int stukje_niet_geland(int field_width, int field_height);

enum State get_orientation(int x, int y);

void set_orientation(int x, int y, enum Orientation orientation);


void initialize_field_tekst_file(FILE *tekstfile,int FIELD_WIDTH, int FIELD_HEIGHT);
/*
 * Geeft je de groep terug van de cel die zich bevindt op positie (x,y) in het veld.
 */
enum Group get_group(int x, int y);

/*
 * Geeft je de staat (i.e., levend of dood) terug van de cel die zich bevindt op positie (x,y) in het veld.
 */
enum State get_state(int x, int y);


/*
 * Wekt de cel op positie (x,y) tot leven laat ze toebehoren aan de gegeven groep.
 */
void resurrect_cell(int x, int y, enum Group group, enum Orientation orientation);

/*
 * Doodt de cel op op positie(x,y).
 */
void kill_cell(int x, int y,enum Group group, enum Orientation orientation);


 //maakt een cel leeg
void empty_cell(int x, int y);

void dood_gelande_cellen();


/*
 * Onderstaande functies doen wat interne bookkeeping, waar je je nu geen zorgen over moet maken.
 * Let wel op: de functie field_start_generation moet wel gecalled worden voor je de do_next_generation
 * functie uit game.c callet, en de field_end_generation moet gecalled worden nadat je do_next_generation
 * gecalled hebt.
 */
void field_start_generation();
void field_end_generation();

void cleanup_cells();

#endif /* FIELD_H_ */
