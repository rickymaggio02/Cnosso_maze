#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 128

void home(){
    FILE *f;
    f=fopen("home.txt", "r");
    if(f==NULL){
        printf("errore nell'apertura del file");
        return;
    }
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),f) != NULL)
        printf("%s",read_string);
    fclose(f);
}


void enemyImage(int n){
    FILE *f;
    if(n==1){
        f=fopen("./monsters/centaurs.txt", "r");
    }
    if(n==2){
        f=fopen("./monsters/centaur2.txt", "r");
    }
    if(n==3){
        f=fopen("./monsters/devil1.txt", "r");
    }
    if(n==4){
        f=fopen("./monsters/devil2.txt", "r");
    }
    if(n==5){
        f=fopen("./monsters/dragon.txt", "r");
    }
    if(n==6){
        f=fopen("./monsters/dragon2.txt", "r");
    }
    if(n==7){
        f=fopen("./monsters/gryphon.txt", "r");
    }
    if(n==8){
        f=fopen("./monsters/mermaid.txt", "r");
    }
    if(n==9){
        f=fopen("./monsters/minotaur.txt", "r");
    }
    if(n==10){
        f=fopen("./monsters/pegasus.txt", "r");
    }
    if(n==11){
        f=fopen("./monsters/reaper.txt", "r");
    }

    if(f==NULL){
        printf("errore nell'apertura del file");
        return;
    }

    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),f) != NULL)
        printf("%s",read_string);

    fclose(f);
}

void bossImage(int n){
    FILE *f;
    if(n==1){
        f=fopen("./monsters/boss1.txt", "r");
    }
    if(n==2){
        f=fopen("./monsters/Final_BOSS.txt", "r");
    }
    
    if(f==NULL){
        printf("errore nell'apertura del file");
        return;
    }

    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),f) != NULL)
        printf("%s",read_string);

    fclose(f);
}

