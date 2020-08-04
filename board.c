#include "main.h"


///SDL ORIENTATION
/*
X : 0 -- - - -- >
Y: 0
   |
   |
   v
*/
//static SDL_Rect Psrc,Pdst;
static SDL_Rect Rsrc,Rdst;
static int is_piece_selected=0;
static int is_piece_selected_for_drag=0;
static enum CaseType gps;
static int iselection; static int jselection; static int curhp;
static int iselection2; static int jselection2;
static int first=0;

__inline__ void bridge_representation_board(char *move)
{
    move[1]='9'-move[1]+'0';move[3]='9'-move[3]+'0';
}


void update_Graphical_board(enum CaseType X,int i, int j)//row-1,line-1
{
    G.B.b[i][j]=X;
}

int board_mouse_motion(int relx, int rely)
{

    if(is_piece_selected_for_drag){
    SDL_Rect v=G.B.Vscreen_board_association;
    /*if(first)
    SDL_RenderCopy(V.renderer, G.B.back, &Psrc, &Pdst);
    if(! first)first=1;*/
        SDL_RenderCopy(V.renderer, G.B.back, &Rsrc, &Rdst);
    int q,Q=100; q=(Q=relx-G.B.Csize/2)>=0 ? Q:0;
                               Rdst.x=v.x+q;
                               q=(Q=rely-G.B.Csize/2)>=0 ? Q:0;
        Rdst.y=v.y+q;
        int q1,q2;
        q1=(Q=v.w-relx)<G.B.Csize/2 ? Q:G.B.Csize/2;
        q2=(Q=relx)<G.B.Csize/2 ? Q:G.B.Csize/2; Rdst.w=q1+q2;
        q1=(Q=v.h-rely)<G.B.Csize/2 ? Q:G.B.Csize/2;
        q2=(Q=rely)<G.B.Csize/2 ? Q:G.B.Csize/2; Rdst.h=q1+q2;
        Rsrc.x=(Q=G.B.Csize/2-relx)>0 ? Q:0;
        Rsrc.y=(Q=G.B.Csize/2-rely)>0 ? Q:0;
        Rsrc.w=Rdst.w;
        Rsrc.h=Rdst.h;
         SDL_UpdateTexture(G.B.back,
                      &Rsrc,
                      G.B.img+4*(Rdst.x+Rdst.y*v.w),
                      4*v.w);
        SDL_RenderCopy(V.renderer, CaseType_texture_association[gps], &Rsrc, &Rdst);
    SDL_RenderPresent(V.renderer);
    //Psrc=Rsrc; Pdst=Rdst;
    }
    return 0;
}

board_util(int i, int j)
{
    SDL_Rect vba=G.B.Vscreen_board_association;


                           enum CaseType v;enum piece_color c=square_color(iselection,jselection); if(c==WHITE)v=wblank;else v=bblank;
                           printcase(i,j,v);
                           SDL_RenderReadPixels(V.renderer,
                         &vba,
                         0,
                         G.B.img,
                         4*vba.w);//capture screen for piece drag and drop
                         //first=0;
                         SDL_SetTextureAlphaMod(CaseType_texture_association[gps],
                           128);printcase(i,j,gps);
    gps=change_piece_bg_color(gps, WHITE);
        SDL_SetTextureAlphaMod(CaseType_texture_association[gps],
                           128);
                           Rdst.x=vba.x+i*G.B.Csize;
                           Rdst.y=vba.y+j*G.B.Csize;
                           Rdst.w=G.B.Csize;
                           Rdst.h=G.B.Csize;
                        Rsrc.x=0;
        Rsrc.y=0;
        Rsrc.w=G.B.Csize;
        Rsrc.h=G.B.Csize;
            SDL_UpdateTexture(G.B.back,
                      &Rsrc,
                      G.B.img+4*(Rdst.x+Rdst.y*vba.w),
                      4*vba.w);
}

int board_mouse_button_down(int x, int y, char* move){ //allow to construct human move, return 1 if a move has been constructed
    if(!move)return 0;


SDL_Rect vba=G.B.Vscreen_board_association;

    int i=x/G.B.Csize; int j=y/G.B.Csize;

    if(is_piece_selected&&(i!=iselection||j!=jselection)){
is_piece_selected=0;
move[0]=iselection+'a';
move[1]=jselection+'1';
move[2]=i+'a';
move[3]=j+'1';
move[4]=0;
move[5]=0;
iselection2=i; jselection2=j;
//if(!first)first=1;
return 1;
}

else{//select piece if it is piece
        gps=G.B.b[i][j];
    if(is_piece_a_piece(gps))
    {iselection=i; jselection=j;

    is_piece_selected=1;is_piece_selected_for_drag=1;
        board_util(i,j);}

return 0;}}

///add support for human vs bot promotions
void update_board(char* move, enum Etype type,struct player* p){ //move is validated

        int iselection=move[0]-'a';
    int jselection=move[1]-'1';
    int i=move[2]-'a';
    int j=move[3]-'1';
enum CaseType graphical_piece_selected=G.B.b[iselection][jselection];
graphical_piece_selected=change_piece_bg_color(graphical_piece_selected, square_color(i,j));
update_Graphical_board(graphical_piece_selected,i,j);


enum CaseType v;enum piece_color c=square_color(iselection,jselection); if(c==WHITE)v=wblank;else v=bblank;
update_Graphical_board(v,iselection,jselection);

if(type&ENPASSANT){

    c=square_color(i,jselection); if(c==WHITE)v=wblank;else v=bblank;
update_Graphical_board(v,i,jselection);
printcase(i,jselection,-1);
}
printcase(iselection,jselection,-1);
printcase(i,j,-1);

if(type&WSROCK)
{G.Wcastling_rights_left=0;G.Wcastling_rights_right=0;
update_Graphical_board(wblank,7,7);
update_Graphical_board(wb_wrook,5,7);
printcase(7,7,-1);
printcase(5,7,-1);}
if(type&BSROCK)
{G.Bcastling_rights_left=0;G.Bcastling_rights_right=0;
update_Graphical_board(bblank,7,0);
update_Graphical_board(db_brook,5,0);
printcase(7,0,-1);
printcase(5,0,-1);}
if(type&WLROCK)
{G.Wcastling_rights_left=0;G.Wcastling_rights_right=0;
update_Graphical_board(bblank,0,7);
update_Graphical_board(wb_wrook,3,7);
printcase(0,7,-1);
printcase(3,7,-1);}
if(type&BLROCK)
{G.Bcastling_rights_left=0;G.Bcastling_rights_right=0;
update_Graphical_board(wblank,0,0);
update_Graphical_board(db_brook,3,0);
printcase(0,0,-1);
printcase(3,0,-1);}
if(type&RWROOKE)G.Wcastling_rights_right=0;
if(type&LWROOKE)G.Wcastling_rights_left=0;
if(type&RBROOKE)G.Bcastling_rights_right=0;
if(type&LBROOKE)G.Bcastling_rights_left=0;
if(type&BKING){G.Bcastling_rights_left=0;G.Bcastling_rights_right=0;}
if(type&WKING){G.Wcastling_rights_left=0;G.Wcastling_rights_right=0;}

if(type&PAWNM||type&CAPTURE)G.halffiftymoves=0; ///before or after incrementation ???

if(type&PROMOTION)
{
      char d;
    d=ask_player_promotion(p,move);
            c=square_color(i,j);

          switch(d){
      case 'q':
       if(G.halfplies%2==WHITE){if(c==WHITE)v=wb_wqueen;else v=db_wqueen;}
       else {if(c==WHITE)v=wb_bqueen;else v=db_bqueen;}
      break;
      case 'n':
       if(G.halfplies%2==WHITE){if(c==WHITE)v=wb_wknight;else v=db_wknight;}
       else {if(c==WHITE)v=wb_bknight;else v=db_bknight;}
      break;
      case 'b':
       if(G.halfplies%2==WHITE){if(c==WHITE)v=wb_wbishop;else v=db_wbishop;}
       else {if(c==WHITE)v=wb_bbishop;else v=db_bbishop;}
      break;
      case 'r':
       if(G.halfplies%2==WHITE){if(c==WHITE)v=wb_wrook;else v=db_wrook;}
       else {if(c==WHITE)v=wb_brook;else v=db_brook;}
      break;
        default:;
          }


update_Graphical_board(v,i,j);
printcase(i,j,-1);
}

}




int board_mouse_button_up(int x, int y,char *move){
int i=x/G.B.Csize; int j=y/G.B.Csize;
    if(is_piece_selected_for_drag){

    SDL_SetTextureAlphaMod(CaseType_texture_association[gps],
                           255);
                           gps=change_piece_bg_color(gps, BLACK);
                           SDL_SetTextureAlphaMod(CaseType_texture_association[gps],
                           255);
                          // is_piece_selected_for_drag=0;
                           SDL_RenderCopy(V.renderer, G.B.back, &Rsrc, &Rdst);
                           SDL_RenderPresent(V.renderer);
                           //if move was not accepted
                           //return board_mouse_button_down( x, y, move);


    //if(is_piece_selected_for_drag){
is_piece_selected_for_drag=0;is_piece_selected=0;
move[0]=iselection+'a';
move[1]=jselection+'1';
move[2]=i+'a';
move[3]=j+'1';
move[4]=0;
move[5]=0;
iselection2=i; jselection2=j;
if(!first)first=1;
return 1;
}





    return 0;
    }

    int board_bad_move()
    {
        enum CaseType CT;
        //printgrid();
        if((CT=G.B.b[iselection][jselection])!=db_wpawn)
            ;
        printcase(iselection,jselection,-1);
if(iselection2==iselection&&jselection2==jselection&&first)//+ chrono condition
{
    first=0;//is_piece_selected_for_drag=1;
    is_piece_selected=1;return 0;}
if(!first)
{

    enum CaseType Pt=G.B.b[iselection2][jselection2];
    if(is_piece_a_piece(Pt))if(find_piece_color(Pt)==G.halfplies%2){iselection=iselection2;jselection=jselection2;gps=Pt;
    is_piece_selected=1;is_piece_selected_for_drag=1;
    board_util(iselection,jselection);}else {is_piece_selected=0;is_piece_selected_for_drag=0;}
return 0;}

    }


