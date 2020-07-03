#include "main.h"

int board_mouse_button_down(int x, int y);

int which_mouse_hit(SDL_Event *e)
{
    int x=e->button.x; int y=e->button.y;
    SDL_Rect *v=&(G.B.Vscreen_board_association);
    if(x>=v->x&&y>=v->y&&x<(v->x+v->w)&&y<(v->y+v->h))
        if(e->button.type==SDL_MOUSEBUTTONDOWN&&e->button.button==SDL_BUTTON_LEFT)
            board_mouse_button_down(x-v->x, y-v->y);
}

