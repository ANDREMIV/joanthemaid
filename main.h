




#include <SDL.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <string.h>
#include <SDL_image.h>

#ifdef WINWIN_BUILD
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>


BOOL
APIENTRY
MyCreatePipeEx(
    OUT LPHANDLE lpReadPipe,
    OUT LPHANDLE lpWritePipe,
    IN LPSECURITY_ATTRIBUTES lpPipeAttributes,
    IN DWORD nSize,
    DWORD dwReadMode,
    DWORD dwWriteMode
    );
void ErrorExit(PTSTR lpszFunction);
#endif // WINWIN_BUILD

#include "case_type.h"
#include "rules.h"
#include "players.h"
#include "board.h"

#include "event.h"

#define BUFSIZE 4096



struct Game{ ///Holds the necessary info to play a particular game
struct Board B;
int halfplies;
int halffiftymoves;
int enpassant_possible;
int Wcastling_rights_left;
int Wcastling_rights_right;
int Bcastling_rights_left;
int Bcastling_rights_right;
#define MAX_MOVES_NB 1000
char moves[MAX_MOVES_NB][6];
int condensed[MAX_MOVES_NB];
struct player players[2];
};

struct VideoHandle{
    SDL_Window *window;
    SDL_Renderer *renderer;
int xVscreen, yVscreen;
};

extern struct Game G;
extern struct VideoHandle V;
extern int Argv;
extern char **Args;

int init_CaseType();
void initgame();
void initvideo();
void printgrid();
void printcase(int i, int j,enum CaseType CT);
int is_move_valid(char* move,enum piece_color turn, enum Etype* type);
void position_mouse(SDL_Event *e, enum BHtype *type, int* relx, int *rely); //detect where mouse button hit
void WriteToPipe(char* s, struct player *p);
void ReadFromPipe(struct player *p, char* mr);
void CreateChildProcess(struct player *p);
int init_player_bot(struct player *p);
