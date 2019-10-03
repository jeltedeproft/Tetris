#include "GUI.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <stdbool.h>
#include "field.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <stdlib.h>
#include "game.h"

int FIELD_WIDTH;
int FIELD_HEIGHT;
int score;
int HIGHSCORES[10];

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel ten einde komt.
 */
static SDL_Surface *window;
static SDL_Surface *text;
static TTF_Font *font;
static SDL_Rect positie_text = {220,20,60,250};
static SDL_Event event;

//deze functie checkt de keyboard input en verandert de variable "ingedrukte_toets" naargelang
enum Keyboard check_keyboard_input(enum Keyboard ingedrukte_toets){
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_KEYDOWN){
			SDLKey toets = event.key.keysym.sym;

			switch(toets){
				case SDLK_UP:
					ingedrukte_toets = KEY_UP;
					break;
				case SDLK_DOWN:
					ingedrukte_toets = KEY_DOWN;
					break;
				case SDLK_LEFT:
					ingedrukte_toets = KEY_LEFT;
					break;
				case SDLK_RIGHT:
					ingedrukte_toets = KEY_RIGHT;
					break;
				default:
					ingedrukte_toets = KEY_NONE;
					break;
			}
		}
	}
	return ingedrukte_toets;
}
/*
 * Maakt het hele venster terug blanco.
 */
void clear_screen() {
	SDL_FillRect(window, NULL, 0xFFFFFFFF);
	SDL_Flip(window);
}

//tekent het veld, itereert over hte volledige veld, kijkt to welke groep een cel behoort en kleurt nargelang de groep met boxrgba
void draw_field(int score, enum Group volgend_stukje) {
    int i;
    for (i = 0; i < FIELD_HEIGHT; i++) {
   	   int j;
   	   for (j = 0; j < FIELD_WIDTH; j++) {
    		   if(get_group(j,i) == O){
    			      boxRGBA(window,
    			              j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
							  (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
    			              150, 50, 0, 255);
    		   }
    		   else if(get_group(j,i) == I){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              0, 150, 50, 255);
    		   }
    		   else if(get_group(j,i) == S){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              150, 50, 100, 255);
    		   }
    		   else if(get_group(j,i) == Z){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              150, 200, 0, 255);
    		   }
    		   else if(get_group(j,i) == L){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              100, 0, 100, 255);
    		   }
    		   else if(get_group(j,i) == J){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              200, 25, 100, 255);
    		   }
    		   else if(get_group(j,i) == T){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              40, 40, 150, 255);
    		   }
    		   else if(get_group(j,i) == H){
 			      boxRGBA(window,
 			    		 j * BLOCK_WIDTH, i * BLOCK_HEIGHT,
						 (j + 1) * BLOCK_WIDTH, (i + 1) * BLOCK_HEIGHT,
 			              0, 0, 0, 255);
    		   }
       }
   }

    //dit is voor het tekstballonetje , we zetten de score integer om in een string en concateneren hem met de standaardstring, hier heb ik ook het probleem dat clear screen de oude tekst niet verwijderd
   SDL_Color text_color = {255,255,255};
   char scores[15];
   sprintf(scores,"%d",score);
   char default_text[50];
   strcpy(default_text,"your current score = ");
   strcat(default_text,scores);
   text = TTF_RenderText_Solid(font,default_text,text_color);
   SDL_BlitSurface(text,NULL,window,&positie_text);
   SDL_Flip(window);

   // dit is voor het het tonen van het volgende stukje, ik weet niet hoe het komt maar voor de een of andere reden blijven de vorige stukjes op het scherm staan ipv plaats te maken voor het
   //volgende stukje, 2  mogelijkheden, clear_screen werkt niet zoals het moet of ik teken in elke iteratie meer en meer stukjes door een bug in mijn code
   if(volgend_stukje == O){
       			      boxRGBA(window,
       			              (FIELD_WIDTH - 2) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
       			              150, 50, 0, 255);
       			      boxRGBA(window,
       			              (FIELD_WIDTH - 2)  * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
       			              150, 50, 0, 255);
       			      boxRGBA(window,
       			              (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
       			              150, 50, 0, 255);
       			      boxRGBA(window,
       			              (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
       			              150, 50, 0, 255);


       		   }
       		   else if(volgend_stukje == I){
    			      boxRGBA(window,
       			              (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              0, 150, 50, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              0, 150, 50, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
    			              0, 150, 50, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 7) * BLOCK_HEIGHT,
    			              0, 150, 50, 255);
       		   }
       		   else if(volgend_stukje == Z){
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              150, 50, 100, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              150, 50, 100, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 2) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              150, 50, 100, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
							  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              150, 50, 100, 255);
       		   }
       		   else if(volgend_stukje == S){
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              150, 200, 0, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              150, 200, 0, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              150, 200, 0, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 2) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              150, 200, 0, 255);
       		   }
       		   else if(volgend_stukje == L){
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              100, 0, 100, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              100, 0, 100, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 7) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
    			              100, 0, 100, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 2) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              100, 0, 100, 255);
       		   }
       		   else if(volgend_stukje == J){
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              200, 25, 100, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              200, 25, 100, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 7) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
    			              200, 25, 100, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
							  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              200, 25, 100, 255);
       		   }
       		   else if(volgend_stukje == T){
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              40, 40, 150, 255);
    			      boxRGBA(window,
    			    		  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT - 6) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
    			              40, 40, 150, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH + 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
   							  (FIELD_WIDTH + 2) * BLOCK_WIDTH, (FIELD_HEIGHT - 4) * BLOCK_HEIGHT,
    			              40, 40, 150, 255);
    			      boxRGBA(window,
       			              (FIELD_WIDTH - 1) * BLOCK_WIDTH, (FIELD_HEIGHT - 5) * BLOCK_HEIGHT,
							  (FIELD_WIDTH) * BLOCK_WIDTH, (FIELD_HEIGHT -4) * BLOCK_HEIGHT,
    			              40, 40, 150, 255);
       		   }

}




/*
 * Met de functies hieronder moet je nu geen rekening houden:
 * zij verzorgen wat achtergrondlogica die nu voor jullie niet relevant is.
 *
 * Let wel op: de functie initialize_gui moet aangeroepen worden aan de start van het spel.
 */

void initialize_window(char *title) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
		}
	if (TTF_Init() < 0){
		printf("Could not initialize ttf: %s\n", SDL_GetError());
		exit(1);
		}

	int window_width = (FIELD_WIDTH * BLOCK_WIDTH) + EXTRA_WIDTH;
	int window_height = (FIELD_HEIGHT * BLOCK_HEIGHT) + EXTRA_HEIGHT;  //extra ruimte voor score en volgend stukje
	window = SDL_SetVideoMode(window_width, window_height, 0, SDL_HWPALETTE | SDL_DOUBLEBUF);
	font = TTF_OpenFont("FreeSans.ttf",24); //lettertype tekst
	if (window == NULL) {
		printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
		exit(1);
	}
	if (font == NULL) {
		printf("Couldn't set font: %s\n", SDL_GetError());
		exit(1);
	}
	/* Set the screen title */
	SDL_WM_SetCaption(title, NULL);
}

void cleanup() {
	/* Shut down SDL */
	SDL_Quit();

	/* shut down ttf */
	TTF_Quit();

	cleanup_cells();  //deze functie free't het memory dat door malloc werd aangeroepe voor de cellen

	HIGHSCORES[2] = score;
}

void initialize_gui() {
	initialize_window("Conway's Game of Life");
	atexit(cleanup);
}


