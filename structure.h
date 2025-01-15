#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <time.h>

#define MAX_CASE 8

#define DUREE_JEU 600

#define CHECK_MALLOC(ptr) \
        { \
            if(ptr == NULL) \
            { \
                fprintf(stderr, "L'allocation de " #ptr " a echouer\n"); \
                exit(1); \
            } \
        } \



enum piece { VIDE, PION, TOUR, CAVALIER, FOU, REINE, ROI };
typedef enum piece Piece;

enum couleur {BLANC, NOIR };
typedef enum couleur Couleur;

struct position{
    Piece p;
    Couleur c;
};
typedef struct position Position;

struct coup{
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
};
typedef struct coup Coup;

struct coup_enregistre
{
	Piece piece;
	Coup coup;
	int prise;
	int grandRoque;
	int petitRoque;
	Piece promotion;
	int echec;
	int mat;
	struct coup_enregistre *suivant;
};
typedef struct coup_enregistre CoupEnregistre;

struct joueur{	
	int xRoi;
	int yRoi;
	int echec;
	int mat;
	int score;	
	double timer;	
};	
typedef struct joueur Joueur;	

struct partie{
    Position **plateau;
    Couleur player;
	CoupEnregistre *fiche_partie;
	CoupEnregistre *dernier_coup_joue;
	Joueur Blanc;	
	Joueur Noir;		
	long debut_coup;
};
typedef struct partie Partie;

#endif
