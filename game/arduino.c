#include "Header.h"

/*FILE* f;
int linelength = 6;
int lineid = -1;
int oldlineid;
char buff[7];*/
//SDL_TimerID timer2;
//const int readfromGamePadEvent = 2;
//f = fopen("/dev/ttyACM0", "r");
//timer = SDL_AddTimer(1, readGamepad, 0);
/*Uint32 readGamepad(Uint32 interval, void* param) {
    oldlineid = lineid;
    fscanf(f, "%s %d", buff, &lineid);
    if (strlen(buff) > 1 && lineid > oldlineid) {
        if (strStartsWith("up", buff))
        {
            direction dir = up;
            SDL_Event event;
            event.type = SDL_USEREVENT;
            event.user.code = readfromGamePadEvent;
            event.user.data1 = &dir;
            SDL_PushEvent(&event);
        }
        else if (strStartsWith("left", buff))
        {
            direction dir = left;
            SDL_Event event;
            event.type = SDL_USEREVENT;
            event.user.code = readfromGamePadEvent;
            event.user.data1 = &dir;
            SDL_PushEvent(&event);
        }
    }
    return interval;
}*/