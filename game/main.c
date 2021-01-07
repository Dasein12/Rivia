#include "Header.h"

SDL_Surface* screen = NULL;
int main(void)
{
	initEverything();
	loadLevels();
	paintMenu(screen);
	closeEverything();
	return 0;
}


/**
 * Inits the libraries we're going to use
 */
void initEverything()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	//Mix_Init(MIX_INIT_MP3);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	screen = SDL_SetVideoMode(800, 600, 0, SDL_HWSURFACE);
	SDL_WM_SetCaption("Wizards of War", NULL);
}
/**
 * Clean everything before we exit the game
 */
void closeEverything()
{
	//atexit(Mix_Quit);
	atexit(IMG_Quit);
	atexit(TTF_Quit);
	atexit(SDL_Quit);
}
