#include "main.h"
#include <math.h>

/*0,0-------------- rownb-1,0
|
|
|
0,linenb-1 ------- rownb-1,linenb-1
*/
//int i, j : src square
//n, m : dst square

//3 fold repetition
//50 moves rule nearly done
//engine promotion
//engine rock chess960 ?

const int ENUMSIZE = sizeof(enum Etype);

void king_pos(enum piece_color c1, int* a,int* b)
{
    int i,j;enum CaseType P1;
    for(i=0;i<ROWNB;i++)
        for(j=0;j<LINENB;j++)
        {
            P1=G.B.b[i][j];
            if(is_piece_a_piece(P1))
               if(find_piece_from_CT(P1)==KING)
                    if(find_piece_color(P1)==c1)
                    {
                        *a=i;*b=j;return;
                    }
        }

}

int can_single_piece_attack_square(int i, int j, int n, int m, enum CaseType P)
{
    if(n==i&&m==j)return 0;
    enum piece p1=find_piece_from_CT(P);
    int k; int s1= (n-i)!=0 ? (n-i)/abs(n-i) : 0; int s2= (m-j)!=0 ? (m-j)/abs(m-j) : 0;
    double distance=sqrt((n-i)*(n-i)+(m-j)*(m-j));

    switch(p1)
    {
    case PAWN:
        if(n==i)return 0;
        if(distance>2.01)return 0;
        if((n-i)*(n-i)>1)return 0;
        if(find_piece_color(P)==BLACK)
                if(m-j<=0)return 0;

        if(find_piece_color(P)==WHITE)
                if(j-m<=0)return 0;


        break;
    case KNIGHT:
        if(distance==sqrt(5));else return 0;
        break;
    case KING:

        if(n>i+1||n<i-1||m>j+1||m<j-1)return 0;
        break;
    case BISHOP:
        //if(cdest!=csrc)return 0;
        if((n-i)*(n-i)!=(m-j)*(m-j))return 0;
        for(k=1;k<=abs(n-i-s1)||k<=abs(m-j-s2);k++)
        {P=G.B.b[i+k*s1][j+k*s2];
            if(is_piece_a_piece(P))return 0;}
        break;
    case ROOK:
        if(n!=i&&m!=j)return 0;
        for(k=1;k<=abs(n-i-s1)||k<=abs(m-j-s2);k++)
        {P=G.B.b[i+k*s1][j+k*s2];
            if(is_piece_a_piece(P))return 0;}
        break;
    case QUEEN:
        if((n-i)*(n-i)!=(m-j)*(m-j)&&n!=i&&m!=j)return 0;
        for(k=1;k<=abs(n-i-s1)||k<=abs(m-j-s2);k++)
        {P=G.B.b[i+k*s1][j+k*s2];
            if(is_piece_a_piece(P))return 0;}
        break;
    default:
        return 0;
    }
    return 1;
}
int who_attacks_square(int a, int b, int* n, int* m, int* k, int*l, enum piece_color attacker)
{
    int i,j,r=0;
    enum CaseType P1;enum piece_color c1;

    for(i=0;i<ROWNB;i++)
        for(j=0;j<LINENB;j++)
        {P1=G.B.b[i][j];
        if(is_piece_a_piece(P1)){
    c1=find_piece_color(P1);
    if(c1==attacker)
        if(can_single_piece_attack_square(i,j,a,b,P1))if(!r){*n=i;*m=j;r++;}else{*k=i;*l=j;return 1;}

        }
        }
    if(r)
        return 1;

    return 0;

}

int is_square_attacked(int n, int m, enum piece_color attacker)
{
    int i,j,r=0;
    enum CaseType P1;enum piece_color c1;

    for(i=0;i<ROWNB;i++)
        for(j=0;j<LINENB;j++)
        {P1=G.B.b[i][j];
        if(is_piece_a_piece(P1)){
    c1=find_piece_color(P1);
    if(c1==attacker)
    {
        if(can_single_piece_attack_square(i,j,n,m,P1))r++;
    }
        }
        }

    return r;
}

int absolute_pin(int i, int j, int* n, int* m, enum piece_color attacker)//pointers to save attacker position
{
    enum CaseType P;
    int a,b,r=0; king_pos(!attacker,&a,&b);if(i==a&&j==b)return 0;
    int k; int s1= (i-a)!=0 ? (i-a)/abs(i-a) : 0; int s2= (j-b)!=0 ? (j-b)/abs(j-b) : 0;
    if((i-a)*(i-a)!=(j-b)*(j-b)&&i!=a&&j!=b)return 0;

    for(k=1;(a+k*s1)<ROWNB&&(a+k*s1)>=0&&(b+k*s2)<LINENB&&(b+k*s2)>=0;k++)
        {P=G.B.b[a+k*s1][b+k*s2];
            if(is_piece_a_piece(P))if(find_piece_color(P)==attacker){
                enum piece p1=find_piece_from_CT(P);
                switch(p1)
                {
                case ROOK:
                    if(i!=a&&j!=b)return 0;
                    goto sucess;
                    break;
                case BISHOP:
                    if((i-a)*(i-a)!=(j-b)*(j-b))return 0;
                    goto sucess;
                    break;
                case QUEEN:
                    if((i-a)*(i-a)!=(j-b)*(j-b)&&i!=a&&j!=b)return 0;
                    goto sucess;
                    break;
                default:
                    return 0;
                    break;
                }
            }
            else{r++;if(r==2)return 0;}
        }
        return 0;
    sucess:
        if(r==1){if(((i>a&&i>a+k*s1)||(i<a&&i<a+k*s1))||((j>b&&j>b+k*s2)||(j<b&&j<b+k*s2)))return 0;else{*n=a+k*s1;*m=b+k*s2;}}else return 0;


        return 1;
}

int is_check(enum piece_color c1)
{
    int a,b; king_pos(c1,&a,&b);
    return is_square_attacked(a,b,!c1);
}


int is_move_valid(char* move,enum piece_color turn, enum Etype* type)
{
    enum Etype dum=0;
    if(!type)type=&dum;
    int i=move[0]-'a'; if(i<0&&i>=ROWNB)return 0;
    int j=move[1]-'1'; if(j<0&&j>=LINENB)return 0;
    int n=move[2]-'a'; if(n<0&&n>=ROWNB)return 0;
    int m=move[3]-'1'; if(m<0&&m>=LINENB)return 0;

    if((i==0&&j==0)||(n==0&&m==0))*type|=LBROOKE;
    if((i==0&&j==7)||(n==0&&m==7))*type|=LWROOKE;
    if((i==7&&j==0)||(n==7&&m==0))*type|=RBROOKE;
    if((i==7&&j==7)||(n==7&&m==7))*type|=RWROOKE;

    //find piece and color
    enum CaseType P1=G.B.b[i][j]; enum CaseType P2=G.B.b[n][m];enum piece_color c1,c2; enum piece p1;
    if(is_piece_a_piece(P1)){
     p1=find_piece_from_CT(P1);

    c1=find_piece_color(P1);
    if(turn==c1);else return 0; //check if piece moved is of the correct color
    }else return 0;//if P1 is not a piece then what do you move
    if(turn==WHITE)
    if(!strcmp(move,"O-O")||(!strcmp(move,"e8g8")&&G.B.b[4][7]==db_wking))
        {if(is_check(turn))return 0;
        if(!G.Wcastling_rights_right)return 0; if(!(!strcmp(move,"e8g8")&&G.B.b[4][7]==db_wking))return 0;
        if(is_square_attacked(5,7,!turn)||is_square_attacked(6,7,!turn))return 0;
        if(is_piece_a_piece(G.B.b[5][7])||is_piece_a_piece(G.B.b[6][7]))return 0;*type|=WSROCK;return 1;}
     if(turn==BLACK)
        if(!strcmp(move,"O-O")||(!strcmp(move,"e1g1")&&G.B.b[4][0]==wb_bking))
        {if(is_check(turn))return 0;if(!G.Bcastling_rights_right)return 0;if(!(!strcmp(move,"e1g1")&&G.B.b[4][0]==wb_bking))return 0;
           if(is_square_attacked(5,0,!turn)||is_square_attacked(6,0,!turn))return 0;
        if(is_piece_a_piece(G.B.b[5][0])||is_piece_a_piece(G.B.b[6][0]))return 0;
        *type|=BSROCK;return 1;}
     if(turn==WHITE)
    if(!strcmp(move,"O-O-O")||(!strcmp(move,"e8c8")&&G.B.b[4][7]==db_wking)){if(is_check(turn))return 0;
        if(!G.Wcastling_rights_left)return 0;if(!(!strcmp(move,"e8c8")&&G.B.b[4][7]==db_wking))return 0;
        if(is_square_attacked(3,7,!turn)||is_square_attacked(2,7,!turn))return 0;
        if(is_piece_a_piece(G.B.b[1][7])||is_piece_a_piece(G.B.b[2][7])||is_piece_a_piece(G.B.b[3][7]))return 0;*type|=WLROCK;return 1;}
        if(turn==BLACK)
        if(!strcmp(move,"O-O-O")||(!strcmp(move,"e1c1")&&G.B.b[4][0]==wb_bking))
        {if(is_check(turn))return 0;if(!G.Bcastling_rights_left)return 0;if(!(!strcmp(move,"e1c1")&&G.B.b[4][0]==wb_bking))return 0;
           if(is_square_attacked(3,0,!turn)||is_square_attacked(2,0,!turn))return 0;
        if(is_piece_a_piece(G.B.b[1][0])||is_piece_a_piece(G.B.b[2][0])||is_piece_a_piece(G.B.b[3][0]))return 0;
        *type|=BLROCK;return 1;}


    if(i==n&&j==m)return 0;//you can not move to the same square


    if(is_piece_a_piece(P2)){

    c2=find_piece_color(P2);
    if(c2==c1)return 0;//you cannot move to a piece of the same color
    }

    /*enum piece_color cdest=square_color(n,m);
    enum piece_color csrc=square_color(i,j);*/
    double distance=sqrt((n-i)*(n-i)+(m-j)*(m-j));

    enum piece p2=NOTPIECE; p2=find_piece_from_CT(P2); if(p2!=NOTPIECE)*type|=CAPTURE;
    int a,b,c,d,e,f,g,h; king_pos(turn,&a,&b); int che=is_check(turn);
        who_attacks_square(a,b,&c,&d, &g,&h,!turn);
    if(p1==KING){if(turn==WHITE)*type|=WKING;else *type|=BKING;if(n>i+1||n<i-1||m>j+1||m<j-1)return 0;//add code to prevent king into staying in check
            if(is_square_attacked(n,m,!turn))return 0;
            if(che&&find_piece_from_CT(G.B.b[c][d])!=PAWN&&find_piece_from_CT(G.B.b[c][d])!=KNIGHT){
                int s1= (c-a)!=0 ? -(c-a)/abs(c-a) : 0; int s2= (d-b)!=0 ? -(d-b)/abs(d-b) : 0; if(n==a+s1&&m==b+s2)return 0;}
            if(che==2&&find_piece_from_CT(G.B.b[g][h])!=PAWN&&find_piece_from_CT(G.B.b[g][h])!=KNIGHT){
                int s1= (g-a)!=0 ? -(g-a)/abs(g-a) : 0; int s2= (h-b)!=0 ? -(h-b)/abs(h-b) : 0; if(n==a+s1&&m==b+s2)return 0;}
            }
    else{

            if(che>=2)return 0;
    if(absolute_pin(i,j,&e,&f,!turn)){int k1,k2; int s1= (e-a)!=0 ? (e-a)/abs(e-a) : 0; int s2= (f-b)!=0 ? (f-b)/abs(f-b) : 0; if(s1)k1=(n-a)/s1;else k1=0;if(s2)k2=(m-b)/s2;else k2=0;
    if(abs(s1)&&abs(s2)&&k1!=k2)return 0;
            if(((n>a&&n>e)||(n<a&&n<e))||((m>b&&m>f)||(m<b&&m<f)))
        return 0;} //can't move the piece but in the inside cases of the pinner's ray
    if(che){

    if((c-a)*(c-a)!=(d-b)*(d-b)&&c!=a&&d!=b){if(n!=c||m!=d)return 0;} //knight check only capture
    else {
            if(find_piece_from_CT(G.B.b[c][d])==PAWN){//pawn check, if not moving the king, only move is to capture pawn by en passant or direct capture
                if(p1!=PAWN){if(n!=c||m!=d)return 0;}
                else{
                        if(j!=3+c1){if(n!=c||m!=d)return 0;}//no en passant so pawn must capture
                    else{if(n!=c||m!=2+3*c1)return 0;}//must be an en passant
                }
            }
            else{
            int k1,k2; int s1= (c-a)!=0 ? (c-a)/abs(c-a) : 0; int s2= (d-b)!=0 ? (d-b)/abs(d-b) : 0; if(s1)k1=(n-a)/s1;else k1=0;if(s2)k2=(m-b)/s2;else k2=0;
    if(abs(s1)&&abs(s2)&&k1!=k2)return 0;
            if(((n>a&&n>c)||(n<a&&n<c))||((m>b&&m>d)||(m<b&&m<d)))//otherwise capture(bishop,rook,queen) or put piece in front
        return 0;}}

    }

    if(p1!=PAWN)
     {if(!can_single_piece_attack_square(i,j,n,m,P1))return 0;}
    else{//pawn special
            *type|=PAWNM;
            if(distance>2.01)return 0;
        if((n-i)*(n-i)>1)return 0;
            if(c1==BLACK){
                if(m-j<=0)return 0;
        if(j!=1)if(distance>sqrt(2))return 0;
        if(distance==2&&is_piece_a_piece(G.B.b[i][2]))return 0;
        }
        if(c1==WHITE){
                if(j-m<=0)return 0;
        if(j!=6)if(distance>sqrt(2))return 0;
        if(distance==2&&is_piece_a_piece(G.B.b[i][5]))return 0;
        }
        if(n!=i&&p2==NOTPIECE){//en passant
                if(c1==WHITE)if(j!=3)return 0; if(c1==BLACK)if(j!=4)return 0;
                char str[5]={0};str[0]='a'+n; str[1]= turn==WHITE ? 1 : 6;str[1]+='1';str[2]='a'+n;str[3]= turn==WHITE ? 3 : 4;
        if(find_piece_from_CT(G.B.b[n][(int)(str[3])])!=PAWN)return 0;
        str[3]+='1';
        //SDL_Delay(25);

                if(!strncmp(&(G.moves[G.halfplies-1][0]),str,4));else return 0; *type|=ENPASSANT;

        }
        if(n==i&&p2!=NOTPIECE)return 0;
        if((c1==WHITE&&m==0)||(c1==BLACK&&m==7))*type|=PROMOTION;

    }
    }

    return 1;
}


int is_checkmate(enum piece_color c1)
{
    if(!is_check(c1))return 0;
    int n,m;
    int i,j; char move[6]={0};
    for(i=0;i>=0&&i<ROWNB;i++)
        for(j=0;j>=0&&j<LINENB;j++)
            for(n=0;n>=0&&n<ROWNB;n++)
                for(m=0;m>=0&&m<LINENB;m++)
        {
            move[0]=i+'a';
            move[1]=j+'1';
            move[2]=n+'a';
            move[3]=m+'1';
            if(is_move_valid(move,c1,NULL))return 0;
        }



    return 1;

}

int is_pat(enum piece_color c1)
{
    if(is_check(c1))return 0;
    int n,m;
    int i,j; char move[6]={0};
    for(i=0;i>=0&&i<ROWNB;i++)
        for(j=0;j>=0&&j<LINENB;j++)
            for(n=0;n>=0&&n<ROWNB;n++)
                for(m=0;m>=0&&m<LINENB;m++)
        {
            move[0]=i+'a';
            move[1]=j+'1';
            move[2]=n+'a';
            move[3]=m+'1';
            if(is_move_valid(move,c1,NULL))return 0;
        }



    return 1;
}


