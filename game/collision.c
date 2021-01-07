#include "Header.h"
SDL_Surface* collisionMap;
void initCollisionMap()
{
    collisionMap = IMG_Load(currentLevel.mapCollision);
}
SDL_Color GetPixel (SDL_Surface* pSurface , int x , int y)
{
    SDL_Color color;
    Uint32 col = 0 ;
    if (x >= 0 && y >= 0)
    {
        //determine position
        char* pPosition = ( char* ) pSurface->pixels ;

        //offset by y
        pPosition += ( pSurface->pitch * y ) ;

        //offset by x
        pPosition += ( pSurface->format->BytesPerPixel * x ) ;

        //copy pixel data
        memcpy ( &col , pPosition , pSurface->format->BytesPerPixel ) ;

        //convert color
    }
    SDL_GetRGB ( col , pSurface->format , &color.r , &color.g , &color.b ) ;
    return ( color ) ;
}
bool collision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    if (rect1->y >= rect2->y + rect2->h)
        return false;
    if (rect1->x >= rect2->x + rect2->w)
        return false;
    if (rect1->y + rect1->h <= rect2->y)
        return false;
    if (rect1->x + rect1->w <= rect2->x)
        return false;
    return true;
}
bool collisionmap (direction d, int collX, int collY)
{
    SDL_Color couleur;
    if (collisionMap == NULL)
        initCollisionMap();
    if (d == up)
    {
        couleur = GetPixel(collisionMap, collX + 35, collY - 49);
    }
    else if (d == down)
    {
        couleur = GetPixel(collisionMap, collX + 35, collY + 59);
    }
    else if (d == right)
    {
        couleur = GetPixel(collisionMap, collX + 40, collY + 54);
    }
    else if (d == left)
    {
        couleur = GetPixel(collisionMap, collX - 30, collY + 54);
    }
    return ((couleur.r == 255 && couleur.g == 255 && couleur.b == 255) );

}