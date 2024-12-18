#include <stdlib.h>
#include <stdio.h>
#include "main.h"

struct possible{
    int v;
    int n;
    Coup c;
    struct possible *suivant;
};
typedef struct possible Possible;

Possible *creer_possible(){
    Possible *res = malloc(sizeof(Possible));
    res->suivant = NULL;
    return res;
}

Possible *max(Possible *p){
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

void end(Possible *p){
    Possible *temp;
    while(p != NULL){
        temp = p->suivant;
        free(p);
        p = temp;
    }
}


int a_jouer(Partie current, int n, int res, Possible l){
    if(n ==3){
        
    }

}

int main(){
    return 0;
}
