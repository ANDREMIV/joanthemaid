#include "main.h"

struct Game G;
struct VideoHandle V;

char Board_Begin_Position[64]="tMvWlVmT\
OoOoOoOo\
 + + + +\
+ + + + \
 + + + +\
+ + + + \
pPpPpPpP\
RnBqKbNr";

void initgame()
{
    G.halfplies=0;
    G.Wcastling_rights_left=1;
    G.Wcastling_rights_right=1;
    G.Bcastling_rights_left=1;
    G.Bcastling_rights_right=1;
    int i,j;
    for(i=0;i<ROWNB;i++)
    for(j=0;j<LINENB;j++)
    G.B.b[i][j]=translate_char_to_case_type(Board_Begin_Position[j*ROWNB+i]);
    G.B.Csize=strtol(Args[2],NULL,10)/LINENB;
    G.B.Vscreen_board_association.h=strtol(Args[2],NULL,10);
    G.B.Vscreen_board_association.w=strtol(Args[1],NULL,10);
    G.B.Vscreen_board_association.x=0;
    G.B.Vscreen_board_association.y=0;
    {
        int i,j;
        for(i=0;i<MAX_MOVES_NB;i++)for(j=0;j<6;j++)
            G.moves[i][j]=0;
    }

}

void initvideo()
{
IMG_Init(IMG_INIT_PNG);
if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
}

V.xVscreen=strtol(Args[1],NULL,10);
V.yVscreen=strtol(Args[2],NULL,10);

if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
if (SDL_CreateWindowAndRenderer(V.xVscreen, V.yVscreen, 0, &V.window, &V.renderer))
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());

}
