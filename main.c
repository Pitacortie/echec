#include <stdio.h>
#include <stdlib.h>

enum piece { VIDE, PION, TOUR, CAVALIER, FOU, REINE, ROI };
typedef enum piece Piece;

enum couleur { BLANC, NOIR };
typedef enum couleur Couleur;

struct place{
    Piece p;
    Couleur c;
};
typedef struct place Place;

struct coup{
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
};
typedef struct coup Coup;

struct partie{
    Place **plate;
    Couleur player;
};
typedef struct partie Partie;


Place **creer_plateau(){
    Place **tab = malloc(sizeof(tab) * 8);
    for(int i = 0; i < 8; i++)
        *(tab + i) = malloc(sizeof(Place));

    for(int i = 0; i < 8; i++){
        tab[1][i].p = PION;
        tab[1][i].c = BLANC;
        tab[6][i].p = PION;
        tab[6][i].c = NOIR;
    }
    Piece temp = 1;
    for(int j = 0; j < 8; j++){
        tab[0][j].p = temp;
        tab[0][j].c = BLANC;
        tab[0][j].p = temp;
        tab[0][j].c = NOIR;
        if(j < 5)
            temp ++;
        else
            temp --;
     
    }

    return tab;
}


void affichage(Partie *partie)
{
    Place **plateau = partie->plate;
    int maj;
    if (partie->player == BLANC)
    {
        printf("C'est aux blancs de jouer.\n Veillez entrer un coup.\n");
    }
    else
    {
        printf("C'est aux noirs de jouer.\n Veillez entrer un coup.\n");
    }
    printf("+-+-+-+-+-+-+-+-+");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (plateau[i][j].c == BLANC)
            {
                 maj = 0;
            }
            else
            {
                 maj = 32;
            }
            printf("|");
            switch (plateau[i][j].p)
            {
                case VIDE :
                    printf(" ");
                
                case PION: 
                    printf("%c", 80 + maj);
                
                case TOUR: 
                    printf("%c", 82 + maj);
                    
                case CAVALIER:
                    printf("%c", 78 + maj);
                    
                case FOU: 
                    printf("%c", 66 + maj);
                
                case REINE:
                    printf("%c", 81 + maj);
                
                case ROI:
                    printf("%c", 75 + maj);
            }
            //passage a la case suivante 
        }
        printf("|");
    }
    printf("+-+-+-+-+-+-+-+-+");
}


int main(){
    Partie teste;
    teste.plate = creer_plateau();
    printf("ok");
    affichage(&teste);
    for(int i = 0; i < 8; i++)
        free(*(teste.plate) + i);
    free(teste.plate);
    return 1;

}
