#ifndef VERIF_H
#define VERIF_H

#include "structure.h"
#include "init.h"


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

#endif
