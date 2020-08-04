#include "main.h"

enum GM
{
    PAT,
    MAT,
    DRAW_AGREED,
    THREE_FOLD,
    FIFTY_MOVE,
    ABORT,
    NEW,
    NEWMOVE,
    UNDOMOVE,
    EXIT_NOW
};

int play_game()
{
    for(;;)
    {


if(is_checkmate(G.halfplies%2))exit(55);
    if(is_pat(G.halfplies%2))exit(56);
    if(G.halffiftymoves>=100)exit(56);
char move[6]={0};
for(;;) //ask for move till move is valid
 {QueryMoveFromPlayer(G.players[G.halfplies%2],move);
 enum Etype type=0;
if(is_move_valid(move,G.halfplies%2,&type))
{update_board(move,type,&G.players[G.halfplies%2]);break;}
else board_bad_move();}



    G.halffiftymoves++;
G.halfplies++;
strncpy(G.moves[G.halfplies-1],move,MAX_MOVES_NB);

}
}
