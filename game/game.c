#include "Header.h"
SDL_Rect portion;
SDL_Surface* wholeMap;
int x;
int y;
SDL_TimerID timer;
const int updateEnemiesEvent = 1;
int startBattleEvent = 2;
Level currentLevel;
Level allLevels[2];
void loadLevels()
{
    Level l1,l2;
    l1.id = 1;
    l1.startPos.x = 20;
    l1.startPos.y = 20;
    l1.endPos.x = 1800;
    l1.endPos.y = 725;
    l1.endPos.w = 200;
    l1.endPos.h = 175;
    l1.enemyCount = 3;
    strcpy(l1.enemyFile,"text/enemy1.txt");
    strcpy(l1.mapFile,"image/map1.jpg");
    strcpy(l1.mapCollision,"image/map1collision.jpg");
    allLevels[0] = l1;
    l2.id = 2;
    l2.startPos.x = 80;
    l2.startPos.y = 80;
    l2.endPos.x = 9999;//This is the last level
    l2.endPos.y = 9999;
    l2.endPos.w = 200;
    l2.endPos.h = 175;
    l2.enemyCount = 3;
    strcpy(l2.enemyFile,"text/enemy2.txt");
    strcpy(l2.mapFile,"image/map2.jpg");
    strcpy(l2.mapCollision,"image/map2collision.jpg");
    allLevels[1] = l2;
}
Uint32 updateEnemies(Uint32 interval, void* param)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = updateEnemiesEvent;
    SDL_PushEvent(&event);
    return interval;
}
void startGame(SDL_Surface* screen)
{
    x = currentLevel.startPos.x;
    y = currentLevel.startPos.y;
    loadSpells();
    loadHeros();
    initHero(1);
    loadEnemies();
    initEnemies();
    timer = SDL_AddTimer(40, updateEnemies, 0);
    SDL_EnableKeyRepeat(20, 20);
    wholeMap = IMG_Load(currentLevel.mapFile);
    SDL_Surface* untouched = IMG_Load(currentLevel.mapFile);
    portion.w = 800;
    portion.h = 600;
    portion.x = 0;
    portion.y = 0;
    SDL_Rect enemyPortion;
    SDL_Event event;
    while (1)
    {
        SDL_BlitSurface(untouched, NULL, wholeMap, NULL);
        showEnemies(wholeMap);
        SDL_BlitSurface(wholeMap, &portion, screen, NULL);
        showHero(screen);
        SDL_Flip(screen);
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT)
        {
            exit(1);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                SDL_RemoveTimer(timer);
                paintMenu(screen);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                moveHero(right);
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                moveHero(down);
            }
            else if (event.key.keysym.sym == SDLK_LEFT)
            {
                moveHero(left);
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                moveHero(up);
            }
            SDL_Rect heroPos;
            heroPos.x = x;
            heroPos.y = y;
            heroPos.w = posHero.w;
            heroPos.h = posHero.h;
            if(collision(&currentLevel.endPos,&heroPos)&&enemyCount == 0){//We can go to the next level
                currentLevel = allLevels[currentLevel.id];
                initCollisionMap();
                shouldPassToNextLevel = true;
                SDL_FreeSurface(untouched);
                SDL_FreeSurface(wholeMap);
                SDL_RemoveTimer(timer);
                break;
            }
            /*else if(event.key.keysym.sym == SDLK_SPACE)
            {
                printf("%d:%d\n", x,y);
            }*/
        }
        else if (event.type == SDL_USEREVENT)
        {
            if ( event.user.code == updateEnemiesEvent)
                moveEnemies();
            /*else if(event.user.code == readfromGamePadEvent){
                    moveHero(*((direction*)event.user.data1));
            }*/
            else if (event.user.code == startBattleEvent)
            {
                SDL_RemoveTimer(timer);
                SDL_EnableKeyRepeat(0, 0);
                startBattle(screen);
                timer = SDL_AddTimer(40, updateEnemies, 0);
                SDL_EnableKeyRepeat(20, 20);
            }
        }
    }
}
void scroll(direction d)
{
    if (d == up)
    {
        portion.y -= 5;
        y -= 5;
    }
    else if (d == down)
    {
        portion.y += 5;
        y += 5;
    }
    else if (d == right)
    {
        portion.x += 5;
        x += 5;
    }
    else if (d == left)
    {
        portion.x -= 5;
        x -= 5;
    }

}
int getMapPosX()
{

    return portion.x;
}
int getMapPosY()
{
    return portion.y;
}
int getMapW()
{
    return wholeMap->w;
}
int getMapH()
{
    return wholeMap->h;
}
