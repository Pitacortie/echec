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


int den_coup(Partie current, Possible *l){
    int res = 0;
    Possible *suiv;
    Coup temp;
    for(int x = 0; x < MAX_CASE; x++){
        for(int y = 0; y < MAX_CASE; y++){
            if(current.plateau[x][y].p != VIDE && current.plateau[x][y].c == NOIR){
                for(int x_bis = 0; x_bis < MAX_CASE; x_bis++){
                    for(int y_bis = 0; y_bis < MAX_CASE; y_bis++){
                        temp.xFrom = x;
                        temp.yFrom = y;
                        temp.xTo = x_bis;
                        temp.yTo = y_bis;
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

int max_tab(int *tab){
    int i = 0;
    int max = tab[0];
    while(tab[i] != 0){
        if(tab[i] > max)
            max = tab[i];
        i++;
    }
    return max;
}

int val_possible(Partie current, Coup c, int *tab, int n, int *k, Fiche *partie, int res, int i){
    Coup *ech;
    Coup temp;
    if(n >= 2){
        return max_tab(tab);
    }
    else{
        jouer_coup(&current, c, k, ech, partie);
        for(int x = 0; x < MAX_CASE; x++){
            for(int y = 0; y < MAX_CASE; y++){
                if(current.plateau[x][y].p != VIDE && current.plateau[x][y].c == NOIR){
                    for(int x_bis = 0; x_bis < MAX_CASE; x_bis++){
                        for(int y_bis = 0; y_bis < MAX_CASE; y_bis++){
                            printf("%d\n", i);
                            temp.xFrom = x;
                            temp.yFrom = y;
                            temp.xTo = x_bis;
                            temp.yTo = y_bis;
                            int verif = verif_coup(&current, temp);
                            switch(verif){
                                case 0:
                                    tab[i] = 0;
                                break;
                                default:
                                    if(verif == 1)
                                        tab[i] = res + 1;
                                    if(verif == 2)
                                        tab[i] = res + 2;
                                    if(est_echec(&current, k[0], k[1], NOIR, ech))
                                        tab[i] = res + 10;
                                    if(est_echec(&current, k[2], k[3], BLANC, ech))
                                        tab[i] = res - 10;
                                    printf("ok\n");
                                    if(est_echec(&current, k[2], k[3], BLANC, ech) && est_mat(&current, k, ech) == 1){
                                        printf("ok2\n");
                                        if(current.plateau[ech->xFrom][ech->yFrom].c == BLANC){
                                            tab[i] = res - 100;
                                        }                              
                                        else{
                                            tab[i] = res + 100;
                                        }
                                    }
                                break;
                            }
                            i++;

                            res = val_possible(current,temp, tab, n+1, k, partie, tab[i], i);
                        }
                    }
                }
            }
        return max_tab(tab);
        }
    }
}


int main(){
    Partie test;
    int *k = king();
    Fiche *p = creer_maillon();
    test.plateau = creer_plateau();
    Possible *list = creer_possible();
    Possible *begin = list;
    int den = den_coup(test, list);
    int tab[20000] = {0};
    for(int i = 0; i < den - 1; i++){
        list->v = val_possible(test, list->c, tab, 0, k, p, 0, 0);
        list = list->suivant;
    }
    printf("%d\n", max_chain(begin)->v);
    return 0;
}
