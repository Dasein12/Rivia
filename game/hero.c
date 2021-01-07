#include "Header.h"
Hero heroList[2] = {0};
Spell allSpells[8] = {0};
Hero currentHero;
SDL_Surface* imageHero;
SDL_Rect posHero;
direction d;
int leftcounter,rightcounter,upcounter,downcounter;
void loadHeros()
{ 
    FILE* f = fopen("text/hero.txt","r");
    int i;
    for(i=0; i<2; i++)
    {
        char spellListID[50];
        fscanf(f,"%d|%[^|]|%d|%d|%s",&heroList[i].id,heroList[i].name,&heroList[i].maxHP,&heroList[i].maxAP,spellListID);
        int spellsID[4];
        sscanf(spellListID,"%d,%d,%d,%d",&spellsID[0],&spellsID[1],&spellsID[2],&spellsID[3]);
        heroList[i].spellList[0] = allSpells[spellsID[0]-1];
        heroList[i].spellList[1] = allSpells[spellsID[1]-1];
        heroList[i].spellList[2] = allSpells[spellsID[2]-1];
        heroList[i].spellList[3] = allSpells[spellsID[3]-1];
    }
    fclose(f);
}
Spell* loadSpells()
{
    FILE* f = fopen("text/spells.txt","r");
    int i;
    for(i=0; i<8; i++)
    {
        fscanf(f,"%d|%[^|]|%d|%d|%d|%d\n",&allSpells[i].id,allSpells[i].name,&allSpells[i].AP,&allSpells[i].damage,&allSpells[i].heal,&allSpells[i].critchance);
    }
    return allSpells;
}
void initHero(int ID)
{
    currentHero = heroList[ID - 1];
    currentHero.currentHP = currentHero.maxHP;
    currentHero.currentAP = currentHero.maxAP;
    leftcounter = rightcounter = upcounter = downcounter = 1;
    posHero.x = x;
    posHero.y = y;
    char imageHeroFile[250];
    int i;
    for(i=0;i<4;i++){
    	sprintf(imageHeroFile,"image/up%d.png",i+1);
        currentHero.upImage[i] = IMG_Load(imageHeroFile);
        sprintf(imageHeroFile,"image/right%d.png",i+1);
        currentHero.rightImage[i] = IMG_Load(imageHeroFile);
        sprintf(imageHeroFile,"image/left%d.png",i+1);
        currentHero.leftImage[i] = IMG_Load(imageHeroFile);
        sprintf(imageHeroFile,"image/down%d.png",i+1);
        currentHero.downImage[i] = IMG_Load(imageHeroFile);
    }
    sprintf(imageHeroFile,"image/battleportrait.png");
    currentHero.battleImage = IMG_Load(imageHeroFile);
    d = down;
}
void showHero(SDL_Surface* screen)
{
    char imageHeroFile[250];
    if(d == left)
    { 
        imageHero = currentHero.leftImage[leftcounter-1];
    }
    else if(d == right)
    {
    	imageHero = currentHero.rightImage[rightcounter-1];
    }
    else if(d == up)
    {
       imageHero = currentHero.upImage[upcounter-1];
    }
    else if(d == down)
    {
    	imageHero = currentHero.downImage[downcounter-1];
    }
    SDL_BlitSurface(imageHero,NULL,screen,&posHero);
}

void moveHero(direction dir)
{
    d = dir;
    if(d == left)
    {
        if(!collisionmap (left,x,y))
        {
            if(getMapPosX()<=0||posHero.x>400)
            {
                posHero.x-=5;
                x-=5;
            }
            else scroll(left);
        }
        leftcounter++;
        if(leftcounter == 5)
            leftcounter = 1;
    }
    else if(d == right)
    {
        if(!collisionmap (right,x,y))
        {
            if(posHero.x<400)
            {
                if(posHero.x+imageHero->w+getMapPosX()<getMapW())
                {
                    posHero.x+=5;
                    x+=5;
                }
            }
            else if(getMapPosX()+800>getMapW())
            {
                if(posHero.x+imageHero->w+getMapPosX()<getMapW())
                {
                    posHero.x+=5;
                    x+=5;
                }
            }

            else scroll(right);
        }
        rightcounter++;
        if(rightcounter == 5)
            rightcounter = 1;
    }
    else if(d == up)
    {
        if(!collisionmap (up,x,y))
        {
            if(getMapPosY()<=0||posHero.y>300)
            {
                posHero.y-=5;
                y-=5;
            }
            else scroll(up);
        }
        upcounter++;
        if(upcounter == 5)
            upcounter = 1;
    }
    else if(d == down)
    {
        if(!collisionmap (down,x,y))
        {
            if(posHero.y<300)
            {
                if(posHero.y+imageHero->h+getMapPosY()<getMapH())
                {
                    posHero.y+=5;
                    y+=5;
                }
            }
            else if(getMapPosY()+600>getMapH())
            {
                if(posHero.y+imageHero->h+getMapPosY()<getMapH())
                {
                    posHero.y+=5;
                    y+=5;
                }
            }
            else scroll(down);
        }
        downcounter++;
        if(downcounter == 5)
            downcounter = 1;
    }

}
