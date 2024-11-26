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

