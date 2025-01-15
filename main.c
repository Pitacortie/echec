#include <stdlib.h>
#include <stdio.h>
#include "pvp.h"

int main(){
    char res;
    int charge;
    printf("Bienvenue sur le jeu d'echec de Maeline Duparc et Noah GAVARD\n");
    printf("Les regles sont simples, un jeux d'echec classique\n");
    printf("Les blancs commencent, le plateau se retourne a chaque tour\n");
    printf("Pour jouer, vous devez rentrer les coordonees en majuscule\n");
    printf("Pour commencez appuyer sur entree\n");
    scanf("%c", &res);
    printf("Que voulez vous faire ?\n");
    printf("1 - Nouvelle partie\n");
    printf("2 - Charger la derniere partie jouer\n");
    scanf("%d", &charge);
    while ((getchar()) != '\n');
    play_pvp(charge);
    return 0;
}
