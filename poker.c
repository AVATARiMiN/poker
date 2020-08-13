#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//定数//
#define MAX 52  //枚数//
#define HAND 5  //手札//
#define TYPE 13 //種類//

void set (int deck[],char mark[]){
    int i,j;
    for (i=0; i<4; i++){
        for (j=0; j<TYPE; j++){
            deck[i*TYPE+j]=j+1;
            if (i==0){
                mark[i*TYPE+j]='S';
            }else if (i==1){
                mark[i*TYPE+j]='H';
            }else if (i==2){
                mark[i*TYPE+j]='D';
            }else {
                mark[i*TYPE+j]='C';
            }
        }
    }
}

void shuffle (int deck[],char mark[]){
    int i,j,tmp_i;
    char tmp_c;

    srand((unsigned)time(NULL));

    for (i=0; i<MAX; i++){

        j=rand()%MAX;

        tmp_i=deck[i];
        deck[i]=deck[j];
        deck[j]=tmp_i;

        tmp_c=mark[i];
        mark[i]=mark[j];
        mark[j]=tmp_c;

    }
}

void show (int deck[], char mark[]){
    int i;

    for (i=0; i<HAND; i++){
        printf("%c:",mark[i]);
        printf("%d  ",deck[i]);
    }
    printf("\n");
}

void change (int deck[],char mark[]){
    int ary[5]={0,0,0,0,0};
    int i,cnt=0;
    printf("choose changing card:");

    for (i=0; i<HAND; i++){
        scanf("%d",&ary[i]);
        if (ary[i]!=0){
            cnt++;
        }else{
            break;
        }
    }

    for (i=0; i<cnt; i++){
        deck[ary[i]-1]=deck[i+5];
        mark[ary[i]-1]=mark[i+5];
    }
}

void sort (int deck[],char mark[]){
    int i,j,tmp;
    char x;
    
    for (i=0; i<5; i++){
        for (j=i+1; j<5; j++){
            if (deck[i]>deck[j]){
                tmp=deck[i];
                deck[i]=deck[j];
                deck[j]=tmp;

                x=mark[i];
                mark[i]=mark[j];
                mark[j]=x;
            }
        }
    }
    for(i=0; i<5; i++){
        if (deck[0]==1){
            tmp=deck[0];
            x=mark[0];
            for (j=0; j<4; j++){
                deck[j]=deck[j+1];
                mark[j]=mark[j+1];
            }
            deck[4]=tmp;
            mark[4]=x;
        }
    }
}

void check(int deck[],char mark[]){
    int rf=0,sf=0,fc=0,fh=0,fl=0,st=0,tc=0,tp=0,op=0;
    int i;
    
    //フラッシュ系//
    if ((mark[0]==mark[1])&&(mark[2]==mark[3])&&(mark[4]==mark[0])&&(mark[1]==mark[2])){
         if((deck[0]==deck[1]-1)&&(deck[2]-2==deck[3]-3)&&(deck[4]-4==deck[0])&&(deck[1]==deck[2])){
            sf=1;
        }else if((deck[0]==10)&&(deck[1]==11)&&(deck[2]==12)&&(deck[3]==13)&&(deck[4]==1)){
            rf=1;
        }else{
            fl=1;
        }
    }
    //ストレート//
    if ((deck[0]==deck[1]-1)&&(deck[0]==deck[2]-2)&&(deck[0]==deck[3]-3)&&(deck[0]==deck[4]-4)){
        st=1;
    }else if((deck[0]==10)&&(deck[1]==11)&&(deck[2]==12)&&(deck[3]==13)&&(deck[4]==1)){
        st=1;
    }
    //フォーカード//
    if (((deck[0]==deck[1])&&(deck[2]==deck[3])&&(deck[1]==deck[2]))||((deck[1]==deck[2])&&(deck[3]==deck[4])&&(deck[2]==deck[3]))){
        fc=1;
    }
    //フルハウス、スリーカード//
    if ((deck[0]==deck[1])&&(deck[1]==deck[2])){
        if(deck[3]==deck[4]){
            fh=1;
        }else{
            tc=1;
        }
    }
    if ((deck[2]==deck[3])&&(deck[3]==deck[4])){
        if (deck[0]==deck[1]){
            fh=1;
        }else{
            tc=1;
        }
    }
    if ((deck[1]==deck[2])&&(deck[2]==deck[3])){
        tc=1;
    }
    //ペア//
    if (((deck[0]==deck[1])&&(deck[2]==deck[3])) || ((deck[1]==deck[2])&&(deck[3]==deck[4])) || ((deck[0]==deck[1])&&(deck[3]==deck[4]))){
        tp=1;
    }
    for(i=0; i<4; i++){
        if (deck[i]==deck[i+1]){
            op=1;
        }
    }

    
    printf("***********************\n       ");

    if (rf==1){
        printf("Royal Flush");
    }else if(sf==1){
        printf("Straight Flush");
    }else if(fc==1){
        printf("Four Card");
    }else if(fh==1){
        printf("Full House");
    }else if (fl==1){
        printf("Flush");
    }else if (st==1){
        printf("Straight");
    }else if (tc==1){
        printf("Three Card");
    }else if (tp==1){
        printf("Two Pair");
    }else if (op==1){
        printf("One Pair");
    }else{
        printf("No Pair");
    }

    printf("\n***********************");
}

int main(void){
    int deck[MAX];
    char mark[MAX];
    int a=1;

    while (a==1){

        set(deck,mark);
        shuffle(deck,mark);
        sort(deck,mark);
        show(deck,mark);
        change(deck,mark);
        sort(deck,mark);
        show(deck,mark);
        check(deck,mark);

        printf("\nContinue:1\nQuit:0\n---->");
        scanf("%d",&a);

    }
  
    return 0;
}