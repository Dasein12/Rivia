#include "Header.h"
bool showBattleMenu;
bool showHeroAction;
bool showEnemyAction;
bool showEnd;
bool hasWon;
bool hasLost;
int pos ;
TTF_Font* font;
SDL_Color Black;
SDL_Color White;
char statusline1[500] = "";
char statusline2[500] = "";
SDL_Surface* createHeroHPBar()
{
	SDL_Surface *s = SDL_CreateRGBSurface(0, 120, 50, 32, 0, 0, 0, 0);//create a 120x60 pixel SDL_Surface (the whole HP indicator)
	SDL_Surface *bar = SDL_CreateRGBSurface(0, 105, 20, 32, 0, 0, 0, 0);//create a 105x20 pixel SDL_Surface (just the HP bar)
	SDL_Surface *textSurface = NULL;
	char text[50];
	int hpPercentage = currentHero.currentHP * 100 / currentHero.maxHP;
	SDL_Rect barPos, textPos, barFill;
	barFill.x = 0;
	barFill.y = 0;
	barFill.h = bar->h;
	barFill.w = hpPercentage * s->w / 100;
	barPos.x = 5;
	barPos.y = 23;
	textPos.x = 10;
	textPos.y = 0;
	SDL_FillRect(bar, NULL, SDL_MapRGB(bar->format, 255, 255, 255));//We fill the hpbar background first with white
	SDL_FillRect(bar, &barFill, SDL_MapRGB(bar->format, 58, 95, 11));//we fill the hp bar with the green color
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 255, 255));//we fill the whole SDL Surface with white background
	sprintf(text, "HP : %d/%d", currentHero.currentHP, currentHero.maxHP);
	textSurface = TTF_RenderText_Blended(font, text, Black);
	SDL_BlitSurface(bar, NULL, s, &barPos);
	SDL_BlitSurface(textSurface, NULL, s, &textPos);
	return s;
}
SDL_Surface* createHeroAPBar()
{
	SDL_Surface *s = SDL_CreateRGBSurface(0, 120, 50, 32, 0, 0, 0, 0);//create a 120x60 pixel SDL_Surface (the whole HP indicator)
	SDL_Surface *bar = SDL_CreateRGBSurface(0, 105, 20, 32, 0, 0, 0, 0);//create a 105x20 pixel SDL_Surface (just the HP bar)
	SDL_Surface *textSurface = NULL;
	char text[50];
	int hpPercentage = currentHero.currentAP * 100 / currentHero.maxAP;
	SDL_Rect barPos, textPos, barFill;
	barFill.x = 0;
	barFill.y = 0;
	barFill.h = bar->h;
	barFill.w = hpPercentage * s->w / 100;
	barPos.x = 5;
	barPos.y = 23;
	textPos.x = 10;
	textPos.y = 0;
	SDL_FillRect(bar, NULL, SDL_MapRGB(bar->format, 255, 255, 255));//We fill the hpbar background first with white
	SDL_FillRect(bar, &barFill, SDL_MapRGB(bar->format, 0, 0, 205));//we fill the ap bar with the blue color
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 255, 255));//we fill the whole SDL Surface with white background
	sprintf(text, "AP : %d/%d", currentHero.currentAP, currentHero.maxAP);
	textSurface = TTF_RenderText_Blended(font, text, Black);
	SDL_BlitSurface(bar, NULL, s, &barPos);
	SDL_BlitSurface(textSurface, NULL, s, &textPos);
	return s;
}
SDL_Surface* createEnemyHPBar()
{
	SDL_Surface *s = SDL_CreateRGBSurface(0, 120, 50, 32, 0, 0, 0, 0);//create a 120x60 pixel SDL_Surface (the whole HP indicator)
	SDL_Surface *bar = SDL_CreateRGBSurface(0, 105, 20, 32, 0, 0, 0, 0);//create a 105x20 pixel SDL_Surface (just the HP bar)
	SDL_Surface *textSurface = NULL;
	char text[50];
	int hpPercentage = enemyList[enemyToBattle].currentHP * 100 / enemyList[enemyToBattle].maxHP;
	SDL_Rect barPos, textPos, barFill;
	barFill.x = 0;
	barFill.y = 0;
	barFill.h = bar->h;
	barFill.w = hpPercentage * s->w / 100;
	barPos.x = 5;
	barPos.y = 23;
	textPos.x = 10;
	textPos.y = 0;
	SDL_FillRect(bar, NULL, SDL_MapRGB(bar->format, 255, 255, 255));//We fill the hpbar background first with white
	SDL_FillRect(bar, &barFill, SDL_MapRGB(bar->format, 58, 95, 11)); //we fill the ap bar with the blue color
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 255, 255));//we fill the whole SDL Surface with white background
	sprintf(text, "HP : %d/%d", enemyList[enemyToBattle].currentHP, enemyList[enemyToBattle].maxHP);
	textSurface = TTF_RenderText_Blended(font, text, Black);
	SDL_BlitSurface(bar, NULL, s, &barPos);
	SDL_BlitSurface(textSurface, NULL, s, &textPos);
	return s;
}
SDL_Surface* createTextArea()
{
	SDL_Surface* s = IMG_Load("image/textarea.png");
	SDL_Surface	*wandImage = IMG_Load("image/MenuCursor.png");
	SDL_Surface* spell1Image = NULL;
	SDL_Surface* spell2Image = NULL;
	SDL_Surface* spell3Image = NULL;
	SDL_Surface* spell4Image = NULL;
	SDL_Surface* status1Image = NULL;
	SDL_Surface* status2Image = NULL;
	SDL_Rect wandPos, spell1Pos, spell2Pos, spell3Pos, spell4Pos, status1Pos, status2Pos;
	wandPos.x = -180 + (pos * 200);
	wandPos.y = 80;
	spell1Pos.x = 60;
	spell1Pos.y = 90;
	spell2Pos.x = 260;
	spell2Pos.y = 90;
	spell3Pos.x = 460;
	spell3Pos.y = 90;
	spell4Pos.x = 660;
	spell4Pos.y = 90;
	status1Pos.x = 20;
	status1Pos.y = 60;
	status2Pos.x = 20;
	status2Pos.y = 120;
	spell1Image = TTF_RenderText_Blended(font, currentHero.spellList[0].name, White);
	spell2Image = TTF_RenderText_Blended(font, currentHero.spellList[1].name, White);
	spell3Image = TTF_RenderText_Blended(font, currentHero.spellList[2].name, White);
	spell4Image = TTF_RenderText_Blended(font, currentHero.spellList[3].name, White);
	status1Image = TTF_RenderText_Blended(font, statusline1, White);
	status2Image = TTF_RenderText_Blended(font, statusline2, White);
	if (showBattleMenu)
	{
		SDL_BlitSurface(wandImage, NULL, s, &wandPos);
		SDL_BlitSurface(spell1Image, NULL, s, &spell1Pos);
		SDL_BlitSurface(spell2Image, NULL, s, &spell2Pos);
		SDL_BlitSurface(spell3Image, NULL, s, &spell3Pos);
		SDL_BlitSurface(spell4Image, NULL, s, &spell4Pos);
	}
	if (showHeroAction || showEnemyAction || showEnd)
	{
		SDL_BlitSurface(status1Image, NULL, s, &status1Pos);
		SDL_BlitSurface(status2Image, NULL, s, &status2Pos);
	}
	return s;
}
void useHeroSpell(Spell s)
{
	bool isaCrit = false;
	int crit;
	srand(time(NULL));
	crit = rand();
	crit = crit % 100;
	if (crit < s.critchance)
		isaCrit = true;
	char buffer[500];
	if (s.AP != 0)
	{
		if (s.AP > currentHero.currentAP )
		{
			sprintf(statusline1, "You don't have enough AP for that spell");
			return;
		}
		else
		{
			currentHero.currentAP -= s.AP;
			sprintf(statusline1, "You used %s for %d AP. ", s.name, s.AP);
		}
	}
	else sprintf(statusline1, "You used %s. ", s.name);
	if (s.heal != 0)
	{
		if (isaCrit)
		{
			currentHero.currentHP += (s.heal * 2);
			sprintf(buffer, "You healed for %d. ", (s.heal * 2));
		}
		else
		{
			currentHero.currentHP += s.heal;
			sprintf(buffer, "You healed for %d. ", s.heal);
		}
		if(currentHero.currentHP > currentHero.maxHP)
			currentHero.currentHP = currentHero.maxHP;
		strcat(statusline1, buffer);
	}
	if (s.damage != 0)
	{
		if (isaCrit)
		{
			enemyList[enemyToBattle].currentHP -= (s.damage * 2);
			sprintf(buffer, "You damaged the enemy for %d HP. ", (s.damage * 2));
		}
		else
		{
			sprintf(buffer, "You damaged the enemy for %d HP.", s.damage);
			enemyList[enemyToBattle].currentHP -= s.damage;
		}
		if(enemyList[enemyToBattle].currentHP < 0)
			enemyList[enemyToBattle].currentHP = 0;
		strcat(statusline1, buffer);
	}
	if (isaCrit)
		sprintf(statusline2, "That was a nice crit.");
	else
		strcpy(statusline2, "");
}
void useEnemySpell(Spell s)
{
	bool isaCrit = false;
	int crit;
	srand(time(NULL));
	crit = rand();
	crit = crit % 100;
	if (crit < s.critchance)
		isaCrit = true;
	char buffer[500];
	sprintf(statusline1, "%s used %s. ", enemyList[enemyToBattle].name, s.name);

	if (isaCrit)
	{
		currentHero.currentHP -= (s.damage * 2);
		sprintf(buffer, "It damaged you for %d HP. ", (s.damage * 2));
	}
	else
	{
		sprintf(buffer, "It damaged you for %d HP.", s.damage);
		currentHero.currentHP -= s.damage;
	}
	strcat(statusline1, buffer);
	if (isaCrit)
		sprintf(statusline2, "That was an unlucky crit.");
	else
		strcpy(statusline2, "");
}
void checkForEnd()
{
	if (currentHero.currentHP <= 0)
	{
		showEnd = true;
		hasLost = true;
		sprintf(statusline1, "%s has trumped you. You will return to the start square.", enemyList[enemyToBattle].name);
	}
	if (enemyList[enemyToBattle].currentHP <= 0)
	{
		showEnd = true;
		hasWon = true;
		sprintf(statusline1, "You have sent %s back to his realm. You will continue the journey.", enemyList[enemyToBattle].name);
	}
}
void startBattle(SDL_Surface * screen)
{
	showBattleMenu = true;
	showHeroAction = false;
	showEnemyAction = false;
	showEnd = false;
	hasWon = false;
	hasLost = false;
	pos = 1;
	font = TTF_OpenFont("police/DejaVuSans.ttf", 18);
	Black.b = 0;
	Black.r = 0;
	Black.g = 0;
	White.b = 255;
	White.r = 255;
	White.g = 255;
	SDL_Surface *textArea = NULL;
	SDL_Surface *background = NULL;
	SDL_Surface *hero = NULL;
	SDL_Surface *enemy = NULL;
	SDL_Surface *heroHP = NULL;
	SDL_Surface *heroAP = NULL;
	SDL_Surface *enemyHP = NULL;
	background = IMG_Load("image/Battlebackground1.png");
	hero = currentHero.battleImage;
	enemy = enemyList[enemyToBattle].battleImage;
	SDL_Rect textAreaPos, backgroundPos, heroHPPos, heroAPPos, enemyHPPos, heroPos, enemyPos;
	textAreaPos.x = 0;
	textAreaPos.y = 400;
	textAreaPos.w = 800;
	textAreaPos.h = 200;
	backgroundPos.x = 0;
	backgroundPos.y = 0;
	backgroundPos.w = 800;
	backgroundPos.h = 560;
	heroHPPos.x = 40;
	heroHPPos.y = 40;
	heroAPPos.x = 40;
	heroAPPos.y = 90;
	enemyHPPos.x = 680;
	enemyHPPos.y = 40;
	heroPos.x = 80;
	heroPos.y = 295;
	enemyPos.x = 640;
	enemyPos.y = 310;
	SDL_Event event;
	while (1)
	{
		heroHP = createHeroHPBar();
		heroAP = createHeroAPBar();
		enemyHP = createEnemyHPBar();
		textArea = createTextArea();
		SDL_BlitSurface(background, NULL, screen, &backgroundPos);
		SDL_BlitSurface(hero, NULL, screen, &heroPos);
		SDL_BlitSurface(enemy, NULL, screen, &enemyPos);
		SDL_BlitSurface(heroHP, NULL, screen, &heroHPPos);
		SDL_BlitSurface(heroAP, NULL, screen, &heroAPPos);
		SDL_BlitSurface(enemyHP, NULL, screen, &enemyHPPos);
		SDL_BlitSurface(textArea, NULL, screen, &textAreaPos);
		SDL_Flip(screen);
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			exit(1);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RETURN ||
			        event.key.keysym.sym ==  SDLK_KP_ENTER)
			{
				if (showEnd)
				{
					currentHero.currentAP = currentHero.maxAP;
					if (hasWon)
					{
						removeEnemy(enemyToBattle);
						break;
					}
					else
						paintMenu(screen);
				}
				if (showBattleMenu)
				{
					showBattleMenu = false;
					showHeroAction = true;
					showEnemyAction = false;
					useHeroSpell(currentHero.spellList[pos - 1]);
					checkForEnd();
				}
				else if (showHeroAction)
				{
					showBattleMenu = false;
					showHeroAction = false;
					showEnemyAction = true;
					useEnemySpell(enemyList[enemyToBattle].spellList[0]);
					checkForEnd();
				}
				else if (showEnemyAction)
				{
					showBattleMenu = true;
					showHeroAction = false;
					showEnemyAction = false;
				}

			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				if (showBattleMenu)
				{
					pos++;
					if (pos == 5)
						pos = 1;
				}
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				if (showBattleMenu)
				{
					pos--;
					if (pos == 0)
						pos = 4;
				}
			}
		}
	}
	TTF_CloseFont( font );
}
