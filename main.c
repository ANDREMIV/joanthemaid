
#include "main.h"

///SDL ORIENTATION
/*
X : 0 -- - - -- >
Y: 0
   |
   |
   v
*/





int Argv; char **Args;


int main(int argv, char** args)
{

    Argv = argv;
    Args=args;
    initgame();
    initvideo();
    init_player(&G.players[0]);

    init_CaseType();
    printgrid();



while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        /* handle your event here */

          if(event.type==SDL_KEYDOWN)
                  goto quit;
          if(event.type==SDL_QUIT)
                  goto quit;
         if(event.type==SDL_MOUSEBUTTONDOWN)
                  {
                    which_mouse_hit(&event);
                      //SDL_RenderCopy(V.renderer, G.players[0].photo, NULL, NULL);
    //SDL_RenderPresent(V.renderer);

                  }
        if(event.type==SDL_MOUSEBUTTONUP)
                  {

                  }

    SDL_Delay(25);

    }
    event.type=0;
    /* do some other stuff here -- draw your app, etc. */
}

quit:


TTF_Quit();
IMG_Quit();


//SDL_DestroyTexture(board);
  SDL_DestroyRenderer(V.renderer);
  SDL_DestroyWindow(V.window);
  SDL_Quit();


    return 0;
}
