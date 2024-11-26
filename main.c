k#include <stdio.h>
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

void affichage(Partie *partie)
{
    plat = partie->plate
    if (partie->player == BLANC)
    {
        printf("C'est aux blancs de jouer.\n Veillez entrer un coup.\n");
    }
    else
    {
        printf("C'est aux noirs de jouer.\n Veillez entrer un coup.\n");
    }
    printf("+-+-+-+-+-+-+-+-+");
    for (int i = 0, i < 8, i++)
    {
        for (int j = 0, j < 8, j++)
        {
            if (plat[i][j]->c == BLANC)
            {
                int maj = 0;
            }
            else
            {
                int maj = 32;
            }
            printf("|");
            switch (case_actuelle->p)
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
}


