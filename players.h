

struct player{

char name[64];
char description[2048];
int is_human;
struct SDL_Rect Vscreen_player_association;
struct SDL_Texture* photo;
int iswhite;
char command[2048];
int time_left;//in ms
#ifdef WINWIN_BUILD
PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   HANDLE g_hChildStd_IN_Rd;
HANDLE g_hChildStd_IN_Wr;
HANDLE g_hChildStd_OUT_Rd;
HANDLE g_hChildStd_OUT_Wr;
#endif // WINWIN_BUILD

};


int init_player(struct player *p);
