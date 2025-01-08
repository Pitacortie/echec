#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"


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
                        if(verif_coup(&current, temp, 1) == 0 || verif_coup(&current, temp, 1) == 6){
                            suiv = creer_possible();
                            l->v = 0;
                            l->c = temp;
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

int val_possible(Partie current, Coup c, int n, int res){
    int tab[200] = {0};
    int i = 0;
    Coup temp;
    if(n >= 5){
        return res;
    }
    else{
        jouer_coup(&current, c);
        for(int x = 0; x < MAX_CASE; x++){
            for(int y = 0; y < MAX_CASE; y++){
                if(current.plateau[x][y].p != VIDE && current.plateau[x][y].c == NOIR){
                    for(int x_bis = 0; x_bis < MAX_CASE; x_bis++){
                        for(int y_bis = 0; y_bis < MAX_CASE; y_bis++){
                            temp.xFrom = x;
                            temp.yFrom = y;
                            temp.xTo = x_bis;
                            temp.yTo = y_bis;
                            int verif = trad_verif_coup(current, temp);
                            switch(verif){
                                case 1:
                                    tab[i] = res + 1;
                                    i++;
                                    res = val_possible(current, temp, n+1, res);
                                break;
                                case 2:
                                    if(current.plateau[c.xFrom][c.yFrom].c == NOIR)
                                        tab[i] = res + 2;
                                    else
                                        tab[i] = res - 2;
                                    i++;
                                    res = val_possible(current, temp, n+1, res);
                                break;
                                case 3:
                                    if(current.Noir.echec == 1){
                                        if(current.Noir.mat == 1)
                                            tab[i] = res -100;
                                        else
                                            tab[i] = res - 10;
                                    }
                                    else{
                                        if(current.Blanc.mat == 1)
                                            tab[i] = res + 100;
                                        else    
                                            tab[i] = res + 10;
                                    }
                                    i++;
                                    res = val_possible(current, temp, n+1, res);
                                break;

                            }

                            
                        }
                    }
                }
            }
        return max_tab(tab);
        }
    }
}


int main(){
    Partie test =creer_partie();
    Possible *list = creer_possible();
    Possible *begin = list;
    int den = den_coup(test, list);
    for(int i = 0; i < den - 1; i++){
        list->v = val_possible(test, list->c, 0, 0);
        list = list->suivant;

    }
    printf("%d\n", max_chain(begin)->v);
    printf("%d\n", max_chain(begin)->c.xFrom);
    printf("%d\n", max_chain(begin)->c.yFrom);
    printf("%d\n", max_chain(begin)->c.xTo);
    printf("%d\n", max_chain(begin)->c.yTo);
    return 0;
}