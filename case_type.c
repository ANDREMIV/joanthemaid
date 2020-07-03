
#include "main.h"

int is_piece_a_piece(enum CaseType p)
{
    if(p!=wblank&&p!=bblank)return 1;
    else return 0;
}

enum piece find_piece_from_CT(enum CaseType p)
{
    if(p/12==2)return NOTPIECE;
    p%=12;
    p/=2;
    return p;
}

enum piece_color find_piece_color(enum CaseType p)
{
   // if(find_piece_from_CT(p)!=NOTPIECE)
    if(p%2) return BLACK;
    else return WHITE;

    //return NOCOL;
}
enum piece_color find_piece_bg_color(enum CaseType p)
{
    if(p==wblank)return WHITE;
    if(p<12) return WHITE;
    else return BLACK;
}

enum CaseType change_piece_bg_color(enum CaseType p, enum piece_color bg)
{
    //check if bg color match with target color;
int c=find_piece_bg_color(p);
if(c==bg);
else p+=12*(1-2*c); //hack modify bg color of piece
return p;
}


enum piece_color square_color(int i, int j)
{
    if((i+j)%2)return BLACK;
    else return WHITE;
};

char CaseType_char_association[]="klqwrtbvnmpoKLQWRTBVNMPO +";
SDL_Texture* CaseType_texture_association[NBCASETYPE];

int translate_char_to_case_type(char c)
{
    int i; for(i=0;i<NBCASETYPE;i++)if(CaseType_char_association[i]==c)return i;
}

int init_CaseType()
{

// load font.ttf at size 16 into font
TTF_Font *font;
font=TTF_OpenFont("CHESS3.TTF", G.B.Csize);
if(!font)
printf("TTF_OpenFont: %s\n", TTF_GetError());

SDL_Color color={0x00,0x00,0x00};
SDL_Surface *s;


int i; for(i=0;i<NBCASETYPE;i++){char Cur[2];Cur[0]=CaseType_char_association[i];Cur[1]=0;
if(!(s=TTF_RenderText_Blended(font,Cur,color)))
printf("TTF_OpenFont: %s\n", TTF_GetError());
    CaseType_texture_association[i] = SDL_CreateTextureFromSurface(V.renderer, s);
    SDL_FreeSurface(s);
}

TTF_CloseFont(font);


return 1;
}
