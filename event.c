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

#ifdef WINWIN_BUILD


void WriteToPipe(HANDLE g_hChildStd_IN_Wr)

// Read from a file and write its contents to the pipe for the child's STDIN.
// Stop when there is no more data.
{
   DWORD dwRead, dwWritten;
   CHAR chBuf[BUFSIZE];
   BOOL bSuccess = FALSE;

   for (;;)
   {
      //bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, NULL);
      //if ( ! bSuccess || dwRead == 0 ) break;

      bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);
      if ( ! bSuccess ) break;
   }

/*// Close the pipe handle so the child process stops reading.

   if ( ! CloseHandle(g_hChildStd_IN_Wr) )
      ErrorExit(TEXT("StdInWr CloseHandle"));*/
}

void ReadFromPipe(HANDLE g_hChildStd_OUT_Rd)

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT.
// Stop when there is no more data.
{
   DWORD dwRead, dwWritten;
   CHAR chBuf[BUFSIZE];
   BOOL bSuccess = FALSE;
   //HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   for (;;)
   {
      bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
      if( ! bSuccess || dwRead == 0 ) break;

     // bSuccess = WriteFile(hParentStdOut, chBuf,
         //                  dwRead, &dwWritten, NULL);
      //if (! bSuccess ) break;
   }
}
#endif // WINWIN_BUILD
