#include "SDL/SDL.h"

#include "cell.h"


#define BLOCK_HEIGHT 20
#define BLOCK_WIDTH 20

#define EXTRA_WIDTH 100
#define EXTRA_HEIGHT 40

/*
 * Initialiseert onder andere het venster waarin het speelveld getoond zal worden.
 * Deze functie moet gecalled worden aan het begin van het spel, vooraleer je
 * de spelwereld begint te tekenen.
 */
void initialize_gui();


/*
 * Tekent het huidige veld in het venster. Deze functie moeten jullie dus zelf implementeren.
 */
void draw_field(int score, enum Group group);

enum Keyboard check_keyboard_input(enum Keyboard toets);

void clear_screen();

SDL_Surface *loadImage(char *name);
