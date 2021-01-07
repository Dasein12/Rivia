#include "Header.h"
void paintOptionsScreen(SDL_Surface* screen)
{
	SDL_Event event;
	SDL_Surface	*background = IMG_Load("image/OptionsBackground.png");
	SDL_Surface	*cursor = IMG_Load("image/MenuCursor.png");
	SDL_Surface* volumeImage = NULL;
	SDL_Surface* soundImage = NULL;
	SDL_Surface* quitImage = NULL;
	SDL_Color Color;
	Color.b = 255;
	Color.r = 255;
	Color.g = 255;
	int volume = 100;
	bool isSoundOn = true;
	char volumeText[50] = "Volume 100";
	SDL_Rect volumePOS, soundPOS, quitPOS, wandpos;
	volumePOS.x = 550;
	volumePOS.y = 160;
	soundPOS.x = 550;
	soundPOS.y = 240;
	quitPOS.x = 550;
	quitPOS.y = 320;
	wandpos.x = 500;
	wandpos.y = 160;
	TTF_Font* font = TTF_OpenFont("police/DejaVuSans.ttf", 32);
	volumeImage = TTF_RenderText_Blended(font, volumeText, Color);
	soundImage = TTF_RenderText_Blended(font, "Sound ON", Color);
	quitImage = TTF_RenderText_Blended(font, "Return", Color);

	int position = 1;
	while (1)//TODO: Move this to events.c
	{
		SDL_BlitSurface(background, NULL, screen, NULL);
		SDL_BlitSurface(volumeImage, NULL, screen, &volumePOS);
		SDL_BlitSurface(soundImage, NULL, screen, &soundPOS);
		SDL_BlitSurface(quitImage, NULL, screen, &quitPOS);
		SDL_BlitSurface(cursor, NULL, screen, &wandpos);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);

		if (event.type == SDL_QUIT)
		{
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
				wandpos.x = 500;
				wandpos.y = 80 + (80 * position);
				SDL_BlitSurface(cursor, NULL, screen, &wandpos);
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				position++;
				if (position == 4)
					position = 1;
				wandpos.x = 500;
				wandpos.y = 80 + (80 * position);
				SDL_BlitSurface(cursor, NULL, screen, &wandpos);
			}
			if (event.key.keysym.sym == SDLK_RETURN ||
			        event.key.keysym.sym ==  SDLK_KP_ENTER)
			{
				if (position == 1)
				{
					if (volume < 100)
						volume += 10;
					else volume = 0;
					sprintf(volumeText, "Volume %d", volume);
					volumeImage = TTF_RenderText_Blended(font, volumeText, Color);
				}
				else if (position == 2)
				{
					isSoundOn = !isSoundOn;
					if (isSoundOn)
						soundImage = TTF_RenderText_Blended(font, "Sound ON", Color);
					else
						soundImage = TTF_RenderText_Blended(font, "Sound OFF", Color);

				}
				else if (position == 3)
				{
					TTF_CloseFont( font );
					break;
				}
			}

		}
	}
}
