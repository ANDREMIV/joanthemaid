
#include "main.h"




#ifdef WINWIN_BUILD
/*void ErrorExit(char* text)
{
    printf("\n%s\n",text);
    exit(1);
}*/

// Format a readable error message, display a message box,
// and exit from the application.
void ErrorExit(PTSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}
#endif // WINWIN_BUILD

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
