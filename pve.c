#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"


struct possible{
    int v;
    Coup c;
    int *tab;
    struct possible *suivant;
};
typedef struct possible Possible;

Possible *creer_possible(){
    Possible *res = malloc(sizeof(Possible));
    res->suivant = NULL;
    return res;
}

void afficher_possible(Possible *p){
    while(p != NULL){
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

int max_tab(int *tab){
    int i = 0;
    int max = tab[0];
    while(tab[i] != 0 || tab[i] != NULL){
        if(tab[i] > max)
            max = tab[i];
        i++;
    }
    return max;
}

void end_possible(Possible *p){
    Possible *temp;
    while(p != NULL){
        temp = p->suivant;
        free(p);
        p = temp;
    }
}


int den_coup(Partie current, Possible *l){
    int res = 0;
    Possible *suiv;
    for(int x = 0; x < MAX_CASE; x++){
        for(int y = 0; y < MAX_CASE; y++){
            if(current.plateau[x][y].p != VIDE && current.plateau[x][y].c == NOIR){
                for(int x_bis = 0; x_bis < MAX_CASE; x_bis++){
                    for(int y_bis = 0; y_bis < MAX_CASE; y_bis++){
                        Coup temp = {x, y, x_bis, y_bis};
                        int tab[200] = {0};
                        if(verif_coup(&current, temp) != 0){
                            suiv = creer_possible();
                            l->v = 0;
                            l->c = temp;
                            l->tab = tab;
                            l->suivant = suiv;
                            l = l->suivant;
                            res++;
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main(){
    Partie test;
    test.plateau = creer_plateau();
    Possible *list = creer_possible();
    int den = den_coup(test, list);
    afficher_possible(list);
    printf("%d\n", den);
    return 0;
}
