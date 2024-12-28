#ifndef MAIN_H
#define MAIN_H


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
	clock_t debut_coup;
};
typedef struct partie Partie;

/******************************************************************************
 * Nom de fonction : creer_partie
 *
 * Description : Création une partie dans l'état initial
 *
 * - Initialiser le plateau dans l'état initial
 * - Initialiser les données du joueur des blancs (position du roi, pas d'echec, pas de mat)
 * - Initialiser les données du joueur des noirs (position du roi, pas d'echec, pas de mat)
 * - Initialise le joueur courant au joueur des blancs
 * - Initialise la fiche de partie à vide
 * - Retourner la partie initialisée
 *
 * Paramètres d'entrée : Aucun
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Partie               La partie initialisée
 ******************************************************************************/
Partie creer_partie();

/******************************************************************************
 * Nom de fonction : liberer_partie
 *
 * Description : Libère l'espace mémoire pris par la partie
 *
 * - Libération de l'espace mémoire occupé par le plateau
 * - Libération de l'espace mémoire occupé par la fiche de partie 
 *
 * Paramètres d'entrée :
 * Paramètre   Type        E/S   Description
 * ---------   ---------   ---   ----------------------------------------------
 * partie     Partie       E/S   La partie en cours dont les différents 
 *								 pointeurs doivent être libérés 
 * 
 * Paramètres de retour : Aucun 
 ******************************************************************************/
void liberer_partie(Partie partie);

/******************************************************************************
 * Nom de fonction : liberer_fiche
 *
 * Description : Libère récursivement l'espace mémoire pris par les coups 
 *               enregistrés de la fiche de match
 *
 * Paramètres d'entrée :
 * Paramètre   Type          E/S   Description
 * ---------   ---------     ---   ----------------------------------------------
 * coup_efface CoupEnregistre E   Le coup à libérer 
 * 
 * Paramètres de retour : Aucun 
 ******************************************************************************/
 void liberer_fiche(CoupEnregistre *coup_efface);

/******************************************************************************
 * Nom de fonction : creer_plateau
 *
 * Description : Création du plateau dans l'état initial
 *
 * - Allouer la mémoire nécessaire pour un tableau 8x8
 * - Initialiser les cases VIDE du plateau
 * - Placer les pions noirs et blancs sur le plateau
 * - Placer les 5 premières pièces majeures Tour, Cavalier, Fou, Dame et Roi
 * - Placer les 3 dernières pièces majeures Fou, Cavalier, Tour
 * - Retourner le plateau initialisé
 *
 * Paramètres d'entrée : Aucun
 *
 * Paramètres de retour : 
 * Type                  Description
 * --------------------- -----------------------------------------------
 * Tableau de positions  Tableau qui contient les informations de toutes
                         les pièces du plateau en début de partie
 ******************************************************************************/
Position **creer_plateau();

/******************************************************************************
 * Nom de fonction : piece2char
 *
 * Description : Transforme une structure Position en sa représentation sur le 
 *               plateau sous forme d'un caractère.
 *               Minuscule = noir, Majuscule = blanc
 *               P:Pion, R:Tour, N:Cavalier, B:Fou, Q:Dame, K:Roi
 *               espace: case vide
 *
 * - Retourner le caractère correspondant à la position
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * case_courante  Position     E    La case à traduire
 * 
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
  char                  caractère correspondant à la pièce à afficher
 ******************************************************************************/
char piece2char(Position case_courante);

/******************************************************************************
 * Nom de fonction : afficher_plateau
 *
 * Description : Afficher le plateau de jeu en le positionnant face au joueur
 *               Le plateau tourne lorsque le joueur change
 *               Les cases blanches et noires sont visibles 
 *
 * - Si joueur blanc
 *   - Afficher le plateau avec la case A1 en bas à gauche
 * - Sinon
 *   - Afficher le plateau avec la case A1 en haut à droite 
 * - Fin Si
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur)
 * 
 * Paramètres de retour : aucun
 ******************************************************************************/
void afficher_plateau(Partie *partie);

/******************************************************************************
 * Nom de fonction : creer_coup_enregistre
 *
 * Description : Créer un pointeur de coup enregistré vide
 *
 * - Allouer la mémoire nécessaire pour un nouveau coup enregistré
 * - Definir le coup enregistré suivant à null
 * - Renvoyer le coup enregistré
 *
 * Paramètres d'entrée : Aucun
 * 
 * Paramètres de retour : Aucun 
 ******************************************************************************/
CoupEnregistre *creer_coup_enregistre();

/******************************************************************************
 * Nom de fonction : afficher_fiche_partie
 *
 * Description : Affiche les coups enregistrés de la partie
 *
 *  La notation utilisée est la notation algébrique française.
 *  Les coups sont indiqués par une lettre majuscule indiquant la pièce qui bouge 
 *  suivi de la case d’arrivée de la pièce. On utilise les lettres R pour Roi, 
 *  D pour Dame, T pour Tour, F pour Fou et C pour Cavalier. Les coups de pions 
 *  sont indiqués uniquement par la case d’arrivée, sans aucune lettre majuscule.
 *
 *  La prise est indiquée par un x entre le nom de la pièce et la case d’arrivée. 
 *  Comme il n’y a pas de lettre dans le cas du pion, on indique sa colonne de départ 
 *  en minuscule. Lorsque deux pièces identiques peuvent aller sur la même case, 
 *  on indique après le nom de la pièce la colonne d’origine si celle-ci est 
 *  différente, ou la rangée d’origine si la colonne est la même.
 *   
 *  Un échec est indiqué par le symbole + après la case d’arrivée, un mat par le symbole #.
 *  Le petit roque est indiqué par le symbole O-O, le grand roque par O-O-O.
 *  La promotion est indiqué par le nom de la pièce dans laquelle le pion est promu 
 *  après l’indication de la case d’arrivée.
 *
 *  Le résultat de la partie est noté 1 – 0, 1/2 – 1/2 ou 0 – 1 pour, respectivement, 
 *  une victoire des Blancs, un match nul ou une victoire des Noirs.
 *
 * - Controle si des coup ont été joué
 * - Affiche en tete des colonnes des coups
 * - Tant qu'il reste un coup à afficher
 *   - Affiche O-O-O pour le grand roque si besoin
 *   - Affiche O-O pour le petit roque si besoin
 *   - Affiche la pièce qui joue
 *   - Affiche X si le coup est une prise 
 *   - Affiche la case d'arrivée
 *   - Affiche la promotion si besoin
 *   - Affiche # si le coup génère un échec et mat
 *   - Affiche + si le coup génère un échec
 *   - Affiche un retour à la ligne si l'on a écrit le coup noir
 *   - Passe au coup suivant
 * - Fin Tant que
 *
 * Paramètres d'entrée :
 * Paramètre     Type                 E/S  Description
 * ---------     ------------------   ---  ----------------------------------------------
 * fiche_partie  CoupEnregistre ptr    E   Pointeur sur le premier coup de la 
 *                                         liste des coups de la partie.
 * 
 * Paramètres de retour : Aucun 
 ******************************************************************************/
void afficher_fiche_partie(CoupEnregistre *fiche_partie, Partie partie);

/******************************************************************************
 * Nom de fonction : maj_score
 *
 * Description : Mettre à jour le score d'un joueur 
 *
 * En cas d'égalité (absence d'échec et mat), une façon de déterminer le vainqueur 
 * est par le score.
 * Chaque pièce possède une valeur : 
 * Pion : 1 point, Cavalier : 3 points, Fou : 3 points 
 * Tour : 5 points et Reine : 9 points
 
 * - Identifier le joueur dont il faut changer le score
 * - Modifier le score en fonction de la valeur de la pièce prise
 *
 * Paramètres d'entrée :
 *
 * Paramètre     Type                 E/S  Description
 * ---------     ------------------   ---  ----------------------------------------------
 * fiche_partie  CoupEnregistre ptr    E   Pointeur sur le premier coup de la 
 * 
 * Paramètres de retour : Aucun 
 ******************************************************************************/
void maj_score(Partie *partie, Piece piece_prise);

/******************************************************************************
 * Nom de fonction : proposition_joueur
 *
 * Description : Demande au joueur le coup qu'il souhaite jouer
 *
 * - Demander la position de la pièce à jouer
 * - Demander la position de destination de la pièce
 * - Retourne le coup du joueur
 *
 * Paramètres d'entrée : Aucun
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Coup                 Le coup que souhaite jouer le joueur
 ******************************************************************************/
 Coup proposition_joueur();
 
/******************************************************************************
 * Nom de fonction : verif_diag
 *
 * Description : Vérifie que le coup proposé est valide pour un déplacement en 
 *               diagonale
 *
 * - Verifier que le déplacement est bien une diagonale
 * - Verifier que les cases de la diagonale sont vide
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      11 : Le coup n'est pas un mouvement en diagonale
 *                      12 : Une autre pièce se trouve sur la diagonale
 ******************************************************************************/
int verif_diag(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_vert
 *
 * Description : Vérifie que le coup proposé est valide pour un déplacement en 
 *               verticale
 *
 * - Verifier que le déplacement est bien une verticale
 * - Verifier que les cases de la verticale sont vide
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         *Partie      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      21 : Le coup n'est pas un mouvement en verticale
 *                      22 : Une autre pièce se trouve sur la verticale
 ******************************************************************************/
int verif_vert(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_hor
 *
 * Description : Vérifie que le coup proposé est valide pour un déplacement en 
 *               horizontale
 *
 * - Verifier que le déplacement est bien une horizontale
 * - Verifier que les cases de la horizontale sont vide
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      31 : Le coup n'est pas un mouvement en horizontale
 *                      32 : Une pièce se trouve sur l'horizontale
 ******************************************************************************/
int verif_hor(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_pion
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement d'un 
 *               pion. 
 *
 * - Verifier que le déplacement correspond à une verticale
 * - Verifier que le déplacement correspond à une diagonale
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         *Partie      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      41 : Le mouvement ne correspond pas au déplacement d'un pion
 *                      42 : La destination du mouvement sans prise est occupee
 ******************************************************************************/
 int verif_pion(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_tour
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement de 
 *               la tour.
 *
 * - Verifier que le déplacement correspond à une verticale ou une horizontale
 * - Verifier que le déplacement n'est pas bloquée par une autre pièce
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         *Partie      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      51 : Le mouvement ne correspond pas au déplacement d'une tour
 *                      52 : Une pièce bloque le déplacement
 ******************************************************************************/
int verif_tour(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_cav
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement d'un cavalier.
 *
 * - Verifier que le déplacement correspond à celui d'un cavalier
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      61 : Le mouvement ne correspond pas au déplacement d'un cavalier
******************************************************************************/
int verif_cav(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_reine
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement de 
 *               la dame.
 *
 * - Verifier que le déplacement correspond à une verticale, horizontale ou une diagonale
 * - Verifier que le déplacement n'est pas bloquée par une pièce
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      71 : Le mouvement ne correspond pas au déplacement d'une dame
 *                      72 : Une pièce bloque le déplacement
******************************************************************************/
int verif_reine(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_roi
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement du 
 *               roi. 
 *
 *   - Verifier si le déplacement correspond à un roque
 *   - Verifier si le déplacement correspond à un grand roque
 *   - Verifier si le déplacement correspond à un petit roque
 *   - Vérifier si le déplacement correspond à un déplacement simple (1 case)
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      81 : Le mouvement ne correspond pas au déplacement du roi
 *                      82 : La position du roi ne permet pas le roque
 *                      83 : Le roque est impossible
 ******************************************************************************/
int verif_roi(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : verif_coup
 *
 * Description : Vérifie que le coup proposé est valide
 *
 * - Vérifier que la position de départ est bien une position valide
 * - Vérifier que la position d'arrivée est bien une position valide
 * - Vérifier que la position de départ contient une pièce du joueur
 * - Vérifier que la position d'arrivée ne contient pas une pièce du joueur
 * - Vérifier que le mouvement de la pièce est valide
 * - Vérifier que le mouvement n'entraine pas une situation d'échec
 * - Retourner l'état de la vérification
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 * controle_echec int          E    Faut il tester si le déplacement génère un échec (1 oui, 0 non) 
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le coup est valide
 *                      1 : La position de départ n'est pas dans les limites de l'échiquier
 *                      2 : La position d'arrivée n'est pas dans les limites de l'échiquier
 *                      3 : La case de départ ne contient pas une pièce du joueur
 *                      4 : La case d'arrivée contient une pièce du joueur
 *                      5 : Le déplacement n'est pas conforme à la piece ou une pièce se trouve sur le trajet
 *                      6 : Le mouvement entraîne une situation d'échec 
 ******************************************************************************/
 int verif_coup(Partie *partie, Coup coup, int controle_echec);

/******************************************************************************
 * Nom de fonction : est_col
 *
 * Description : Vérifie si les deux vecteurs de coordonnées respectives
 * (v1_x ; v1_y) et (v2_x ; v2_y) sont bien colinéaires
 *
 * - Vérifier que les deux vecteurs sont colinéaires en calculant 
 *   le produit vectoriel et en vérifiant qu'il est nul.
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * v1_x           int          E    Coordonnées horizontale du vecteur 1
 * v1_y           int          E    Coordonnées verticale du vecteur 1
 * v2_x           int          E    Coordonnées horizontale du vecteur 2
 * v2_y           int          E    Coordonnées verticale du vecteur 2
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la colinéarité des deux vecteurs
 *                      0 : Les deux vecteurs ne sont pas colinéaires
 *                      1 : Les deux vecteurs sont colinéaires
 ******************************************************************************/
int est_col(int v1_x, int v1_y, int v2_x, int v2_y);

/******************************************************************************
 * Nom de fonction : trajectoire
 *
 * Description : Crée un tableau contenant les coordonnées de toutes les cases 
 * parcourues par la pièce lors de son déplacement.
 *
 * - Calculer la norme du vecteur directeur du déplacement
 * - Allouer la mémoire nécessaire aux tableaux contenant les coordonnées 
 *   des cases situées sur la trajectoire de la pièce
 * - Parcourir les cases du plateau
 * - Ajouter les cases de la trajectoire au plateau
 * - Retourner le tableau contenant les coordonnées des cases parcourues par la pièce lors de son déplacement
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * tableau d'entiers    Tableau contenant les coordonnées des cases 
 *                      empruntées par la pièce lors de son déplacement 
 ******************************************************************************/

int **trajectoire(Coup coup);

/******************************************************************************
 * Nom de fonction : est_echec
 *
 * Description : Vérifie si la case de coord x, y, et de couleur c,  est en échec
 *
 * - Vérifier si une pièce du joueur peut prendre le roi adverse
 *   (Parcours de chaque case et vérification si la pièce peut prendre le roi)
 * - Retourner l'état de la vérification
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le roi adverse n'est pas en échec
 *                      1 : Le roi adverse est en échec
 ******************************************************************************/
 int est_echec(Partie *partie);

/******************************************************************************
 * Nom de fonction : est_mat
 *
 * Description : Vérifie si le roi est en échec et mat
 *
 * - Initialiser les coordonnées du roi en échec
 * - Déplacer le roi en échec
 * - Rechercher la pièce qui met le roi en échec
 * - Vérifier si une pièce du roi en échec peut prendre la pièce qui génère l'échec
 * - Vérifier si une pièce du roi en échec peut couper la trajectoire du coup qui met le roi en échec
 * - Calculer la trajectoire de la pièce qui met en échec le roi
 * - Vérifier si une pièce du roi en échec peut couper la trajectoire de la pièce qui le met en échec
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur)
 *
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Entier               Code d'erreur de la validité du coup
 *                      0 : Le roi adverse n'est pas en échec et mat
 *                      1 : Le roi adverse est en échec et mat
 ******************************************************************************/
int est_mat(Partie *partie);

/******************************************************************************
 * Nom de fonction : jouer_coup
 *
 * Description : Déplace les pièces sur l'échiquier
 *
 * - Créer un enregistrement du coup pour la fiche de match
 * - Vérifier la prise d'une pièce pour l'affichage de la fiche de match
 * - Déplacer la pièce jouée 
 * - Sauvegarder les coordonnées des rois
 * - Promouvoir un pion
 * - Détecter si échec au roi adverse
 * - Détecter si échec et mat au roi adverse
 * - Mise à jour du temps du joueur
 * - Enregistrer le coup joué dans la fiche de partie
 * - Changer de joueur
 *  
 * Paramètres d'entrée :
 * Paramètre     Type                 E/S  Description
 * ---------     ------------------   ---  ----------------------------------------------
 * partie        *Partie              E    Pointeur sur la partie en cours
 * coup          coup                 E    Coup à jouer
 * 
 * Paramètres de retour : Aucun
 ******************************************************************************/
void jouer_coup(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : promotion_pion
 *
 * Description : Vérifie que la promotion d’un pion est possible 
 * et demande au joueur en quelle pièce le pion est promu.
 *
 * - Vérifier que la pièce est un pion sinon renvoyer la pièce
 * - Vérifier que la destination est bien une ligne de fond sinon renvoyer la pièce
 * - Demander la promotion au joueur
 * - Renvoyer la promotion
 *
 * Paramètres d'entrée :
 * Paramètre   Type        E/S   Description
 * ---------   ---------   ---   ----------------------------------------------
 * partie      Partie ptr   E    La partie en cours
 * coup        Coup         E    Le coup joué 
 * 
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Piece                La promotion du pion 
 ******************************************************************************/
Piece promotion_pion(Partie *partie, Coup coup);

/******************************************************************************
 * Nom de fonction : play_pvp
 *
 * Description : Déroulement du jeu humain contre humain
 *
 * - Créer la partie dans l'état initiale
 * - Afficher le plateau à l'état initial
 * - Demander le premier coup
 * - Tant que pas d'échec et mat
 *   - Vérifier la validité du coup
 *   - Déplacer les pièces
 *   - Afficher la fiche de partie
 *   - Afficher le plateau et le score actuel
 *   - Afficher les informations du joueur (joueur qui joue, temps restant, état échec ou erreur du coup précédent)
 *   - Lire le coup à jouer (Joueur ou tableau de test automatique)
 *  - Fin Tant que
 *  - Afficher le résultat de la partie  
 *  - Libérer l'espace mémoire utilisé par la partie
 *
 * Paramètres d'entrée : Aucun
 *
 * Paramètres de retour : Aucun 
 ******************************************************************************/
void play_pvp();

/******************************************************************************
 * Nom de fonction : main
 *
 * Description : Programme principal
 * - Lancer le jeu humain contre humain
 *
 * Paramètres d'entrée : Aucun
 * Paramètres de retour : Aucun 
 ******************************************************************************/
int main();

#endif
