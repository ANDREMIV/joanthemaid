#include "main.h"

int init_player(struct player* p){
SDL_Surface *s;
s=IMG_Load("marie2.jpg");
p->photo= SDL_CreateTextureFromSurface(V.renderer, s);
SDL_FreeSurface(s);
}
