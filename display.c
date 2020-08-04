#include "main.h"

///SDL ORIENTATION
/*
X : 0 -- - - -- >
Y: 0
   |
   |
   v
*/


void printgrid()
{
    //Clear screen
    SDL_SetRenderDrawColor( V.renderer, 0x88, 0x88, 0x88, 0xFF );
    SDL_RenderClear( V.renderer);
    //SDL_SetRenderDrawColor( V.renderer, 0x88, 0x88, 0x00, 0x00 );

    int i,j;
    struct SDL_Rect Rsrc,Rdst;
    Rdst.h=G.B.Csize;
    Rdst.w=G.B.Csize;
    Rsrc=Rdst; Rsrc.x=0;Rsrc.y=0;

    for(i=0;i<ROWNB;i++)
    for(j=0;j<LINENB;j++){Rdst.x=G.B.Vscreen_board_association.x+i*G.B.Csize;
        Rdst.y=G.B.Vscreen_board_association.y+j*G.B.Csize;
    SDL_RenderCopy(V.renderer, CaseType_texture_association[G.B.b[i][j]], &Rsrc, &Rdst);}
    SDL_RenderPresent(V.renderer);
}

void printcase(int i, int j,enum CaseType CT)
{
    if(CT==-1)
        CT=G.B.b[i][j];
    SDL_SetRenderDrawColor( V.renderer, 0x88, 0x88, 0x88, 0xFF );

    struct SDL_Rect Rsrc,Rdst;
    Rdst.h=G.B.Csize;
    Rdst.w=G.B.Csize;
    Rsrc=Rdst; Rsrc.x=0;Rsrc.y=0;
    Rdst.x=G.B.Vscreen_board_association.x+i*G.B.Csize;
    Rdst.y=G.B.Vscreen_board_association.y+j*G.B.Csize;
    SDL_RenderFillRect(V.renderer,&Rdst);
    SDL_RenderCopy(V.renderer, CaseType_texture_association[CT], &Rsrc, &Rdst);
    SDL_RenderPresent(V.renderer);
}
