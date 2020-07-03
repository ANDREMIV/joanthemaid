#define NBCASETYPE 26

enum piece_color
{
    WHITE,
    BLACK//,
 //   NOCOL
};

enum piece
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    NOTPIECE
};

enum CaseType
{ //wb white background; db dark background
    wb_wking,
    wb_bking,
    wb_wqueen,
    wb_bqueen,
    wb_wrook,
    wb_brook,
    wb_wbishop,
    wb_bbishop,
    wb_wknight,
    wb_bknight,
    wb_wpawn,
    wb_bpawn,
    db_wking,
    db_bking,
    db_wqueen,
    db_bqueen,
    db_wrook,
    db_brook,
    db_wbishop,
    db_bbishop,
    db_wknight,
    db_bknight,
    db_wpawn,
    db_bpawn,
    wblank,
    bblank,
};
extern char CaseType_char_association[];
extern SDL_Texture* CaseType_texture_association[];

int translate_char_to_case_type(char c);
int is_piece_a_piece(enum CaseType p);
enum piece_color find_piece_color(enum CaseType p);
enum piece_color find_piece_bg_color(enum CaseType p);
enum piece find_piece_from_CT(enum CaseType p);
enum piece_color square_color(int i, int j);
enum CaseType change_piece_bg_color(enum CaseType p, enum piece_color bg);
