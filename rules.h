extern const int ENUMSIZE;

enum Etype
{
    NORMAL=0,
    CAPTURE=1<<0,
    PROMOTION=1<<1,
    ENPASSANT=1<<2,
    WSROCK=1<<3,
    BSROCK=1<<4,
    WLROCK=1<<5,
    BLROCK=1<<6,
    BKING=1<<7,
    WKING=1<<8,
    LWROOKE=1<<9,
    RWROOKE=1<<10,
    LBROOKE=1<<11,
    RBROOKE=1<<12,
    PAWNM=1<<13
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
