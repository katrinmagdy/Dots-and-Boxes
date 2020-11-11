#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include<string.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

int count=0,countA=0,countB=0;
char check;
int x,y,n,m,ur=0,xc,yc;
signed int undo1=-1;
char player;
int i ,j,nl,k;
char be;
char one_two;
char newg_ex_t10;
char unre;
long int begin_time, current_time, total_seconds ,sstotal_seconds=0;
char extra;
int gameno;


typedef struct{
    int X;
    int Y;
    char colour;
    char line;
    char p;
}emove;
emove undo_redo[100];


//struct to save info of stored game in a file
typedef struct{
    char sgame[5][5];
    int sur;
    signed int sundo1;
    char pAname[100];
    char pBname[100];
    int sscoreA;
    int sscoreB;
    long int stotal_seconds;
    int scount;
    int scountA;
    int scountB;
    int snl;
    char turnplayer;
    char mode;
}save_game_beginner;

typedef struct{
    char sgame[11][11];
    int sur;
    signed int sundo1;
    char pAname[100];
    char pBname[100];
    int sscoreA;
    int sscoreB;
    long int stotal_seconds;
    int scount;
    int scountA;
    int scountB;
    int snl;
    char turnplayer;
    char mode;
}save_game_expert;

//struct to save information of stored game and load it back
save_game_beginner info_of_gameb;
save_game_expert info_of_gamee;


typedef struct{
    char name[100];
    int score;
}playe_r;

playe_r playerA;
playe_r playerB;
playe_r top_ten[10];


typedef struct{
    int minutes;
    int seconds;
}time_hms;
time_hms splited_time;

FILE *Top ;
//files for saved game beginner
FILE *saveb1;
FILE *saveb2;
FILE *saveb3;

//files to save info for each saved beginner game
FILE *infob1;
FILE *infob2;
FILE *infob3;

//files for saved game expert
FILE *savee1;
FILE *savee2;
FILE *savee3;

//files to save info for each saved expert game
FILE *infoe1;
FILE *infoe2;
FILE *infoe3;

//file to save top ten beginners and experts
FILE *topb;
FILE *tope;



void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


time_hms split_time(long long total_seconds){
    time_hms splited_time;
    long int remainder_1;
    splited_time.minutes = total_seconds / 60;
    remainder_1 = total_seconds % 60;
    splited_time.seconds = remainder_1;
    return splited_time;
}


void validation (int n,int m,char game[n][m]){
    int r1, r2 ,c1 ,c2;
    int flag=0;
    while(1){
        scanf("%d %d %d %d",&r1,&r2,&c1,&c2);
        fflush(stdin);
        for(i=1;i<n;i=i+2){
            for(j=1;j<m;j=j+2){
                if(r1==i||r2==i||c1==j||c2==j){
                    flag=1;
                    break;
                }
            }
        }
        if(r1>=n||r2>=n||c1>=m||c2>=m){
          printf("Invalid move\n");
          printf("Player%c:",player);
        }
        else if(r1<0||r2<0||c1<0||c2<0)
        {
                printf("Invalid move\n");
                printf("Player%c:",player);
        }

        else if(flag==1){
            printf("Invalid move\n");
            printf("Player%c:",player);
            flag=0;
        }
        else if(r1==r2){
            if(c2>c1){
                if((c2-c1)==2&&game[r1][c2-1]==' ') {
                game[r1][c2-1]=45;
                check=45;
                count++;
                x=r1; y=c2-1;
                undo_redo[ur].X=x;
                undo_redo[ur].Y=y;
                undo_redo[ur].line=45;
                if(player=='A'){
                    countA++;
                    undo_redo[ur].colour='r';
                    undo_redo[ur].p='A';
                }
                else{
                    countB++;
                    undo_redo[ur].colour='b';
                    undo_redo[ur].p='B';
                }
                ur++;
                undo1=ur-1;
                break;
                }
                else{
                    printf("Invalid move\n");
                    printf("Player%c:",player);
                }
            }
            else if (c1>c2){
                if((c1-c2)==2&&game[r1][c1-1]==' ') {
                game[r1][c1-1]=45;
                count++;
                check=45;
                x=r1; y=c1-1;
                undo_redo[ur].X=x;
                undo_redo[ur].Y=y;
                undo_redo[ur].line=45;
                if(player=='A'){
                    countA++;
                    undo_redo[ur].colour='r';
                    undo_redo[ur].p='A';
                }
                else{
                    countB++;
                    undo_redo[ur].colour='b';
                    undo_redo[ur].p='B';
                }
                ur++;
                undo1=ur-1;
                break;
                }
                else{
                    printf("Invalid move\n");
                    printf("Player%c:",player);
                }
            }
            else{
                printf("Invalid move\n");
                    printf("Player%c:",player);
            }
        }
        else if (c1==c2){
               if(r2>r1){
                if((r2-r1)==2&&game[r2-1][c2]==' ') {
                game[r2-1][c2]=124;
                count++;
                check=124;
                x=r2-1; y=c2;
                undo_redo[ur].X=x;
                undo_redo[ur].Y=y;
                undo_redo[ur].line=124;
                if(player=='A'){
                    countA++;
                    undo_redo[ur].colour='r';
                    undo_redo[ur].p='A';
                }
                else{
                    countB++;
                    undo_redo[ur].colour='b';
                    undo_redo[ur].p='B';
                }
                ur++;
                undo1=ur-1;
                break;}
                else{
                     printf("Invalid move\n");
                    printf("Player%c:",player);
                }
            }
            else if(r1>r2){
                if(r1-r2==2&&game[r1-1][c2]==' ') {
                game[r1-1][c2]=124;
                count++;
                check=124;
                x=r1-1; y=c2;
                undo_redo[ur].X=x;
                undo_redo[ur].Y=y;
                undo_redo[ur].line=124;
                if(player=='A'){
                    countA++;
                    undo_redo[ur].colour='r';
                    undo_redo[ur].p='A';
                }
                else{
                    countB++;
                    undo_redo[ur].colour='b';
                    undo_redo[ur].p='B';
                }
                ur++;
                undo1=ur-1;
                break;}
                else{
                     printf("Invalid move\n");
                    printf("Player%c:",player);

                }
            }
            else{
                 printf("Invalid move\n");
                    printf("Player%c:",player);

            }

        }
        else {
            printf("Invalid Move\n");
            printf("Player%c:",player);
        }
    }
    }


void print_array (int n,int m,char game[n][m]){
    if(be=='b'){
        printf("  01234\n");
    }
    else if(be=='e'){
        printf("  012345678910\n");
    }
        for(i=0;i<n;i++){
            if(i==10){
                printf("%d",i);
            }
            else{printf("%d ",i);}
            for(j=0;j<m;j++){
                    if(game[i][j]=='A'){
                        SetColor(4);
                        printf("%c",game[i][j]);
                        SetColor(15);
                    }
                    else if(game[i][j]=='B'){
                        SetColor(1);
                        printf("%c",game[i][j]);
                        SetColor(15);
                    }
                    else if(game[i][j]==45||game[i][j]==124){
                        for(k=0;k<ur;k++){
                            if(undo_redo[k].X==i&&undo_redo[k].Y==j){
                                if(undo_redo[k].colour=='r'){
                                    SetColor(4);
                                    printf("%c",game[i][j]);
                                    SetColor(15);
                                    break;
                                }
                                else if(undo_redo[k].colour=='b'){
                                    SetColor(1);
                                    printf("%c",game[i][j]);
                                    SetColor(15);
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        printf("%c",game[i][j]);
                    }
            }
            if(i==0){
                printf("\t scoreA=%d \t scoreB=%d ",playerA.score,playerB.score);
            }
            else if(i==1){
                printf("\t Number of remaining lines %d",nl-count);
            }
            else if(i==2){
                printf("\t Number of moves of playerA: %d",countA);
            }
            else if(i==3){
                printf("\t Number of moves of playerB: %d",countB);
            }
            else if(i==4){
                current_time = GetTickCount();
                total_seconds = (current_time - begin_time+sstotal_seconds)/1000;
                time_hms splited_time;
                splited_time = split_time(total_seconds);
                printf("\t passed time = %d:%d", splited_time.minutes, splited_time.seconds);
            }
            printf("\n");
        }
    }


void check_moveh(int x,int y,char game[n][m]){
        if(x==0){
            if(game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124){
                game[x+1][y]=player ;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                  }
                }

            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }

        }
        else if(x==n-1){
            if(game[x-1][y-1]==124 && game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x-1][y]=player;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
        else{
            if(game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124&&game[x-1][y-1]==124&&game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x+1][y]=player ;
                game[x-1][y]=player;
                if(player=='A'){
                    playerA.score=playerA.score+2;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score=playerB.score+2;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else if (game[x-1][y-1]==124&&game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x-1][y]=player;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else if (game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124){
                game[x+1][y]=player ;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
    }


void check_movev(int x,int y,char game[n][m]){
        if(y==0){
            if(game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45){
                game[x][y+1]=player ;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }

        }
        else if(y==n-1){
            if(game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y-1]=player;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
        else{
            if(game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45&&game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y+1]=player ;
                game[x][y-1]=player;
                if(player=='A'){
                    playerA.score=playerA.score+2;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score=playerB.score+2;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else if (game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45){
                game[x][y+1]=player ;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else if (game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y-1]=player;
                if(player=='A'){
                    playerA.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='r';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='r';
                    }
                  }
                }
                else{
                    playerB.score++;
                    for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        undo_redo[k].colour='b';
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        undo_redo[k].colour='b';
                    }
                  }
                }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
    }


void check_movehundo(int x,int y,char game[n][m]){
        if(x==0){
            if(game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124){
                game[x+1][y]=' ' ;
                if(player=='A'){
                    playerA.score--;

                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }


            }
           else{ if (player=='A'){
                        player='B';
                    }
                    else{
                        player='A';
                    }
           }
        }
        else if(x==n-1){
            if(game[x-1][y-1]==124 && game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x-1][y]=' ';
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else{
                if (player=='A'){
                        player='B';
                    }
                    else{
                        player='A';
                    }
            }

        }
        else{
            if(game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124&&game[x-1][y-1]==124&&game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x+1][y]=' ' ;
                game[x-1][y]=' ';
                if(player=='A'){
                    playerA.score=playerA.score-2;
                }
                else{
                    playerB.score=playerB.score-2;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else if (game[x-1][y-1]==124&&game[x-1][y+1]==124&&game[x-2][y]==45){
                game[x-1][y]=' ';
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else if (game[x+1][y-1]==124&&game[x+2][y]==45&&game[x+1][y+1]==124){
                game[x+1][y]=' ' ;
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+2&&undo_redo[k].Y==y){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else{
                if (player=='A'){
                        player='B';
                    }
                    else{
                        player='A';
                    }
            }
        }
    }


void check_movevundo(int x,int y,char game[n][m]){
        if(y==0){
            if(game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45){
                game[x][y+1]=' ' ;
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }

        }
        else if(y==n-1){
            if(game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y-1]=' ';
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
        else{
            if(game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45&&game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y+1]=' ' ;
                game[x][y-1]=' ';
                if(player=='A'){
                    playerA.score=playerA.score-2;
                }
                else{
                    playerB.score=playerB.score-2;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else if (game[x-1][y+1]==45&&game[x][y+2]==124&&game[x+1][y+1]==45){
                game[x][y+1]=' ' ;
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y+2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y+1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else if (game[x-1][y-1]==45 && game[x+1][y-1]==45&&game[x][y-2]==124){
                game[x][y-1]=' ';
                if(player=='A'){
                    playerA.score--;
                }
                else{
                    playerB.score--;
                }
                for(k=0;k<ur;k++){
                    if(undo_redo[k].X==x-1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x+1&&undo_redo[k].Y==y-1){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                    else if(undo_redo[k].X==x&&undo_redo[k].Y==y-2){
                        if (undo_redo[k].p=='A'){
                            undo_redo[k].colour='r';
                        }
                        else if(undo_redo[k].p=='B'){
                            undo_redo[k].colour='b';
                        }
                    }
                  }
            }
            else{
                if (player=='A'){
                    player='B';
                }
                else{
                    player='A';
                }
            }
        }
    }


void undo(emove undo_redo[100],char game[n][m]){
     if(undo_redo[undo1].line==45){
        check_movehundo(undo_redo[undo1].X,undo_redo[undo1].Y,game);
     }
     else if(undo_redo[undo1].line==124){
        check_movevundo(undo_redo[undo1].X,undo_redo[undo1].Y,game);
     }
     if(player=='A'){
        countA--;
     }
     else if(player=='B'){
        countB--;
     }
     count--;
     game[undo_redo[undo1].X][undo_redo[undo1].Y]=' ';
     undo1--;
     print_array(n ,m ,game);

 }


void redo(emove undo_redo[100],char game[n][m]){
     undo1++;
     game[undo_redo[undo1].X][undo_redo[undo1].Y]=undo_redo[undo1].line;
     if(player=='A'){
        countA++;
     }
     else if(player=='B'){
        countB++;
     }
     if(undo_redo[undo1].line==45){
        check_moveh(undo_redo[undo1].X,undo_redo[undo1].Y,game);
     }
     else if(undo_redo[undo1].line==124){
        check_movev(undo_redo[undo1].X,undo_redo[undo1].Y,game);
     }
     count++;
     print_array(n ,m ,game);
 }


void validationcomp(char game[n][m]){
     srand(time(0));
     if(be=='b'){
     xc=rand()% 5;
     yc=rand()% 5;
     }
     else if(be=='e'){
        xc=rand()% 11;
        yc=rand() %11;
     }

     while(game[xc][yc]!=' '||(xc%2!=0&&yc%2!=0)){
         if(be=='b'){
              xc=rand()% 5;
              yc=rand()% 5;
             }
           else if(be=='e'){
              xc=rand()% 11;
              yc=rand() %11;
              }
     }
        if(game[xc+1][yc]=='.'){
            game[xc][yc]=124;
            count++;
            check=124;
            countB++;
            undo_redo[ur].X=xc;   undo_redo[ur].Y=yc;  undo_redo[ur].line=124;  undo_redo[ur].colour='b';
            undo_redo[ur].p='B';
            ur++;
            undo1=ur-1;

          }
        else if(game[xc][yc+1]=='.'){
            game[xc][yc]=45;
            count++;
            check=45;
            countB++;
            undo_redo[ur].X=xc;   undo_redo[ur].Y=yc;  undo_redo[ur].line=45;  undo_redo[ur].colour='b';
            undo_redo[ur].p='B';
            ur++;
            undo1=ur-1;

        }

 }


void save_game(char game[n][m]){
    printf("To save game in game 1 enter '1' , game 2 enter '2' , game 3 enter '3' ");
    scanf("%d",&gameno);
        if(be=='b'){
            //store info in struct
               for(i=0;i<5;i++){
                  for(j=0;j<5;j++){
                    info_of_gameb.sgame[i][j]=game[i][j];
                      }
                    }
                info_of_gameb.sur=ur;
                info_of_gameb.sundo1=undo1;
                info_of_gameb.scount=count;
                info_of_gameb.sscoreA=playerA.score;
                info_of_gameb.sscoreB=playerB.score;
                info_of_gameb.scountA=countA;
                info_of_gameb.scountB=countB;
                info_of_gameb.snl=nl;
                info_of_gameb.turnplayer=player;
                strcpy(info_of_gameb.pAname,playerA.name);
                strcpy(info_of_gameb.pBname,playerB.name);
                current_time = GetTickCount();
                info_of_gameb.stotal_seconds=current_time-begin_time;
                info_of_gameb.mode=one_two;

           if(gameno==1){
                //store struct undo_redo
              saveb1= fopen("saveb1.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, saveb1);
              fclose(saveb1);
                //store info of game
              infob1=fopen("infob1.txt","wb");
              fwrite(&info_of_gameb,sizeof(save_game_beginner),1,infob1);
              fclose(infob1);
                }
           else if(gameno==2){
                //store struct undo_redo
              saveb2= fopen("saveb2.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, saveb2);
              fclose(saveb2);
                //store info of game
              infob2=fopen("infob2.txt","wb");
              fwrite(&info_of_gameb,sizeof(save_game_beginner),1,infob2);
              fclose(infob2);
                }
           else if(gameno==3){
                //store struct undo_redo
              saveb3= fopen("saveb3.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, saveb3);
              fclose(saveb3);
                //store info of game
              infob3=fopen("infob3.txt","wb");
              fwrite(&info_of_gameb,sizeof(save_game_beginner),1,infob3);
              fclose(infob3);
                }
            }
        else if(be=='e'){
                //store info in struct
               for(i=0;i<5;i++){
                  for(j=0;j<5;j++){
                    info_of_gamee.sgame[i][j]=game[i][j];
                      }
                    }
                info_of_gamee.sur=ur;
                info_of_gamee.sundo1=undo1;
                info_of_gamee.scount=count;
                info_of_gamee.sscoreA=playerA.score;
                info_of_gamee.sscoreB=playerB.score;
                info_of_gamee.scountA=countA;
                info_of_gamee.scountB=countB;
                info_of_gamee.snl=nl;
                info_of_gamee.turnplayer=player;
                strcpy(info_of_gamee.pAname,playerA.name);
                strcpy(info_of_gamee.pBname,playerB.name);
                current_time = GetTickCount();
                info_of_gamee.stotal_seconds=current_time-begin_time;
                info_of_gamee.mode=one_two;

            if(gameno==1){
                //store struct undo_redo
              savee1= fopen("savee1.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, savee1);
              fclose(saveb1);
                //store info of game
              infoe1=fopen("infoe1.txt","wb");
              fwrite(&info_of_gamee,sizeof(save_game_expert),1,infoe1);
              fclose(infoe1);
                }
            else if(gameno==2){
                //store struct undo_redo
              savee2= fopen("savee2.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, savee2);
              fclose(savee2);
                //store info of game
              infoe2=fopen("infoe2.txt","wb");
              fwrite(&info_of_gamee,sizeof(save_game_expert),1,infoe2);
              fclose(infoe2);
                }
            else if(gameno==3){
                //store struct undo_redo
              savee3= fopen("savee3.txt","wb");
              fwrite(undo_redo, sizeof(undo_redo), 1, savee3);
              fclose(savee3);
                //store info of game
              infoe3=fopen("infoe3.txt","wb");
              fwrite(&info_of_gamee,sizeof(save_game_expert),1,infoe3);
              fclose(infoe3);
                }
            }

   return 0;

 }


void load_game(char game[n][m],char be,int gameno){
         if(be=='b'){
            if(gameno==1){
                    //load array of struct undo_redo
                saveb1 = fopen("saveb1.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, saveb1);
                fclose(saveb1);

                    //load struct info of game
                infob1=fopen("infob1.txt","rb");
                fread(&info_of_gameb,sizeof(save_game_beginner),1,infob1);
                fclose(infob1);
            }
            else if(gameno==2){
                    //load array of struct undo_redo
                saveb2 = fopen("saveb2.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, saveb2);
                fclose(saveb2);

                    //load struct info of game
                infob2=fopen("infob2.txt","rb");
                fread(&info_of_gameb,sizeof(save_game_beginner),1,infob2);
                fclose(infob2);
            }
            else if(gameno==3){
                    //load array of struct undo_redo
                saveb3 = fopen("saveb3.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, saveb3);
                fclose(saveb3);

                    //load struct info of game
                infob3=fopen("infob3.txt","rb");
                fread(&info_of_gameb,sizeof(save_game_beginner),1,infob3);
                fclose(infob3);

            }
            for(i=0;i<5;i++){
                for(j=0;j<5;j++){
                    game[i][j]=info_of_gameb.sgame[i][j];
                }
            }
            n=5;m=5;
            one_two=info_of_gameb.mode;
            count=info_of_gameb.scount;
            countA=info_of_gameb.scountA;
            countB=info_of_gameb.scountB;
            nl=info_of_gameb.snl;
            playerA.score=info_of_gameb.sscoreA;
            playerB.score=info_of_gameb.sscoreB;
            sstotal_seconds=info_of_gameb.stotal_seconds;
            undo1=info_of_gameb.sundo1;
            ur=info_of_gameb.sur;
            player=info_of_gameb.turnplayer;
            strcpy(playerA.name,info_of_gameb.pAname);
            strcpy(playerB.name,info_of_gameb.pBname);
            print_array(n,m,game);

         }
         else if(be=='e'){
            if(gameno==1){
                    //load array of struct undo_redo
                savee1 = fopen("savee1.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, savee1);
                fclose(savee1);

                    //load struct info of game
                infoe1=fopen("infoe1.txt","rb");
                fread(&info_of_gamee,sizeof(save_game_expert),1,infoe1);
                fclose(infoe1);
            }
            else if(gameno==2){
                    //load array of struct undo_redo
                savee2 = fopen("savee2.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, savee2);
                fclose(savee2);

                    //load struct info of game
                infoe2=fopen("infoe2.txt","rb");
                fread(&info_of_gamee,sizeof(save_game_expert),1,infoe2);
                fclose(infoe2);
            }
            else if(gameno==3){
                    //load array of struct undo_redo
                savee3 = fopen("savee3.txt", "rb");
                fread(undo_redo, sizeof(undo_redo), 1, savee3);
                fclose(savee3);

                    //load struct info of game
                infoe3=fopen("infoe3.txt","rb");
                fread(&info_of_gamee,sizeof(save_game_expert),1,infoe3);
                fclose(infoe3);
            }

            n=11;m=11;
            one_two=info_of_gamee.mode;
            count=info_of_gamee.scount;
            countA=info_of_gamee.scountA;
            countB=info_of_gamee.scountB;
            nl=info_of_gamee.snl;
            playerA.score=info_of_gamee.sscoreA;
            playerB.score=info_of_gamee.sscoreB;
            sstotal_seconds=info_of_gamee.stotal_seconds;
            undo1=info_of_gamee.sundo1;
            ur=info_of_gamee.sur;
            player=info_of_gamee.turnplayer;
            strcpy(playerA.name,info_of_gamee.pAname);
            strcpy(playerB.name,info_of_gamee.pBname);
            print_array(n,m,game);

         }
}


void top_tens(char be){
         if(be=='b'){
                topb = fopen("topb.txt", "rb");
                fread(top_ten, sizeof(top_ten), 1, topb);
                fclose(topb);
                print_topten(top_ten);
          }
          else if(be=='e'){
                tope = fopen("tope.txt", "rb");
                fread(top_ten, sizeof(top_ten), 1, tope);
                fclose(tope);
                print_topten(top_ten);
          }
}


void print_topten(playe_r top_ten[10]){
    for(i=9;i>=0;i--){
                    printf("%s \t %d \n",top_ten[i].name,top_ten[i].score);
                }
}


void find_topten(char winner[100],int score,char be){
    int flag=0;
    if(be=='b'){
                topb = fopen("topb.txt", "rb");
                fread(top_ten, sizeof(top_ten), 1, topb);
                fclose(topb);
          }
    else if(be=='e'){
                tope = fopen("tope.txt", "rb");
                fread(top_ten, sizeof(top_ten), 1, tope);
                fclose(tope);
          }

    for(i=0;i<10;i++){
            if(flag==0){
        if(strcasecmp(winner,top_ten[i].name)==0){
                flag=1;
            if(score>top_ten[i].score){
                top_ten[i].score=score;
                sort_topten(top_ten);
                }
            }
        }
        else{break;}
    }

    if(flag==0){
        if(score>top_ten[9].score){
            top_ten[9].score=score;
            strcpy(top_ten[9].name,winner);
            sort_topten(top_ten);
        }
        else{
            sort_topten(top_ten);
        }

    }

    if(be=='b'){
                topb = fopen("topb.txt", "wb");
                fwrite(top_ten, sizeof(top_ten), 1, topb);
                fclose(topb);
          }
    else if(be=='e'){
                tope = fopen("tope.txt", "wb");
                fwrite(top_ten, sizeof(top_ten), 1, tope);
                fclose(tope);
          }

    print_topten(top_ten);

}


void sort_topten(playe_r top_ten[10]){
    for(i=0;i<10;i++){
        for(j=0;j<9-i;j++){
            if(top_ten[j].score>top_ten[j+1].score){
                swap(top_ten,j,j+1);
            }
        }
    }


}

void swap(playe_r top_ten[10],int a ,int b){
    int temps;
    char tempc[100];
    temps=top_ten[a].score;
    strcpy(tempc,top_ten[a].name);

    top_ten[a].score=top_ten[b].score;
    strcpy(top_ten[a].name,top_ten[b].name);

    top_ten[b].score=temps;
    strcpy(top_ten[b].name,tempc);

}



void game_loop(char game[n][m]){
     while(count<nl){
    if(one_two=='2'){
  // human vs human
        if(player=='A'){
            while (1){
                    printf("Enter 'u' for undo or 'r' for redo or 'm' for move or 's' for save or 'e' for exit \n");
                    scanf(" %c",&unre);
            if (unre=='u'){
                    if(undo1==-1){
                        printf("Invalid Move \n");
                    }
                    else{
                //undo
                        undo(undo_redo, game);
                        break;
                    }
            }
            else if(unre=='r'){
                    if(undo1==ur-1){
                        printf("Invalid Move\n");
                    }
                    else {
                   //redo
                        redo( undo_redo, game);
                        break;
                    }
            }
            else if (unre=='m'){
                    //move then move
                    printf("PlayerA:");
        if(undo1==ur-1){
            validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
              }
            }
            else if(undo1<ur-1){
                ur=undo1+1;
                validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
               }
             }
            break;
            }
            else if (unre=='s'){
               //save
               save_game(game);
               return 0;

            }
            else if(unre=='e'){
                return 0;
            }
            else{
                printf("Invalid Move\n");
            }
            }
        }
        if(player=='B'){
            while (1){
                    printf("Enter 'u' for undo or 'r' for redo or 'm' for move or 's' for save or 'e' for exit \n");
                    scanf(" %c",&unre);
            if (unre=='u'){
                if(undo1==-1){
                        printf("Invalid Move \n");
                    }
                    else{
                //undo
                        undo(undo_redo, game);
                        break;
                    }
            }
            else if(unre=='r'){
                if(undo1==ur-1){
                        printf("Invalid Move\n");
                    }
                    else {
                   //redo
                        redo( undo_redo, game);
                        break;
                    }
            }
            else if (unre=='m'){
                    printf("PlayerB:");
        if(undo1==ur-1){
            validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
              }
            }
        else if(undo1<ur-1){
                ur=undo1+1;
                validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
               }
        }
            break;
            }
            else if(unre=='s'){
                //save
                save_game(game);
                return 0;
            }
            else if(unre=='e'){
                return 0;
            }
            else{
                printf("Invalid Move\n");
            }
            }
        }
    }
    else if (one_two=='1'){
// human vs computer
       if(player=='A'){
            while (1){
                    printf("Enter 'u' for undo or 'r' for redo or 'm' for move or 's' for save or 'e' for exit \n");
                    scanf(" %c",&unre);
            if (unre=='u'){
                if(undo1==-1){
                        printf("Invalid Move \n");
                    }
                else{
                //undo
                        undo(undo_redo, game);
                        break;
                    }
            }
            else if(unre=='r'){
                if(undo1==ur-1){
                        printf("Invalid Move\n");
                    }
                else {
                   //redo
                        redo( undo_redo, game);
                        break;
                    }
            }
            else if (unre=='m'){
                    //move then move
            printf("PlayerA:");
          if(undo1==ur-1){
            validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
              }
            }
            else if(undo1<ur-1){
                ur=undo1+1;
                validation( n, m, game);
            if(check==45){
              check_moveh( x, y,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( x, y, game);
              print_array ( n, m, game);
               }
             }
            break;
            }
            else if (unre=='s'){
               //save
               save_game(game);
               return 0;
            }
            else if(unre=='e'){
                return 0;
            }
            else{
                printf("Invalid Move\n");
            }
            }
        }
        if(player=='B'){
            while (1){
                    printf("Enter 'u' for undo or 'r' for redo or 'm' for move or 's' for save or 'e' for exit \n");
                    scanf(" %c",&unre);
            if (unre=='u'){
                if(undo1==-1){
                        printf("Invalid Move \n");
                    }
                    else{
                //undo
                        undo(undo_redo, game);
                        break;
                    }
            }
            else if(unre=='r'){
                if(undo1==ur-1){
                        printf("Invalid Move\n");
                    }
                    else {
                   //redo
                        redo( undo_redo, game);
                        break;
                    }
            }
            else if (unre=='m'){
                    printf("computer's turn\n");
        if(undo1==ur-1){
            validationcomp(game);
            if(check==45){
              check_moveh( xc, yc,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( xc, yc, game);
              print_array ( n, m, game);
              }
            }
        else if(undo1<ur-1){
                ur=undo1+1;
                validationcomp(game);
            if(check==45){
              check_moveh( xc, yc,game);
              print_array ( n, m, game);
            }
            else if(check==124){
              check_movev( xc, yc, game);
              print_array ( n, m, game);
               }
        }
            break;
            }
            else if(unre=='s'){
               //save
               save_game(game);
               return 0;
            }
            else if(unre=='e'){
                return 0;
            }
            else{
                printf("Invalid Move\n");
            }
            }
        }
        }
      }
      //winner
    if(playerA.score>playerB.score){
        printf("The Winner is %s\n",playerA.name);
        find_topten(playerA.name,playerA.score,be);
    }
    else if(playerB.score>playerA.score){
        if (one_two=='1'){
            printf("Computer is the winner ");
        }
        else if (one_two=='2'){
           printf("The Winner is %s\n",playerB.name);
           find_topten(playerB.name,playerB.score,be);
        }
    }
    else{
        printf("Tie\n");
    }


}


int main()
{
// interface ask for new game or exit or top 10
    printf("Enter 'N' for New Game \n");
    printf("Enter 'x' for Exit\n");
    printf("Enter 'L' for loading a previous game\n");
    printf("Enter 'T' for Top 10 menu\n");
    scanf("%c",&newg_ex_t10);

//New game
    if(newg_ex_t10=='N'){

    playerA.score=0;
    playerB.score=0;

    //ask for beginner or expert and check validation
    while (1){
             printf("Enter 'b' for beginner,Enter 'e' for expert:");
             scanf(" %c",&be);
    if(be=='b'){
        n=5;  m=5;  nl=12;
        break;
    }
    else if (be=='e'){
        n=11;  m=11;  nl=60;
        break;
    }
    else{
        printf("Invalid Input\n");
    }
    }

    // ask for human vs computer or human vs human and check validation
    while (1){
            printf("Enter '1' for human vs computer or '2' for human vs human: ");
            scanf(" %c",&one_two);
    if(one_two=='1'){
        break;
    }
    else if (one_two=='2'){
        break;
    }
    else{
        printf("Invalid Input\n");
    }
    }
// name for each player
  if (one_two=='2'){
    scanf("%c",&extra);
    printf("Enter name of playerA: ");
    gets(playerA.name);
    printf("Enter name of playerB: ");
    gets(playerB.name);
  }
  else if(one_two=='1'){
        scanf("%c",&extra);
    printf("Enter name of playerA: ");
    gets(playerA.name);
    printf("PlayerB is the computer\n");
  }

// storing the time when the game is started
    begin_time = GetTickCount();

//setting the game
    char game[n][m];
    for (i=0;i<n;i++){
        for(j=0;j<m;j++){
            game[i][j]=' ';
        }
    }
    for (i=0;i<n;i=i+2){
        for(j=0;j<m;j=j+2){
            game[i][j]='.';
        }
    }
    print_array(n,m,game);

// notes about the game
    printf("Enter the move as row1 row2 column1 column2\n");

    player ='A';

// game loop
 game_loop(game);

    }
    else if(newg_ex_t10=='L'){
        printf("Beginner 'b' or Expert 'e' \n");
         scanf(" %c",&be);

         printf("Enter '1' for game1 , '2' for game2 , '3' for game3 \n");
         scanf("%d",&gameno);

         if(be=='b'){
            n=5;m=5;
         }
         else if(be=='e'){
            n=11;m=11;
         }
         char game[n][m];
          begin_time = GetTickCount();
          load_game(game, be, gameno);

//game loop
          game_loop(game);


    }
    else if(newg_ex_t10=='x'){
        return 0;
    }
    else if(newg_ex_t10=='T'){
        //still
        printf("Top ten menu for beginner enter 'b' for expert enter 'e' \n");
        scanf(" %c",&be);
        top_tens(be);

    }




    return 0;
}
