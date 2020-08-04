///To do list
//3 fold repetitions
//50 moves rules testing
//chess960
//linux support
//android support
//chess clock support
//simple gui
//playing over internet
//opening namings
//survival mode
//hand & brain mode
//syzygy endgame table bases
//tournament settings
//difficulty settings
//new engine installation
//new game
//fen support
//resize window
//undo move
//sound support
//music
//blind mode
//color pick



#include "main.h"

int play_game();


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
    init_CaseType();
    init_player(&G.players[0]);
    //init_player(&G.players[1]);
    //init_player_bot(&G.players[0]);
    init_player_bot(&G.players[1]);


    printgrid();

    play_game();





    return 0;
}
