#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "GUI.h"
#include "field.h"
#include "cell.h"

int FIELD_WIDTH = 20;
int FIELD_HEIGHT = 30;
enum Group  volgend_stukje = T;
enum Keyboard ingedrukte_toets = KEY_NONE;

static struct Blokje huidig_blokje = {5,0};

int score = 0;

/*
 * Zorgt ervoor dat het programma tijdelijk pauzeert (en helemaal niets doet) voor een periode gelijk
 * aan het gegeven aantal seconden plus milliseconden.
 * Het is handig om deze functie te callen bij het overgaan van de ene generatie op de andere zodat het programma
 * niet meteen klaar is en alle generaties niet te snel na elkaar in de console worden geprint.
 *
 * Aan deze functie moeten jullie ook zeker niets aanpassen.
 */
static void sleep(int nr_of_seconds, int nr_of_milliseconds) {
	struct timespec *sleep_time = malloc(sizeof(struct timespec));
	sleep_time->tv_sec = nr_of_seconds;
	sleep_time->tv_nsec = nr_of_milliseconds * 1000 * 1000;
	struct timespec *remainder_sleep_time = malloc(sizeof(struct timespec));
	nanosleep(sleep_time, remainder_sleep_time);
}

int main(int argc, char *argv[]) {

	srand(time(NULL)); //set random seed


	/* initialiseer het veld*/
	initialize_field(FIELD_WIDTH, FIELD_HEIGHT);

	//deze functie moet aan het begin van het spel aangeroepen worden
	initialize_gui();


	//command line argument word nu gebruikt voor de highscores in op te slagen
	if (argc == 2){
		load_highscores(argv[1]);
	}


	//laad het eerste stukje in
	wissel_stukje();

	field_end_generation();

	//deze functie tekent het veld, de score en het volgende stukje
	draw_field(score, volgend_stukje);


	while (check_eindconditie(FIELD_WIDTH, FIELD_HEIGHT)){


		while(!(stukje_niet_geland(FIELD_WIDTH, FIELD_HEIGHT))){

			/*voer interne onderhoudsfunctie uit*/
			field_start_generation();

			/*we checken voor keyboard input, indien er een toets is ingedrukt, roepen we move_stukje op met de ingedrukte toets als argument*/
			ingedrukte_toets = check_keyboard_input(ingedrukte_toets);
			if (ingedrukte_toets == KEY_LEFT){
				schuif_blok_links();
			}
			else if(ingedrukte_toets == KEY_RIGHT){
				schuif_blok_rechts();
			}
			else if(ingedrukte_toets == KEY_UP){
				move_stukje(ingedrukte_toets);
			}
			else if(ingedrukte_toets == KEY_DOWN){
				do_next_generation();               //druk pijltje omlaag = zak een lijn
			}
			ingedrukte_toets = KEY_NONE;


			/*zet volgende generatie klaar*/
			do_next_generation();

			/*voer interne onderhoudsfunctie uit*/
			field_end_generation();

			void clear_screen();

			/*print deze generatie uit*/
			draw_field(score,volgend_stukje);

			/*we gaan afwisselend slapen, en checken voor toetsenbord input, dit staat ons toe om de orientatie van het blokje meerdere keren te wijzigen in 1 lus*/
			sleep(0,100);

			ingedrukte_toets = check_keyboard_input(ingedrukte_toets);
			if (ingedrukte_toets == KEY_LEFT){
				schuif_blok_links();
			}
			else if(ingedrukte_toets == KEY_RIGHT){
				schuif_blok_rechts();
			}
			else if(ingedrukte_toets == KEY_UP){
				move_stukje(ingedrukte_toets);
			}
			else if(ingedrukte_toets == KEY_DOWN){
				do_next_generation();               //druk pijltje omlaag = zak een lijn
			}
			ingedrukte_toets = KEY_NONE;
			void clear_screen();
			field_end_generation();
			draw_field(score,volgend_stukje);


			sleep(0,100);


			ingedrukte_toets = check_keyboard_input(ingedrukte_toets);
			if (ingedrukte_toets == KEY_LEFT){
				schuif_blok_links();
			}
			else if(ingedrukte_toets == KEY_RIGHT){
				schuif_blok_rechts();
			}
			else if(ingedrukte_toets == KEY_UP){
				move_stukje(ingedrukte_toets);
			}
			else if(ingedrukte_toets == KEY_DOWN){
				do_next_generation();               //druk pijltje omlaag = zak een lijn
			}
			ingedrukte_toets = KEY_NONE;
			void clear_screen();
			field_end_generation();
			draw_field(score,volgend_stukje);

		}
		dood_gelande_cellen();

		//controleert of er een volle lijn is gevormd
		check_volle_lijn();

		/*deze functie zet net nieuwe stukje in het veld en maakt het nieuwe volgende stukje aan*/
		wissel_stukje();

		field_end_generation();
	}
	return EXIT_SUCCESS;
}

void wissel_stukje(){
	switch(volgend_stukje){  // in deze functie staat voor elk type blokje welke vakjes moeten ingevuld worden relatief ten opzichte van de veldafmetingen,
							 // we vullen ook de x en y coordinaten van het rotatiecentrum voor elk blokje in, dit gebeurt in een aparte structure genaam blokje
		case O:
			resurrect_cell((FIELD_WIDTH / 2),0,O,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,0,O,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,O,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,1,O,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 1;
			break;
		case I:
			resurrect_cell((FIELD_WIDTH / 2),0,I,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,I,UP);
			resurrect_cell((FIELD_WIDTH / 2),2,I,UP);
			resurrect_cell((FIELD_WIDTH / 2),3,I,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 0;
			break;
		case S:
			resurrect_cell((FIELD_WIDTH / 2),0,S,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,0,S,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,S,UP);
			resurrect_cell((FIELD_WIDTH / 2) - 1,1,S,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 1;
			break;
		case Z:
			resurrect_cell((FIELD_WIDTH / 2),0,Z,UP);
			resurrect_cell((FIELD_WIDTH / 2) - 1,0,Z,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,Z,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,1,Z,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 1;
			break;
		case L:
			resurrect_cell((FIELD_WIDTH / 2),0,L,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,L,UP);
			resurrect_cell((FIELD_WIDTH / 2),2,L,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,2,L,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 1;
			break;
		case J:
			resurrect_cell((FIELD_WIDTH / 2),0,J,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,J,UP);
			resurrect_cell((FIELD_WIDTH / 2),2,J,UP);
			resurrect_cell((FIELD_WIDTH / 2) - 1,2,J,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 1;
			break;
		case T:
			resurrect_cell((FIELD_WIDTH / 2),0,T,UP);
			resurrect_cell((FIELD_WIDTH / 2) - 1,0,T,UP);
			resurrect_cell((FIELD_WIDTH / 2) + 1,0,T,UP);
			resurrect_cell((FIELD_WIDTH / 2),1,T,UP);
			huidig_blokje.rotatiecentrum_x = (FIELD_WIDTH / 2);
			huidig_blokje.rotatiecentrum_y = 0;
			break;
		case H:
			printf("verkeerd bloktype geselecteerd");
			break;
	}
	volgend_stukje = rand() % 7; // we kiezen een wilekeurig stukje uit de 7 verschillende als nieuwe volgende
}

//deze functie is veranwtoordelijk voor het naar beneden schuiven van het huidig actieve blokje, deze functie gebeurt automatisch maar kan ook opgeroepen worden door de beneden pijl toets
void do_next_generation(){
	int j = 0;
	while(j < FIELD_WIDTH){
		int k = FIELD_HEIGHT - 1;    //we vertrekken van onderaan het veld, zodat we niet meerdere keren na mekaar het zelfde blokje resurrecte / killen
		while(k >= 0 ){
			enum State state = get_state(j, k);
			enum Group group = get_group(j, k);
			enum Orientation orientation = get_orientation(j, k);
			if (state == ALIVE ) {
				if((k + 1) < FIELD_HEIGHT){
					enum State state_next_line = get_state(j, k + 1); //onder ons bevind zich een blokje ==> stop met bewegen , we zijn geland
					if (state_next_line == DEAD){
						j = 10000; break;
					}
				}
				else if((k + 1) >= FIELD_HEIGHT){  // ondre ons bevind zich het einde van het veld ==> stop met bewegen, geland
					j = 10000; break;
				}
				empty_cell(j,k); //dood deze cel
				resurrect_cell(j,k + 1,group,orientation); //resurect de cel op de volgende lijn (geeft de illusie dat het blok naar beneden schuift
				}
			k = k - 1;
		}
		j = j + 1;
	}

	if(huidig_blokje.rotatiecentrum_y < (FIELD_HEIGHT - 1)){
		huidig_blokje.rotatiecentrum_y = (huidig_blokje.rotatiecentrum_y) + 1;  //hier passen we het rotatiecentrum aan dat nu 1 vakje lager ligt
	}
}

//deze functie controleert of er een volle lijn is, ze itereert over elke rij en zodra er een leeg vakje is gevonden stop het met zoeken en gaat het naar de volgende rij
void check_volle_lijn(){
	int j = 0;
	while(j < FIELD_HEIGHT){
		int k = 3;
		while(k < FIELD_WIDTH - 2){
			enum State state = get_state(k, j);
			if (state == EMPTY ) {
				break;          //indien er een gaatje is in de lijn, mag ze niet weggehaald worden
				}
			if (k == (FIELD_WIDTH - 3)){
				remove_line(j);            //indien de check helemaal tot op het einde van de lijn geraakt, hebben we een volle lijn en mag ze verwijderd worden
			}
			k = k + 1;
		}
		j = j + 1;
	}
}

void remove_line(int line_number){
	int i = 3;
	while (i < FIELD_WIDTH - 2){
		empty_cell(i,line_number);  //we verwijderen eerst de desbetreffende lijn
		i = i + 1;
	}

	int j = line_number - 1;       //we vertrekken 1 lijn boven de verdwenen lijn
	while(j >= 0){
		int k = 3;
		while(k < FIELD_WIDTH - 3){    // en schuifen elke rij 1 rij naar onder
			enum Group group = get_group(k, j);
			enum Orientation orientation = get_orientation(k, j);
			enum State state = get_state(k,j);

			if(state == EMPTY){
				empty_cell(k,j+1);
			}
			else{
				kill_cell(k,j + 1,group,orientation);
			}
			k = k + 1;
		}
		j = j - 1;
	}
	score = score + 50;  //we hebben punten verdiend, update de score
}

//deze functie is onrechtsreeks verantwoordelijk voor de rotaite, het roept eigenlijk enkel roteer_blok op
void move_stukje(enum Keyboard toets){
	int j = 0;
	while(j < FIELD_WIDTH){
		int k = 0;
		while(k < FIELD_HEIGHT){
			enum State state = get_state(j, k);
			enum Group group = get_group(j, k);
			enum Orientation orientation = get_orientation(j, k);
			if (state == ALIVE ) {
				switch(toets){
				case KEY_UP:
					roteer_blok(j,k,group,orientation);                      //druk pijltje omhoog = roteer
					break;
				case KEY_RIGHT:
					break;
				case KEY_DOWN:
					break;
				case KEY_LEFT:
					break;
				case KEY_NONE:
					break;
				}
			}
			k = k + 1;
		}
		j = j + 1;
	}
}

//de roteer blok functie word opgeroepen voor elk vakje dat levend is, merk op dat ik hier eerst controleer of het blokje dezelfde coordinaten heeft als het rotatiecentrum, zoja gebruiken we dit vakje als centrum,,
//en vervolgens pas alle berekeningen uitvoer relatief ten opzichte van dit rotatiecentrum.
//de reden voor deze redelijk complexe werkwijze is dat ik door het veld op deze manier te coderen, ik nu eenmaal over elke vakje moet gaan en wanneer ik dan een actie moet uitvoeren op een groep
//vakjes ik 1 vakje als relatief centrum gebruik.
void roteer_blok(int j, int k,enum Group group,enum Orientation orientation){
	int x = huidig_blokje.rotatiecentrum_x;
	int y = huidig_blokje.rotatiecentrum_y;

	enum Orientation nieuwe_orientatie = ((get_orientation(j,k) + 1) % 4); //we hebben geroteerd, dus de orientatie veranderd 1 plaatsje verder UP,RIGHT,DOWN,LEFT
	set_orientation(j,k,nieuwe_orientatie);

	if ((j == x ) && (k == y)){ //hier contorleren we of we met het rotatiecentrum te maken hebben, of een ander levend vakje van het blokje
		switch(group){  //we definieren voor elk type  + orientatie welke cellen leeggemaakt of geresurect moeten worden, waarschijnlijk niet de optimale manier om dit te doen.
		case O:
			break;
		case I:
			if (orientation == DOWN || orientation == UP){
				if ((j > FIELD_WIDTH - 3) || (j < 4)){
					set_orientation(j,k + 1,orientation);     // in het geval dat we niet mogen roteren, omdat we bvb tegen een muur aanleunen en niet kunnen draaien
					set_orientation(j,k + 2,orientation);     // moeten we onze operatie afbreken met break, en de verandering in rotatie die we reeds preventief hadden uitgevoerd, ongedaan maken
					set_orientation(j,k + 2,orientation);     //set rotation zet de rotatie terug op de oorspronkelijke rotatie
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k + 1);
				empty_cell(j,k + 2);
				empty_cell(j,k + 3);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);   // deze lijnen zijn verantwoordelijk voor het dode en tot leven wekken van de gepaste cellen
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);   // om het rechtopstaand I blok om te zetten in een liggend I blok
				resurrect_cell(j + 2,k,group,nieuwe_orientatie);
				break;
			}
			else{
				if (k > FIELD_HEIGHT - 4){
					set_orientation(j - 1,k,orientation);
					set_orientation(j + 1,k,orientation);
					set_orientation(j + 2,k,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j - 1,k);
				empty_cell(j + 1,k);
				empty_cell(j + 2,k);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j,k + 2,group,nieuwe_orientatie);
				resurrect_cell(j,k + 3,group,nieuwe_orientatie);
				break;
			}
		case S:
			if (orientation == DOWN) {
				empty_cell(j - 1,k + 1);
				empty_cell(j + 1,k);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == UP) {
				empty_cell(j - 1,k);
				empty_cell(j + 1,k - 1);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == LEFT) {
				if (j >= (FIELD_WIDTH - 3)){
					set_orientation(j - 1,k,orientation);
					set_orientation(j - 1,k - 1,orientation);
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j - 1,k - 1);
				empty_cell(j,k + 1);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == RIGHT) {
				if (j <= 3){
					set_orientation(j,k - 1,orientation);
					set_orientation(j + 1,k,orientation);
					set_orientation(j,k + 2,orientation);
					set_orientation(j + 1,k + 1,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k - 1);
				empty_cell(j + 1,k + 1);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else break;
		case Z:
			if (orientation == DOWN) {
				empty_cell(j,k + 1);
				empty_cell(j + 1,k + 1);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == UP) {
				empty_cell(j - 1,k - 1);
				empty_cell(j,k - 1);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == LEFT) {
				if (j >= (FIELD_WIDTH - 3)){
					set_orientation(j,k - 1,orientation);
					set_orientation(j - 1,k,orientation);
					set_orientation(j - 1,k + 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j - 1,k);
				empty_cell(j - 1,k + 1);
				resurrect_cell(j - 1,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == RIGHT) {
				if (j <= 3){
					set_orientation(j + 1,k,orientation);
					set_orientation(j + 1,k - 1,orientation);
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j+ 1,k);
				empty_cell(j + 1,k - 1);
				resurrect_cell(j + 1,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				break;
			}
			else break;
		case L:
			if (orientation == DOWN) {
				if (j >= (FIELD_WIDTH - 3)){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j - 1,k - 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k + 1);
				empty_cell(j,k - 1);
				empty_cell(j - 1,k - 1);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == UP) {
				if (j <= 3){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j + 1,k + 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k - 1);
				empty_cell(j,k + 1);
				empty_cell(j + 1,k + 1);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == LEFT) {
				empty_cell(j + 1,k);
				empty_cell(j - 1,k);
				empty_cell(j + 1,k - 1);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == RIGHT) {
				empty_cell(j+ 1,k);
				empty_cell(j - 1,k);
				empty_cell(j - 1,k + 1);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else break;
		case J:
			if (orientation == DOWN) {
				if (j <= 3){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j + 1,k - 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k - 1);
				empty_cell(j,k + 1);
				empty_cell(j + 1,k - 1);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == UP) {
				if (j >= (FIELD_WIDTH - 3)){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j - 1,k + 1,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k + 1);
				empty_cell(j,k - 1);
				empty_cell(j - 1,k + 1);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == LEFT) {
				empty_cell(j + 1,k);
				empty_cell(j - 1,k);
				empty_cell(j + 1,k + 1);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j - 1,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == RIGHT) {
				empty_cell(j + 1,k);
				empty_cell(j - 1,k);
				empty_cell(j - 1,k - 1);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				resurrect_cell(j + 1,k - 1,group,nieuwe_orientatie);
				break;
			}
			else break;
		case T:
			if (orientation == DOWN) {
				empty_cell(j - 1,k);
				resurrect_cell(j,k + 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == UP) {
				empty_cell(j + 1,k);
				resurrect_cell(j,k - 1,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == LEFT) {
				if (j <= 3){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j + 1,k,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k - 1);
				resurrect_cell(j - 1,k,group,nieuwe_orientatie);
				break;
			}
			else if(orientation == RIGHT) {
				if (j >= (FIELD_WIDTH - 3)){
					set_orientation(j,k + 1,orientation);
					set_orientation(j,k - 1,orientation);
					set_orientation(j - 1,k,orientation);
					set_orientation(j,k,orientation);
					break;  //we zitten te dicht tegen de rand om te roteren
				}
				empty_cell(j,k + 1);
				resurrect_cell(j + 1,k,group,nieuwe_orientatie);
				break;
			}
			else break;
		case H:
			break;
		}
	}
}

void schuif_blok_rechts(){
	int rechts_niet_meer_mogelijk = 0;  //deze int houd bij wanneer we niet meer naar rechts mogen bewegen
	int j = FIELD_WIDTH - 1;
	while(j >= 0){
		int k = 0;
		while(k < FIELD_HEIGHT){
			enum State state = get_state(j, k);
			enum Group group = get_group(j, k);
			enum Orientation orientation = get_orientation(j, k);
			if (state == ALIVE) {
				if (j >= (FIELD_WIDTH - 3)){
					j = k = 0; rechts_niet_meer_mogelijk = 1; break;    //deze lijn is om te ontsnappen uit de dubbele while loop wanneer we vaststellen dat het blokje zich aan de rechterkant bevind
				}

				enum State state_ernaast = get_state(j + 1, k);
				if (state_ernaast == DEAD){
					j = k = 0; rechts_niet_meer_mogelijk = 1; break;   //deze lijn is om te ontsnappen uit de dubbele while loop wanneer we vaststellen dat het blokje tegen een ander blokje zit
				}
				resurrect_cell(j + 1,k,group,orientation); //alles is ok, beweeg naar rechts
				empty_cell(j,k);
			}
			k = k + 1;
		}
		j = j - 1;
	}
	if(rechts_niet_meer_mogelijk == 0){
		huidig_blokje.rotatiecentrum_x = (huidig_blokje.rotatiecentrum_x) + 1;
	}
}

void schuif_blok_links(){
	int links_niet_meer_mogelijk = 0;
	int j = 0;
	while(j < FIELD_WIDTH){
		int k = 0;
		while(k < FIELD_HEIGHT){
			enum State state = get_state(j, k);
			enum Group group = get_group(j, k);
			enum Orientation orientation = get_orientation(j, k);
			if (state == ALIVE) {
				if (j <= 3){
					j = k = 10000; links_niet_meer_mogelijk = 1; break;    //deze lijn is om te ontsnappen uit de dubbele while loop wanneer we vaststellen dat het blokje zich aan de linkerkant bevind
				}

				enum State state_ernaast = get_state(j - 1, k);
				if (state_ernaast == DEAD){
					j = k = 10000; links_niet_meer_mogelijk = 1; break;   //deze lijn is om te ontsnappen uit de dubbele while loop wanneer we vaststellen dat het blokje naas teen ander blokje zit
				}
				resurrect_cell(j - 1,k,group,orientation);
				empty_cell(j,k);
			}
			k = k + 1;
		}
		j = j + 1;
	}
	if(links_niet_meer_mogelijk == 0){
		huidig_blokje.rotatiecentrum_x = (huidig_blokje.rotatiecentrum_x) - 1;
	}
}


