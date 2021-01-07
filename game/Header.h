#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
//#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
typedef enum{
	up,down,right,left
}direction;
typedef struct
{
	int id;
	char name[50];
	int damage;
	int heal;
	int AP;
	int critchance;
}Spell;
typedef struct
{
	int id;
	char name[50];
	int maxHP;
	int maxAP;
	int currentHP;
	int currentAP;
	SDL_Surface* upImage[4];
	SDL_Surface* downImage[4];
	SDL_Surface* rightImage[4];
	SDL_Surface* leftImage[4];
	SDL_Surface* battleImage;
	Spell spellList[4];
}Hero;
typedef struct
{
	int id;
	char name[50];
	int maxHP;
	int maxAP;
	int currentHP;
	int currentAP;
	int spawnPointX;
	int spawnPointY;
	int range;
	int leftcounter;
	int rightcounter;
	int upcounter;
	int downcounter;
	direction d;
	SDL_Rect pos;
	SDL_Surface* upImage[4];
	SDL_Surface* downImage[4];
	SDL_Surface* rightImage[4];
	SDL_Surface* leftImage[4];
	SDL_Surface* battleImage;
	Spell spellList[4];
}Enemy;
typedef struct{
	int id;
	int enemyCount;
	char enemyFile[50];
	SDL_Rect startPos;
	SDL_Rect endPos;
	char mapFile[50];
	char mapCollision[50];
}Level;
void initEverything();
Uint32 updateScreen(Uint32 interval, void *param);
void closeEverything();
void handleEvents(SDL_Event event);
void paintMenu(SDL_Surface* screen);
void startGame(SDL_Surface* screen);
void paintOptionsScreen(SDL_Surface* screen);
void loadHeros();
void loadLevels();
Spell* loadSpells();
void initHero(int ID);
void showCharacterSelectMenu(SDL_Surface* screen);
void showHero(SDL_Surface* screen);
void moveHero(direction dir);
void scroll(direction d);
int getMapPosX();
int getMapPosY();
int getMapW();
int getMapH();
bool collisionmap (direction d, int collX, int collY);
bool collision(SDL_Rect* rect1,SDL_Rect* rect2);
void initCollisionMap();
void loadEnemies();
void initEnemies();
void showEnemies(SDL_Surface* screen);
void removeEnemy(int index);
void moveEnemies();
void pathToHero(int enemyIndex);
void startBattle(SDL_Surface* screen);
extern int x;
extern int y;
extern Spell allSpells[8];
extern SDL_Rect posHero;
extern Enemy enemyList[100];
extern Level allLevels[2];
extern Level currentLevel;
extern int enemyCount;
extern int startBattleEvent;
extern Hero currentHero;
extern int enemyToBattle;
extern bool shouldPassToNextLevel;
