#include "Header.h"
bool shouldPassToNextLevel = false;
void paintMenu(SDL_Surface* screen)
{
	SDL_EnableKeyRepeat(0, 0);
	SDL_Surface	*background = NULL;
	SDL_Surface	*cursor = NULL;
	SDL_Rect	wandpos;
	SDL_Rect	backpos;
	SDL_Event	event;
	int position = 1;
	backpos.x = 0;
	backpos.y = 0;
	wandpos.x = 550;
	wandpos.y = 160;
	background = IMG_Load("image/MenuBackground.png");
	cursor = IMG_Load("image/MenuCursor.png");
	while (1)
	{

		SDL_BlitSurface(background, NULL, screen, &backpos);
		SDL_BlitSurface(cursor, NULL, screen, &wandpos);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			SDL_FreeSurface(screen);
			SDL_FreeSurface(background);
			SDL_FreeSurface(cursor);
			closeEverything();
			exit(0);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
			{
				position--;
				if (position == 0)
					position = 3;
				wandpos.x = 550;
				wandpos.y = 80 + (80 * position);
				SDL_BlitSurface(cursor, NULL, screen, &wandpos);
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				position++;
				if (position == 4)
					position = 1;
				wandpos.x = 550;
				wandpos.y = 80 + (80 * position);
				SDL_BlitSurface(cursor, NULL, screen, &wandpos);
			}
			if (event.key.keysym.sym == SDLK_RETURN ||
			        event.key.keysym.sym ==  SDLK_KP_ENTER)
			{
				if (position == 1)
				{
					int i;
					currentLevel = allLevels[0];
					do
					{
						SDL_Surface* screenTEMP = SDL_ConvertSurface(screen, screen->format, SDL_SWSURFACE);//Copie du contenu du screen
						for (i = 0; i < 180; i++)//Rotozoom avant chaque debut d'un niveau
						{
							SDL_Surface* effect = rotozoomSurface(screenTEMP, i, 1.0, SMOOTHING_ON);
							SDL_BlitSurface(effect, NULL, screen, NULL);
							SDL_FreeSurface(effect);
							SDL_Flip(screen);
						}
						startGame(screen);
					}
					while (shouldPassToNextLevel);
				}
				else if (position == 2)
				{
					paintOptionsScreen(screen);
				}
				else if (position == 3)
				{
					SDL_FreeSurface(screen);
					SDL_FreeSurface(background);
					SDL_FreeSurface(cursor);
					closeEverything();
					exit(0);
				}
			}

		}
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	SDL_FreeSurface(cursor);
	closeEverything();
}
