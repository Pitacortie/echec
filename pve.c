#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"
#include "verif.h"
#include "init.h"


struct possible{
    int v;
    Coup c;
    struct possible *suivant;
};
typedef struct possible Possible;

Possible *creer_possible(){
    Possible *res = malloc(sizeof(Possible));
    res->suivant = NULL;
    return res;
}

void afficher_possible(Possible *p){
    while(p->suivant != NULL){
        printf("%d %d\n", p->c.xFrom, p->c.yFrom);
        p = p->suivant;
    }
}

Possible *max_chain(Possible *p){
    int max = p->v;
    Possible *res = p;
    while(p != NULL){
        if(p->v > max){
            max = p->v;
            res = p;
        }
    p = p->suivant;
    }
    return res;
}


void end_possible(Possible *p){
    Possible *temp;
    while(p != NULL){
        temp = p->suivant;
        free(p);
        p = temp;
    }
}


int trad_verif_coup(Partie current, Coup c){
    int verif = verif_coup(&current, c, 0);
    if(verif == 0){
        if(current.plateau[c.xTo][c.yTo].p != VIDE)
            return 2;
        else
            return 1;
    }
    else if(verif == 6)
        return 3;

    return 0;
    
}

int nb_coup(Partie current, int x, int y, Possible *l){
    Coup temp = {x, y, 0, 0};
    Possible *suiv;
    int res = 0;
    for(int x_bis = 0; x_bis < MAX_CASE; x_bis++){
        for(int y_bis = 0;y_bis < MAX_CASE; y_bis++){
            temp.xTo = x_bis;
            temp.yTo = y_bis;
            if(trad_verif_coup(current, temp) != 0){
                suiv = creer_possible();
                l->suivant = suiv;
                l->c = temp;
                l->v = 0;
                l = l->suivant;
                res++;
        }
        }
    }
    return res;
}

int den_coup(Partie current, Possible *l){
    int res = 0;
    Possible *temp;
    for(int x = 0; x < MAX_CASE; x++){
        for(int y = 0; y < MAX_CASE; y++){
            if(current.plateau[x][y].c == current.player){
                res += nb_coup(current, x, y, l);
            }
            
        }
    }
    return res;
}



int main(){
    Partie current = creer_partie();
    Possible *l = creer_possible();
    Possible *begin = l;
    printf("%d\n", den_coup(current, l));
    afficher_possible(l);
}
