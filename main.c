#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(){
    int res;
    printf("Bienvenu sur le Jeux d'echec de Maeline Duparc et Noah GAVARD, pour commencer, choississez votre mode de Jeux.\n");
    printf("1 - PVP, Jouez avec contre un ami\n");
    printf("2 - PVE, affrontez un ordinateur\n");
    scanf("%d", &res);
    if(res == 1){
        play_pvp();
    }
    else if(res == 2){
        printf("ok\n");
    }
    else
        printf("Erreur\n");

    return 0;
}