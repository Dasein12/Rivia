#include "Header.h"
Enemy enemyList[100] = {0};
int enemyCount;
int enemyToBattle = 0;
void removeEnemy(int index)
{
    int i;
    for (i = index; i < enemyCount - 1; i++)
    {
        enemyList[i] = enemyList[i+1];
    }
    enemyCount--;
}
void loadEnemies()
{
    FILE* f = fopen(currentLevel.enemyFile, "r");
    enemyCount = currentLevel.enemyCount;
    int i;
    for (i = 0; i < enemyCount; i++)
    {
        char spellListID[50];
        char dir;
        char temp[500];
        fscanf(f, "%d|%[^|]|%d|%d|%d|%d|%d|%c|%s", &enemyList[i].id, enemyList[i].name, &enemyList[i].maxHP, &enemyList[i].maxAP, &enemyList[i].spawnPointX, &enemyList[i].spawnPointY, &enemyList[i].range, &dir, spellListID);
        switch (dir)
        {
        case 'u':
            enemyList[i].d = up;
            break;
        case 'd':
            enemyList[i].d = down;
            break;
        case 'r':
            enemyList[i].d = right;
            break;
        case 'l':
            enemyList[i].d = left;
            break;
        }
        int spellsID[4];
        sscanf(spellListID, "%d,%d,%d,%d", &spellsID[0], &spellsID[1], &spellsID[2], &spellsID[3]);
        enemyList[i].spellList[0] = allSpells[spellsID[0] - 1];
        enemyList[i].spellList[1] = allSpells[spellsID[1] - 1];
        enemyList[i].spellList[2] = allSpells[spellsID[2] - 1];
        enemyList[i].spellList[3] = allSpells[spellsID[3] - 1];
    }
    fclose(f);
}
void initEnemies()
{
    int i;
    for (i = 0; i < enemyCount; i++)
    {
        enemyList[i].currentHP = enemyList[i].maxHP;
        enemyList[i].currentAP = enemyList[i].maxAP;
        enemyList[i].leftcounter = enemyList[i].rightcounter = enemyList[i].upcounter = enemyList[i].downcounter = 1;
        enemyList[i].pos.x = enemyList[i].spawnPointX;
        enemyList[i].pos.y = enemyList[i].spawnPointY;
        char imageEnemyFile[250];
        int j;
        for (j = 0; j < 4; j++)
        {
            sprintf(imageEnemyFile, "image/enemy%dup%d.png", enemyList[i].id, j + 1);
            enemyList[i].upImage[j] = IMG_Load(imageEnemyFile);
            sprintf(imageEnemyFile, "image/enemy%dup%d.png", enemyList[i].id, j + 1);
            enemyList[i].rightImage[j] = IMG_Load(imageEnemyFile);
            sprintf(imageEnemyFile, "image/enemy%ddown%d.png", enemyList[i].id, j + 1);
            enemyList[i].leftImage[j] = IMG_Load(imageEnemyFile);
            sprintf(imageEnemyFile, "image/enemy%ddown%d.png", enemyList[i].id, j + 1);
            enemyList[i].downImage[j] = IMG_Load(imageEnemyFile);
        }
        sprintf(imageEnemyFile, "image/enemy%dbattleportrait.png", enemyList[i].id);
        enemyList[i].battleImage = IMG_Load(imageEnemyFile);
    }
}
void showEnemies(SDL_Surface* screen)
{
    int i;
    SDL_Surface* imageEnemy;
    for (i = 0; i < enemyCount; i++)
    {
        if (enemyList[i].d == left)
            imageEnemy = enemyList[i].leftImage[enemyList[i].leftcounter - 1];
        else if (enemyList[i].d == right)
            imageEnemy = enemyList[i].rightImage[enemyList[i].rightcounter - 1];
        else if (enemyList[i].d == up)
            imageEnemy = enemyList[i].upImage[enemyList[i].upcounter - 1];
        else if (enemyList[i].d == down)
            imageEnemy = enemyList[i].downImage[enemyList[i].downcounter - 1];
        SDL_BlitSurface(imageEnemy, NULL, screen, &enemyList[i].pos);
    }
}
void moveEnemy(int i, direction d)
{
    if (d == up)
    {
        enemyList[i].pos.y -= 5;
        enemyList[i].upcounter++;
        if (enemyList[i].upcounter == 5)
            enemyList[i].upcounter = 1;
    }
    else if (d == down)
    {
        enemyList[i].pos.y += 5;
        enemyList[i].downcounter++;
        if (enemyList[i].downcounter == 5)
            enemyList[i].downcounter = 1;
    }
    else if (d == left)
    {
        enemyList[i].pos.x -= 5;
        enemyList[i].leftcounter++;
        if (enemyList[i].leftcounter == 5)
            enemyList[i].leftcounter = 1;
    }
    else if (d == right)
    {
        enemyList[i].pos.x += 5;
        enemyList[i].rightcounter++;
        if (enemyList[i].rightcounter == 5)
            enemyList[i].rightcounter = 1;
    }
}
void moveEnemies()
{
    int i;
    for (i = 0; i < enemyCount; i++)
    {
        if (enemyList[i].d == down)
        {
            SDL_Rect collisionRect = enemyList[i].pos;
            SDL_Rect heroPos;
            heroPos.x = x;
            heroPos.y = y;
            heroPos.w = posHero.w;
            heroPos.h = posHero.h;
            collisionRect.y += 5;
            if (!collision(&heroPos, &collisionRect))
            {
                bool shouldReverse = false;
                if (enemyList[i].pos.y >= enemyList[i].spawnPointY + enemyList[i].range || collisionmap(down, enemyList[i].pos.x, enemyList[i].pos.y))
                    shouldReverse = true;
                else if (enemyList[i].pos.y <= enemyList[i].spawnPointY)
                    shouldReverse = false;
                if (!shouldReverse)
                {
                    moveEnemy(i, down);
                }
                else if (shouldReverse)
                {
                    enemyList[i].d = up;
                }
            }
            else
            {
                SDL_Event event;
                event.type = SDL_USEREVENT;
                event.user.code = startBattleEvent;
                enemyToBattle = i;
                SDL_PushEvent(&event);
            }
        }
        else if (enemyList[i].d == up)
        {
            SDL_Rect collisionRect = enemyList[i].pos;
            SDL_Rect heroPos;
            heroPos.x = x;
            heroPos.y = y;
            heroPos.w = posHero.w;
            heroPos.h = posHero.h;
            collisionRect.y -= 5;
            if (!collision(&heroPos, &collisionRect))
            {
                bool shouldReverse = false;
                if (enemyList[i].pos.y >= enemyList[i].spawnPointY + enemyList[i].range || collisionmap(down, enemyList[i].pos.x, enemyList[i].pos.y))
                    shouldReverse = false;
                else if (enemyList[i].pos.y <= enemyList[i].spawnPointY)
                    shouldReverse = true;
                if (!shouldReverse)
                {
                    moveEnemy(i, up);
                }
                else if (shouldReverse)
                {
                    enemyList[i].d = down;
                }
            }
            else
            {
                SDL_Event event;
                event.type = SDL_USEREVENT;
                event.user.code = startBattleEvent;
                enemyToBattle = i;
                SDL_PushEvent(&event);
            }
        }
        else if (enemyList[i].d == left)
        {
            SDL_Rect collisionRect = enemyList[i].pos;
            SDL_Rect heroPos;
            heroPos.x = x;
            heroPos.y = y;
            heroPos.w = posHero.w;
            heroPos.h = posHero.h;
            collisionRect.x -= 5;
            if (!collision(&heroPos, &collisionRect))
            {
                bool shouldReverse = false;
                if (enemyList[i].pos.x >= enemyList[i].spawnPointX + enemyList[i].range || collisionmap(down, enemyList[i].pos.x, enemyList[i].pos.y))
                    shouldReverse = false;
                else if (enemyList[i].pos.x <= enemyList[i].spawnPointX)
                    shouldReverse = true;
                if (!shouldReverse)
                {
                    moveEnemy(i, left);
                }
                else if (shouldReverse)
                {
                    enemyList[i].d = right;
                }
            }
            else
            {
                SDL_Event event;
                event.type = SDL_USEREVENT;
                event.user.code = startBattleEvent;
                enemyToBattle = i;
                SDL_PushEvent(&event);
            }
        }
        else if (enemyList[i].d == right)
        {
            SDL_Rect collisionRect = enemyList[i].pos;
            SDL_Rect heroPos;
            heroPos.x = x;
            heroPos.y = y;
            heroPos.w = posHero.w;
            heroPos.h = posHero.h;
            collisionRect.x += 5;
            if (!collision(&heroPos, &collisionRect))
            {
                bool shouldReverse = false;
                if (enemyList[i].pos.x >= enemyList[i].spawnPointX + enemyList[i].range || collisionmap(down, enemyList[i].pos.x, enemyList[i].pos.y))
                    shouldReverse = true;
                else if (enemyList[i].pos.x <= enemyList[i].spawnPointX)
                    shouldReverse =
                        false;
                if (!shouldReverse)
                {
                    moveEnemy(i, right);
                }
                else if (shouldReverse)
                {
                    enemyList[i].d = left;
                }
            }
            else
            {
                SDL_Event event;
                event.type = SDL_USEREVENT;
                event.user.code = startBattleEvent;
                enemyToBattle = i;
                SDL_PushEvent(&event);
            }
        }
    }
}
