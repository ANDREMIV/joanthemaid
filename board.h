
#define ROWNB 8
#define LINENB 8


extern enum CaseType graphical_piece_selected;
extern int is_piece_selected;

struct Board{ ///Holds the necessary info to play a particular game
int b[ROWNB][LINENB];
SDL_Rect Vscreen_board_association;
int Csize;
};

int board_mouse_button_down(int x, int y);
int board_mouse_button_up(int x, int y);

//white left rook line
#define WLRL 7
#define WRRL 7
#define WLRR 0
#define WRRR 7
#define BLRL 0
#define BRRL 0
#define BLRR 0
#define BRRR 7

//white king row
#define WKR 4
#define WKL 7
#define BKR 4
#define BKL 0

//white pawn launch line
#define WPLL 6
#define BPLL 1

//white pawn en-passant line
#define WPEPL 3
#define BPEPL 4
