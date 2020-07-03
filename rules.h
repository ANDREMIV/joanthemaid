enum Etype
{
    NORMAL,
    PROMOTION,
    ENPASSANT,
    WSROCK,
    BSROCK,
    WLROCK,
    BLROCK,
    BKING,
    WKING,
    LROOK,

};

/*
CAPTURE
NOCAPTURE
PAWNMOVE
KINGMOVE
WLCORNER
WRCORNER
BLCORNER
BRCORNER

*/

int is_pat(enum piece_color c1);
int is_checkmate(enum piece_color c1);
