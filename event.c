#include "main.h"



void position_mouse(SDL_Event *e, enum BHtype *type, int* relx, int *rely) //detect where mouse button hit
{
    int x=e->button.x; int y=e->button.y;
    SDL_Rect *v=&(G.B.Vscreen_board_association);
    if(x>=v->x&&y>=v->y&&x<(v->x+v->w)&&y<(v->y+v->h))
        if(e->button.type==SDL_MOUSEBUTTONDOWN||e->button.type==SDL_MOUSEMOTION||e->button.type==SDL_MOUSEBUTTONDOWN)
            {*type=BHBOARD;*relx=x-v->x; *rely=y-v->y;}
}

#ifdef WINWIN_BUILD

#endif // WINWIN_BUILD
