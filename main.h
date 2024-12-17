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

extern Fiche *creer_maillon();

extern Position **creer_plateau();

extern char piece2char(Position case_courante);

extern void affichage(Partie *partie);

extern Coup proposition_joueur();

extern int *king();

extern int verif_vert(Partie *current, Coup c);

extern int verif_hor(Partie *current, Coup c);

extern int verif_diag(Partie *current, Coup c);

extern int verif_pion(Partie *current, Coup c);

extern int verif_tour(Partie *current, Coup c);

extern int verif_reine(Partie *current, Coup c);

extern int verif_cav(Partie *current, Coup c);

extern int verif_roi(Partie *current, Coup c);

extern int verif_coup(Partie *current, Coup c);

extern int est_echec(Partie *current, int x, int y, Couleur c, Coup *ech);

extern int est_col(int v1_x, int v1_y, int v2_x, int v2_y);

extern int **trajectoire(Coup c);

extern int est_mat(Partie *current, int *k, Coup *ech);

extern int jouer_coup(Partie *current, Coup c, int *k, Coup *ech);

extern void prom(Partie *current);

extern void feuille_partie(Fiche *premier_tour);

#endif