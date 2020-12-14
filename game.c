#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "asciiArt.h"

typedef struct{
    int x;
    int y;
}cella;

int **load_map(int *size, const char filename[]);
//void visualize_map(int **map, int size);
void mk_maze(int r_size, int c_size, int **maze, cella c, int **support);
int **makeWall(int r_size, int c_size);
int **makeSupp(int r_size, int c_size);
int **generate_map(int size, int liv);
void save_map(int **map, int size, const char filename[]);
int action(int **map,int size, cella k, int vite);
cella maink(int **map, int size);
int controlloMuro(int map);
int controlloVincita(int map);
int controlloMostro(int map);
void visualize_map(int** map, int size, cella k, int win_size);
int battle(int vite, int mostro);
void livello(int vite, int liv);

int scelta(){
    char sn;
    scanf("%c%*c", &sn);
    if(sn=='y' || sn=='Y'){
        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    int **map;
    int *n;
    *n = 1;
    char save[30];
    int c;
    int vite=3;
    printf("\e[1;1H\e[2J");
    home();
    printf("\n \n--------------- BENVENUTO AVVENTURIERO -----------\n \n");
    printf("hai una faccia conosciuta avventuriero, sicuro di voler ricominciare un'avventura y/n\n");
    c = scelta();
    if(c==0){
        FILE *f;
        f = fopen("save.txt", "r");
        if(f==NULL){
            printf("salvataggio non esistente\n");
            fclose(f);
        }
        else{
            map = load_map(n, "save.txt");
            int m = action(map,*n, maink(map, *n), vite);
            if(m==4){
                printf("\n vuoi salvare la partita y/n?\n");
                c = scelta();
                if(c==1){
               save_map(map, *n, "save.txt");
                }
            return 0;
            }
            else if(m==0){
                return 0;
            }
            fclose(f);
        }

    }

    livello(vite, *n);
    
    return 0;

}

int **load_map(int *size, const char filename[]){
    FILE *f;
    f = fopen(filename, "r");
    if(f==NULL){
        printf("errore in apertura del salvataggio\n");
        return 0;
    }
    fscanf(f, "%d", size);
    int **map;
    int i,j;
    map = calloc(*size, sizeof(int*));
    for(i=0; i<*size; i++){
        map[i]= calloc(*size, sizeof(int));
    }
    for(i=0; i<*size; i++){
        for(j=0; j<*size; j++){
            fscanf(f,"%d",&map[i][j]);
            if(feof(f)!=0){
                break;
            }
        }
    }
    fclose(f);
    return map;
}


void visualize_map(int** map, int size, cella k, int win_size){
    int i,j;
    int w,s,a,d;
    int r1=0, r2=0, r3=0, r4=0;

    if(k.y-(win_size/2)<0){
        a=0;
        r1=-(k.y-(win_size/2));
    }
    else{
        a=k.y-(win_size/2);
    }

    if((k.y+(win_size/2))>=size){
        d=size;
        r2=(k.y+(win_size/2))-size;
    }
    else{
        d=k.y+(win_size/2);
    }

    if((k.x-(win_size/2))<0){
        w=0;
        r3=-(k.x-(win_size/2));
    }
    else{
        w=k.x-(win_size/2);
    }

    if((k.x+(win_size/2))>=size){
        s=size;
        r4=(k.x+(win_size/2))-size;
    }
    else{
        s=k.y+(win_size/2);
    }
    printf("x: %d -- y: %d\n", k.x, k.y);

    int **map2;
    map2 = calloc(win_size, sizeof(int*));
    for(i=0; i<win_size; i++){
        map2[i]= calloc(win_size, sizeof(int));
    }

    for(i=0; i<win_size; i++){
        for(j=0; j<win_size; j++){
            map2[i][j]=0;
        }
    }

    for(i=0; i<(win_size-r4-r3); i++){
        for(j=0; j<(win_size-r2-r1); j++){
            map2[i+r3][j+r1]=map[i+w][j+a];
        }
    }
 
    for(i=0; i<win_size; i++){
        for(j=0; j<win_size; j++){
            if(map2[i][j]==0){
                printf("%c", ' ');
            }

            else if(map2[i][j]==1){
                printf("%c", '#');
            }

            else if(map2[i][j]==2){
                printf("%c", 'k');
            }

            else if(map2[i][j]==3){
                printf("%c", 'o');
            }

            else if(map2[i][j]==4){
                printf("%c", 'm');
            }

            else{
                printf("p.corrotto");
            }
            }
          printf("\n");  
        }

}

int **makeWall(int r_size, int c_size){
    int **map;
    int i, j;
    map = calloc(r_size, sizeof(int*));
    for(i=0; i<r_size; i++){
        map[i]= calloc(c_size, sizeof(int));
    }

    for(i=0; i<r_size; i++){
        for(j=0; j<c_size; j++){
            map[i][j]=1;
        }
    }
    return map;

}

void mk_maze(int r_size, int c_size, int **maze, cella c, int **support){
    support[c.x][c.y]=1;
    cella new;
    int rc, rv;
    int rx, ry;

    maze[c.x][c.y]=0;
    

    int cond=1;

    if((c.x+2)<r_size){
        if(support[c.x + 2][c.y + 0]==0){
            cond =0;
            
        }
    }

    if((c.y+2)<c_size){
        if(support[c.x + 0][c.y + 2]==0){
            cond =0;
            
        }
    }

    if((c.x-2)>=0){
        if(support[c.x - 2][c.y + 0]==0){
            cond =0;
            
        }
    }

    if((c.y-2)>=0){
        if(support[c.x + 0][c.y -2]==0){
            cond = 0;
            
        }
    }


    if(cond==1){
        return;
    }

    do{
        rv = (rand() % 2);
        if(rv==0){
            rv = 2;
        }
        else if(rv==1){
            rv = -2;
        }

        rc = (rand() % 2);
        if(rc==0){
            rx = rv;
            ry = 0;
        }
        else if(rc==1){
            rx = 0;
            ry = rv;
        }
    }while((c.x + rx)<0 || (c.y + ry)<0 || (c.x + rx)>=r_size || (c.y + ry)>=c_size || support[c.x + rx][c.y + ry]==1);
    new.x = c.x + rx;
    new.y = c.y + ry;

    support[(new.x + c.x)/2][(new.y + c.y)/2]=1;
    maze[(new.x + c.x)/2][(new.y + c.y)/2]=0;
    
    mk_maze(r_size, c_size, maze, new, support);

}

int **makeSupp(int r_size, int c_size){
    int **map;
    int i, j;
    map = calloc(r_size, sizeof(int*));
    for(i=0; i<r_size; i++){
        map[i]= calloc(c_size, sizeof(int));
    }

    for(i=0; i<r_size; i++){
        for(j=0; j<c_size; j++){
            map[i][j]=0;
        }
    }
    return map;

}

int **generate_map(int size, int liv){
    int **supp;
    int **map;
    cella start;
    start.x=1;
    start.y=1;
    srand(time(NULL));
    supp = makeSupp(size, size);
    map = makeWall(size, size);
    mk_maze(size, size, map, start,supp);
    int x, y;
    do{
        x = (rand() % size);
        y = (rand() % size);

    }while((map[x][y])!=0);
    map[x][y]=2;

    do{
        x = (rand() % size);
        y = (rand() % size);

    }while((map[x][y])!=0);
    map[x][y]=3;
    int i;
    for(i=0; i<((liv/3)+1); i++){
    do{
        x = (rand() % size);
        y = (rand() % size);
    }while((map[x][y])!=0 );
    map[x][y]=4;
    }

    return map;

}

void save_map(int **map, int size, const char filename[]){
    FILE *f;
    f = fopen(filename, "w");
    fprintf(f, "%d\n", size);
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            fprintf(f, "%d ", map[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

cella maink(int **map, int size){
    int i,j;
    cella k;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(map[i][j]==2){
                k.x=i;
                k.y=j;
            }
        }

    }
    return k;
}
int controlloMuro(int map){
    if(map==1){
        printf("ouch, il muro! \n");
        return 1;
    }
    else{
        return 0;
    }
}

int controlloMostro(int map){
    if(map==4){
        return 1;
    }
    else{
        return 0;
    }
}


int controlloVincita(int map){
    if(map==3){
        printf("complimenti, sei arrivato all'uscita!!\n");
        printf("\n \n-------------------------------------\n !!!!!LIVELLO COMPLETATO!!!!!");
        return 1;
    }
    else{
        return 0;
    }
}

int action(int **map,int size, cella k, int vite){
    char scelta;
    printf("\e[1;1H\e[2J");
    visualize_map(map,size,k, 20);
    printf("scegli la tua azione: wasd per il movimento e q per uscire:\n");
    scanf("%c%*c", &scelta);
    srand(time(NULL));
    switch(scelta){
        case 'd':
            if(controlloMuro(map[k.x][k.y+1])!=1 && k.y+1<size){
                if(controlloVincita(map[k.x][k.y+1])!=1){
                    if(controlloMostro(map[k.x][k.y+1])!=1){
                    map[k.x][k.y+1]=2;
                    map[k.x][k.y]=0;
                    k.y=k.y+1;
                    }
                    else if(controlloMostro(map[k.x][k.y+1])==1){
                    int n= (rand() % 11)+1;
                    vite = battle(vite, n);
                    if(vite>0){
                        map[k.x][k.y+1]=2;
                        map[k.x][k.y]=0;
                        k.y=k.y+1;
                    }
                    else{
                        return 0;
                    }
                    }
                }
                else if(controlloVincita(map[k.x][k.y+1])==1){
                    return vite;
                }
            }
            break;
            
        case 'a':
            if(controlloMuro(map[k.x][k.y-1])!=1 && k.y-1>0){
                if(controlloVincita(map[k.x][k.y-1])!=1){
                    if(controlloMostro(map[k.x][k.y-1])!=1){

                    map[k.x][k.y-1]=2;
                    map[k.x][k.y]=0;
                    k.y=k.y-1;
                    }
                     else if(controlloMostro(map[k.x][k.y-1])==1){
                    int n= (rand() % 11)+1;
                    vite = battle(vite, n);
                    if(vite>0){
                        map[k.x][k.y-1]=2;
                        map[k.x][k.y]=0;
                        k.y=k.y-1;
                    }
                    else{
                        return 0;
                    }
                    }
                }
                else if(controlloVincita(map[k.x][k.y-1])==1){
                    return vite;
                }
            }
            break;

        case 'w':
            if(controlloMuro(map[k.x-1][k.y])!=1 && k.x-1>0){
                if(controlloVincita(map[k.x-1][k.y])!=1){
                    if(controlloMostro(map[k.x-1][k.y])!=1){
                    map[k.x-1][k.y]=2;
                    map[k.x][k.y]=0;
                    k.x=k.x-1;
                    }

                    else if(controlloMostro(map[k.x-1][k.y])==1){
                    int n= (rand() % 11)+1;
                    vite = battle(vite, n);
                    if(vite>0){
                    map[k.x-1][k.y]=2;
                    map[k.x][k.y]=0;
                    k.x=k.x-1;
                    }
                    else{
                        return 0;
                    }
                }

                }
                else if(controlloVincita(map[k.x-1][k.y])==1){
                    return vite;
                }
                
            }
            break;
        
        case 's':
            if(controlloMuro(map[k.x+1][k.y])!=1 && k.x+1>0){
                if(controlloVincita(map[k.x+1][k.y])!=1){
                    if(controlloMostro(map[k.x+1][k.y])!=1){
                    map[k.x+1][k.y]=2;
                    map[k.x][k.y]=0;
                    k.x=k.x+1;
                    }

                    else if(controlloMostro(map[k.x+1][k.y])==1){
                    int n= (rand() % 11)+1;
                    vite = battle(vite, n);
                    if(vite>0){
                        map[k.x+1][k.y]=2;
                        map[k.x][k.y]=0;
                        k.x=k.x+1;
                    }
                    else{
                        return 0;
                    }
                }


                }
                else if(controlloVincita(map[k.x+1][k.y])==1){
                    return vite;
                }
            }
            break;

        case 'q':
            return 4;
            break;
        
        default:
            printf("comando invalido\n");
            break;
    }

    action(map, size, k, vite);

}

int battle(int vite, int mostro){
    char mossa;
    int m;
    srand(time(NULL));
    if(vite<=0){
        //schermata di morte
        return vite;
    }
    printf("\e[1;1H\e[2J");
    enemyImage(mostro);
    printf("\n \n");
    printf("   vite: ");
    int i;
    for(i=0; i< vite; i++){
        printf(" <3 ");
    }
    printf("\n");
    printf(" -----------------------------------------------------------------------------------------------\n");
    printf("|                                                                                                |\n");
    printf("|                              avventuriero la tua mossa?                                        |\n");
    printf("|                                                                                                |\n");
    printf(" -----------------------------------------------------------------------------------------------\n");
    
    do{
    scanf("%c%*c", &mossa);
    switch(mossa){
        case 'c':
            m=0;
            break;
        case  'f':
            m=1;
            break;
        case 's':
            m=2;
            break;
        
        default:
            printf("\n hai a disposizione tre tipi di attacchi: c f s, e ricorda che c<f<s<c\n");

    }
    }while(m!=0 && m!=1 && m!=2);
    int n= (rand() % 3);
    if(n!=2){
        if(m>n){
            //schermata uccisione mostro
            return vite;
        }
        if(m==n){
            printf("- pareggio! uno scontro alla pari!\n");
            battle(vite,mostro);
        }
        else{
            printf("ahia, sembra che hai perso una vita");
            battle(vite-1, mostro);
        }
    }
    else if(n==2){
        if(m==0){
            //schermata uccisione mostro
            return vite;
        }
        else if(m==n){
            printf("- pareggio! uno scontro alla pari!\n");
            battle(vite,mostro);
        }
        else{
            printf("ahia, sembra che hai perso una vita");
            battle(vite-1, mostro);
        }
    }

    
}

void livello(int vite, int liv){
    if(vite==0){
        return;
    }
    else{
        int **map;
        int n = 15+(liv*2);
        map = generate_map(n, liv);
        printf("\n          livello : %d", liv);
        int m = action(map,n, maink(map, n), vite);
        if(m==4){
            printf("\n vuoi salvare la partita y/n?\n");
            char c = scelta();
            if(c==1){
               save_map(map, n, "save.txt");
            }
            return;
        }
        else{
            livello(m, liv+1);
        }
    }
    
}
