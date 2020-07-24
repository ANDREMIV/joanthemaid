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

int init_player_bot(struct player *p) //create engine thread, create pipes with chess GUI
{
    #ifdef WINWIN_BUILD
    SECURITY_ATTRIBUTES saAttr;

   printf("\n->Start of parent execution.\n");

// Set the bInheritHandle flag so pipe handles are inherited.

   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   saAttr.bInheritHandle = TRUE;
   saAttr.lpSecurityDescriptor = NULL;

// Create a pipe for the child process's STDOUT.

   if ( ! CreatePipe(&p->g_hChildStd_OUT_Rd, &p->g_hChildStd_OUT_Wr, &saAttr, 0) )
      ErrorExit(TEXT("StdoutRd CreatePipe"));

// Ensure the read handle to the pipe for STDOUT is not inherited.

   if ( ! SetHandleInformation(&p->g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      ErrorExit(TEXT("Stdout SetHandleInformation"));

// Create a pipe for the child process's STDIN.

   if (! CreatePipe(&p->g_hChildStd_IN_Rd, &p->g_hChildStd_IN_Wr, &saAttr, 0))
      ErrorExit(TEXT("Stdin CreatePipe"));

// Ensure the write handle to the pipe for STDIN is not inherited.

   if ( ! SetHandleInformation(&p->g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
      ErrorExit(TEXT("Stdin SetHandleInformation"));



    #endif // WINWIN_BUILD
}

void CreateChildProcess(struct player *p)
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{
   TCHAR* szCmdline=&p->command;
   //PROCESS_INFORMATION piProcInfo;
   //STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE;

// Set up members of the PROCESS_INFORMATION structure.

   ZeroMemory( &p->piProcInfo, sizeof(PROCESS_INFORMATION) );

// Set up members of the STARTUPINFO structure.
// This structure specifies the STDIN and STDOUT handles for redirection.

   ZeroMemory( &p->siStartInfo, sizeof(STARTUPINFO) );
   p->siStartInfo.cb = sizeof(STARTUPINFO);
   p->siStartInfo.hStdError = p->g_hChildStd_OUT_Wr;
   p->siStartInfo.hStdOutput = p->g_hChildStd_OUT_Wr;
   p->siStartInfo.hStdInput = p->g_hChildStd_IN_Rd;
   p->siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

// Create the child process.

   bSuccess = CreateProcess(NULL,
      szCmdline,     // command line
      NULL,          // process security attributes
      NULL,          // primary thread security attributes
      TRUE,          // handles are inherited
      0,             // creation flags
      NULL,          // use parent's environment
      NULL,          // use parent's current directory
      &p->siStartInfo,  // STARTUPINFO pointer
      &p->piProcInfo);  // receives PROCESS_INFORMATION

   // If an error occurs, exit the application.
   if ( ! bSuccess )
      ErrorExit(TEXT("CreateProcess"));
   else
   {
      // Close handles to the child process and its primary thread.
      // Some applications might keep these handles to monitor the status
      // of the child process, for example.

      CloseHandle(p->piProcInfo.hProcess);
      CloseHandle(p->piProcInfo.hThread);

      // Close handles to the stdin and stdout pipes no longer needed by the child process.
      // If they are not explicitly closed, there is no way to recognize that the child process has ended.

      CloseHandle(p->g_hChildStd_OUT_Wr);
      CloseHandle(p->g_hChildStd_IN_Rd);
   }
}

void initgame()
{
    G.halfplies=0;
    G.halffiftymoves=0;
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
