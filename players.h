
struct player{

char name[64];
char description[2048];
int is_human;
struct SDL_Rect Vscreen_player_association;
struct SDL_Texture* photo;
int iswhite;
int time_left;
};


int init_player(struct player *p);
