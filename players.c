#include "main.h"

int init_player(struct player* p){
    p->is_human=1;
SDL_Surface *s;
s=IMG_Load("marie2.jpg");
p->photo= SDL_CreateTextureFromSurface(V.renderer, s);
SDL_FreeSurface(s);
return 0;
}



int QueryMoveFromPlayer(struct player p,char *move) //query user input too for if the user wants to quit
{
    if(p.is_human){

/*
SDL_CreateTexture(V.renderer,
                               SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                               G.B.Csize,
                               G.B.Csize); //create texture of dynamic background behind piece to be dragged
                               int SDL_LockTexture(G.B.back,
                    const SDL_Rect* rect,
                    void**          pixels,
                    int*            pitch);

SDL_UnlockTexture(G.B.back);*/



        /*SDL_RenderCopy(V.renderer, G.B.back, &Rsrc, &Rdst);
    SDL_RenderCopy(V.renderer, CaseType_texture_association[v], &Rsrc, &Rdst);}
    SDL_RenderPresent(V.renderer);*/








int relx, rely; enum BHtype t;
            while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        /* handle your event here */

          if(event.type==SDL_KEYDOWN)
                  if(event.key.keysym.sym==SDLK_ESCAPE)goto quit;
          if(event.type==SDL_QUIT)
                  goto quit;
         if(event.type==SDL_MOUSEBUTTONDOWN) //select
                  {

                    position_mouse(&event,&t,&relx,&rely);
                    if(t==BHBOARD)//the user tries to make a selection
                        if(event.button.button==SDL_BUTTON_LEFT)
                        if(board_mouse_button_down(relx,rely,move))
                    return 1;}
                      //SDL_RenderCopy(V.renderer, G.players[0].photo, NULL, NULL);
    //SDL_RenderPresent(V.renderer);


        if(event.type==SDL_MOUSEMOTION)//drag
        {
            position_mouse(&event,&t,&relx,&rely);
            if(t==BHBOARD)//the user may drag)
                        board_mouse_motion(relx,rely);
        }
        if(event.type==SDL_MOUSEBUTTONUP)//drop
                  {
                    position_mouse(&event,&t,&relx,&rely);
            if(t==BHBOARD)//the user may drop
                if(event.button.button==SDL_BUTTON_LEFT)

                        if(board_mouse_button_up(relx,rely,move))return 1;

                  }
    }
    event.type=0;
    SDL_Delay(5);

    }
    /* do some other stuff here -- draw your app, etc. */
}
    else
    {
        char moves[MAX_MOVES_NB*6+40]; memset((void*)moves,0,MAX_MOVES_NB*6+40);
        //send position to engines, listen to their output and retrieves their best move
        strncat(moves,"position startpos moves",30);
        //strncat(moves,"position fen nnnnknnn/pppppppp/8/8/8/8/PPPPPPPP/R1BQKB1R w KQ - 0 1 moves",80);
        {
            int i;for(i=0;i<G.halfplies;i++){
                strncat(moves," ",2);
                char m[6]={0};
            strncat(m,G.moves[i],6);
            bridge_representation_board(m);
            strncat(moves,m,6);}
        }
        strncat(moves,"\n",3);
        WriteToPipe(moves,&p);
        WriteToPipe("isready\n",&p);

        for(;;)
        {
            char mr[BUFSIZE]; memset((void*)mr,0,BUFSIZE);
            //SDL_Delay(100);
            ReadFromPipe(&p,mr);
            if(strstr(mr,"readyok"))
                break;
        }
        WriteToPipe("go depth 10\n",&p);
        char *ptr;
        for(;;)
        {
            char mr[BUFSIZE]; memset((void*)mr,0,BUFSIZE);
            //SDL_Delay(100);
            ReadFromPipe(&p,mr);
            if((ptr=strstr(mr,"bestmove")))break;
        }
        sscanf(ptr,"%*s %s",move);
        bridge_representation_board(move);
    }
return 0;

    quit:


TTF_Quit();
IMG_Quit();


//SDL_DestroyTexture(board);
  if(!p.is_human)
  WriteToPipe("quit\n",&p);
  SDL_DestroyRenderer(V.renderer);
  SDL_DestroyWindow(V.window);
  SDL_Quit();
  exit(0);

}

char ask_player_promotion(struct player* p,char* move)
{
    if(p->is_human)
    {


    int cond1=1;
        while (cond1) {
    SDL_Event event;

    SDL_WaitEvent(&event);
        /* handle your event here */

          if(event.type==SDL_KEYDOWN)
          switch(event.key.keysym.sym){
      case SDLK_r:
          cond1=0;move[4]='q';return 'q';
      break;
      case SDLK_c:
          cond1=0;move[4]='n';return 'n';
      break;
      case SDLK_f:
        cond1=0;move[4]='b';return 'b';
      break;
      case SDLK_t:
          cond1=0;move[4]='r';return 'r';
      break;
        default:;
          }

    SDL_Delay(25);


}
    }
    else{

        return move[4];
    }
    return 'q';
}
