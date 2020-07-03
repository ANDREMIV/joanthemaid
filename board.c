#include "main.h"

enum CaseType graphical_piece_selected;
static int iselection; static int jselection;
int is_piece_selected=0;
///SDL ORIENTATION
/*
X : 0 -- - - -- >
Y: 0
   |
   |
   v
*/

void update_Graphical_board(enum CaseType X,int i, int j)//row-1,line-1
{
    G.B.b[i][j]=X;
}

int board_mouse_button_down(int x, int y){
    int i=x/G.B.Csize; int j=y/G.B.Csize;

    if(is_checkmate(G.halfplies%2))exit(55);
    if(is_pat(G.halfplies%2))exit(56);

if(is_piece_selected&&(i!=iselection||j!=jselection)){//move the piece to the square
is_piece_selected=0;
char move[6]={0};
move[0]=iselection+'a';
move[1]=jselection+'1';
move[2]=i+'a';
move[3]=j+'1';
int type=0;
if(is_move_valid(move,G.halfplies%2,&type))
{

graphical_piece_selected=change_piece_bg_color(graphical_piece_selected, square_color(i,j));
update_Graphical_board(graphical_piece_selected,i,j);

enum CaseType v=square_color(iselection,jselection); if(v==WHITE)v=wblank;else v=bblank;
update_Graphical_board(v,iselection,jselection);

if(type == ENPASSANT){

    enum CaseType v=square_color(i,jselection); if(v==WHITE)v=wblank;else v=bblank;
update_Graphical_board(v,i,jselection);
printcase(i,jselection);
}

printcase(iselection,jselection);
printcase(i,j);

if(type == WSROCK)
{G.Wcastling_rights_left=0;G.Wcastling_rights_right=0;
update_Graphical_board(wblank,7,7);
update_Graphical_board(wb_wrook,5,7);
printcase(7,7);
printcase(5,7);}
if(type == BSROCK)
{G.Bcastling_rights_left=0;G.Bcastling_rights_right=0;
update_Graphical_board(bblank,7,0);
update_Graphical_board(db_brook,5,0);
printcase(7,0);
printcase(5,0);}
if(type == WLROCK)
{G.Wcastling_rights_left=0;G.Wcastling_rights_right=0;
update_Graphical_board(bblank,0,7);
update_Graphical_board(wb_wrook,3,7);
printcase(0,7);
printcase(3,7);}
if(type == BLROCK)
{G.Bcastling_rights_left=0;G.Bcastling_rights_right=0;
update_Graphical_board(wblank,0,0);
update_Graphical_board(db_brook,3,0);
printcase(0,0);
printcase(3,0);}

if(type == PROMOTION)
{
      int cond1=1;

    while (cond1) {
    SDL_Event event;

    SDL_WaitEvent(&event);
            v=square_color(i,j);
        /* handle your event here */

          if(event.type==SDL_KEYDOWN)
          switch(event.key.keysym.sym){
      case SDLK_r:
          cond1=0;move[4]='q';
       if(G.halfplies%2==WHITE){if(v==WHITE)v=wb_wqueen;else v=db_wqueen;}
       else {if(v==WHITE)v=wb_bqueen;else v=db_bqueen;}
      break;
      case SDLK_c:
          cond1=0;move[4]='n';
       if(G.halfplies%2==WHITE){if(v==WHITE)v=wb_wknight;else v=db_wknight;}
       else {if(v==WHITE)v=wb_bknight;else v=db_bknight;}
      break;
      case SDLK_f:
        cond1=0;move[4]='b';
       if(G.halfplies%2==WHITE){if(v==WHITE)v=wb_wbishop;else v=db_wbishop;}
       else {if(v==WHITE)v=wb_bbishop;else v=db_bbishop;}
      break;
      case SDLK_t:
          cond1=0;move[4]='r';
       if(G.halfplies%2==WHITE){if(v==WHITE)v=wb_wrook;else v=db_wrook;}
       else {if(v==WHITE)v=wb_brook;else v=db_brook;}
      break;
        default:;
          }

    SDL_Delay(25);


}
update_Graphical_board(v,i,j);
printcase(i,j);
}


G.halfplies++;
strcpy(G.moves[G.halfplies-1],move);
}
}
else{//select piece if it is piece
    graphical_piece_selected=G.B.b[i][j];
    if(is_piece_a_piece(graphical_piece_selected))
    {iselection=i; jselection=j;
    is_piece_selected=1;}
}
}


int board_mouse_button_up(int x, int y){







    return 0;
    }


