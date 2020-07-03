#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <string.h>
#include <SDL_image.h>

#include "case_type.h"
#include "board.h"
#include "rules.h"
#include "players.h"


struct Game{ ///Holds the necessary info to play a particular game
struct Board B;
int halfplies;
int halffiftymoves;
int enpassant_possible;
int Wcastling_rights_left;
int Wcastling_rights_right;
int Bcastling_rights_left;
int Bcastling_rights_right;
#define MAX_MOVES_NB 100
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
void printcase(int i, int j);
int which_mouse_hit(SDL_Event *e);
int is_move_valid(char* move,enum piece_color turn, int* type);
