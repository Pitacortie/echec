#ifndef MAIN_H
#define MAIN_H


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

struct partie{
    Position **plateau;
    Couleur player;
};
typedef struct partie Partie;

struct fiche
{
	Piece piece;
	Coup coup;
	int prise;
	struct fiche *suivant;
};
typedef struct fiche Fiche;

Fiche *creer_maillon();

Position **creer_plateau();

char piece2char(Position case_courante);

void affichage(Partie *partie);

Coup proposition_joueur();

int *king();

int verif_vert(Partie *current, Coup c);

int verif_hor(Partie *current, Coup c);

int verif_diag(Partie *current, Coup c);

int verif_pion(Partie *current, Coup c);

int verif_tour(Partie *current, Coup c);

int verif_reine(Partie *current, Coup c);

int verif_cav(Partie *current, Coup c);

int verif_roi(Partie *current, Coup c);

int verif_coup(Partie *current, Coup c);

int est_echec(Partie *current, int x, int y, Couleur c, Coup *ech);

int est_col(int v1_x, int v1_y, int v2_x, int v2_y);

int **trajectoire(Coup c);

int est_mat(Partie *current, int *k, Coup *ech);

int jouer_coup(Partie *current, Coup c, int *k, Coup *ech);

void prom(Partie *current);

void feuille_partie(Fiche *premier_tour);

void pvp_play();

#endif
