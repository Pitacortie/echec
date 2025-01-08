#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"

int main(){
    //Le PVE n'a pas encore été codé, ce fichier permet juste d'executer le pvp, il est donc provisoire
    int res;
    printf("Bienvenu sur le Jeux d'echec de Maeline Duparc et Noah GAVARD, pour commencer, choississez votre mode de Jeux.\n");
    printf("1 - PVP, Jouez avec contre un ami\n");
    printf("2 - PVE, Affrontez un ordinateur\n");
    scanf("%d", &res);
    while ((getchar()) != '\n');
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