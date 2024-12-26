#ifndef MAIN_H
#define MAIN_H


#define MAX_CASE 8

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
	clock_t debut_coup;
};
typedef struct partie Partie;

Partie creer_partie();

void liberer_partie(Partie partie);

Position **creer_plateau();

char piece2char(Position case_courante);

void afficher_plateau(Partie *partie);

CoupEnregistre *creer_coup_enregistre();

void afficher_fiche_partie(CoupEnregistre *fiche_partie);

void liberer_fiche(CoupEnregistre *coup_efface);

void maj_score(Partie *etat_partie, Piece piece_prise);


Coup proposition_joueur();

int verif_vert(Partie *current, Coup c);

int verif_hor(Partie *current, Coup c);

int verif_diag(Partie *current, Coup c);

int verif_pion(Partie *current, Coup c);

int verif_tour(Partie *current, Coup c);

int verif_reine(Partie *current, Coup c);

int verif_cav(Partie *current, Coup c);

int verif_roi(Partie *current, Coup c);

int verif_coup(Partie *current, Coup c, int controle_echec);

int est_echec(Partie *current);

int est_col(int v1_x, int v1_y, int v2_x, int v2_y);

int **trajectoire(Coup c);

int est_mat(Partie *current);

void jouer_coup(Partie *current, Coup c);

Piece promotion_pion(Partie *current, Coup coup);

void play_pvp();

#endif
