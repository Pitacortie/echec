#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"

int main(){
    char res;
    printf("Bienvenue sur le jeu d'echec de Maeline Duparc et Noah GAVARD\n");
    printf("Les regles sont simples, un jeux d'echec classique\n");
    printf("Les blancs commencent, le plateau se retourne a chaque tour\n");
    printf("Pour jouer, vous devez rentrer les coordonees en majuscule\n");
    printf("Pour commencez appuyer sur entree\n");
    scanf("%c", &res);
    play_pvp();

    return 0;
}
