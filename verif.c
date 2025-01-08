#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "verif.h"
#include "pvp.h"
#include "init.h"
#include "structure.h"



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
int verif_diag(Partie *partie, Coup coup)
{
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une diagonale
	if (abs(vect_x) != abs(vect_y))
	{
		return 11;
	}
	
	// Verifier que les cases de la diagonale sont vides
	int norme = abs(vect_x);
	int x_iter = vect_x >0?1:-1;
	int y_iter = vect_y >0?1:-1;
    for(int i = 1; i < norme ; i++)
	{ 
	    int x_test = coup.xFrom + i * x_iter;
		int y_test = coup.yFrom + i * y_iter;

		if(partie->plateau[x_test][y_test].p != VIDE)
		{
			return 12;
		}
    }
	
    return 0;
}

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
int verif_vert(Partie *partie, Coup coup)
{
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une verticale
	if(coup.yFrom != coup.yTo)
	{
		return 21;
	}
	
	// Verifier que les cases de la verticale sont vide
	int norme = abs(vect_x);
	int x_iter = vect_x >0?1:-1;
    for(int i = 1; i < norme ; i++)
	{ 
	    int x_test = coup.xFrom + i * x_iter;
		int y_test = coup.yFrom;

		if(partie->plateau[x_test][y_test].p != VIDE)
		{
			return 22;
		}
    }
			
	return 0;
}

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
int verif_hor(Partie *partie, Coup coup)
{
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une horizontale
	if(coup.xFrom != coup.xTo)
	{
		return 31;
	}
	
	// Verifier que les cases de l'horizontale sont vide
	int norme = abs(vect_y);
	int y_iter = vect_y >0?1:-1;
    for(int i = 1; i < norme ; i++)
	{ 
	    int x_test = coup.xFrom;
		int y_test = coup.yFrom + i * y_iter;

		if(partie->plateau[x_test][y_test].p != VIDE)
		{
			return 32;
		}
    }
			
	return 0;
}

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
 int verif_pion(Partie *partie, Coup coup)
{
	int vect_x = coup.xTo - coup.xFrom;
	
	int verif_v = verif_vert(partie, coup);
	int verif_d = verif_diag(partie, coup);
	
	// Verifier que le déplacement correspond à une verticale
	if (verif_vert(partie, coup) == 0)
	{
		if (partie->plateau[coup.xTo][coup.yTo].p != VIDE)
		{
			return 42;
		}
		if (vect_x == -1 && partie->player == BLANC){
			return 0;
		}
		if (vect_x == 1 && partie->player == NOIR){
			return 0;
		}
		
		if (vect_x == -2 && partie->player == BLANC && coup.xFrom == 6){
			return 0;
		}

		if (vect_x == 2 && partie->player == NOIR && coup.xFrom == 1){
			return 0;
		}		
	}

	// Verifier que le déplacement correspond à une diagonale
	if (verif_diag(partie, coup) == 0)
	{
		if (vect_x == -1 && partie->player == BLANC && partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player)
		{
			return 0;
		}
		if (vect_x == 1 && partie->player == NOIR && partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player)
		{
			return 0;
		}
	}
	
	return 41;
}

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
int verif_tour(Partie *partie, Coup coup)
{
	int verif_v = verif_vert(partie, coup);
	int verif_h = verif_hor(partie, coup);
	
	// Verifier que le déplacement correspond à une verticale ou une horizontale
	if (verif_v == 21 && verif_h == 31)
	{
		return 51;
	}
	
	// Verifier que le déplacement n'est pas bloquée par une autre pièce
	if (verif_v == 22 || verif_h == 32)
	{
		return 52;
	}
	
	return 0;
}

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
int verif_cav(Partie *partie, Coup coup)
{
	//Vérifier que le déplacement est bien conforme à celui d'un cavalier
	int dx = abs(coup.xTo - coup.xFrom); //Calcule la valeur absolue de la coordonnée en x du vecteur du coup
	int dy = abs(coup.yTo - coup.yFrom); //Calcule la valeur absolue de la coordonnée en y du vecteur du coup
	if((dx == 2 && dy == 1) || (dy == 2 && dx == 1))
	{
			return 61;
	}
	return 0;
}

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
int verif_reine(Partie *partie, Coup coup)
{
	int verif_v = verif_vert(partie, coup);
	int verif_h = verif_hor(partie, coup);
	int verif_d = verif_diag(partie, coup);
	
	// Verifier que le déplacement correspond à une verticale, horizontale ou une diagonale
	if (verif_d == 11 && verif_v == 21 && verif_h == 31 )
	{
		return 71;
	}

	// Verifier que le déplacement n'est pas bloquée par une pièce
	if (verif_d == 12 || verif_v == 22 || verif_h == 32)
	{
		return 72;
	}

	return 0;
}

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
int verif_roi(Partie *partie, Coup coup)
{
	
	int vect_x = coup.xTo - coup.xFrom;
	int vect_y = coup.yTo - coup.yFrom;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	
	// Vérifier si un roque
	if (norme == 2)
	{
		if (coup.yFrom != 4 || coup.xFrom != coup.xTo)
		{
			return 82;
		}
	
		if ((coup.xFrom != 0 && partie->player == NOIR) || (coup.xFrom != 7 && partie->player == BLANC))
		{
			return 82;
		}
		
		// Verifier Grand roque
		if (coup.yFrom > coup.yTo && partie->plateau[coup.xFrom][0].p == TOUR && partie->plateau[coup.xFrom][0].c == partie->player)
		{
			Coup coup_tour = { coup.xFrom, 0, coup.xFrom, 3 };
			Coup coup_roi = { coup.xFrom, coup.yFrom, coup.xTo, coup.yTo };
			int verif_t = verif_hor(partie, coup_tour);
			int verif_r = verif_hor(partie, coup_roi);
			if (verif_t == 0 && verif_r == 0)
			{
				return 0;
			}
		}	

		// Verifier Petit roque
		if (coup.yFrom < coup.yTo && partie->plateau[coup.xFrom][MAX_CASE-1].p == TOUR && partie->plateau[coup.xFrom][MAX_CASE-1].c == partie->player)
		{
			Coup coup_tour = { coup.xFrom, MAX_CASE-1, coup.xFrom, 5 };
			Coup coup_roi = { coup.xFrom, coup.yFrom, coup.xTo, coup.yTo };
			int verif_t = verif_hor(partie, coup_tour);
			int verif_r = verif_hor(partie, coup_roi);
			if (verif_t == 0 && verif_r == 0)
			{
				return 0;
			}
		}	
		
		return 83;
	}
	// Vérifier si un déplacement simple (1 case)
	if(norme == 1)
	{	
		return 0;
	}
	
	return 81;
}

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
 int verif_coup(Partie *partie, Coup coup, int controle_echec)
{	
    // Vérifier que la position de départ est bien une position valide
	if (coup.xFrom < 0 || coup.xFrom >= MAX_CASE || coup.yFrom < 0 || coup.yFrom >= MAX_CASE)
	{
		return 1;
	}

	// Vérifier que la position d'arrivée est bien une position valide
	if (coup.xTo < 0 || coup.xTo >= MAX_CASE || coup.yTo < 0 || coup.yTo >= MAX_CASE)
	{
		return 2;
	}

	// Vérifier que la position de départ contient une pièce du joueur
	if (partie->plateau[coup.xFrom][coup.yFrom].p != VIDE && partie->plateau[coup.xFrom][coup.yFrom].c != partie->player)
	{
		return 3;
	}
	
	// Vérifier que la position d'arrivée ne contient pas une pièce du joueur
	if (partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c == partie->player)
	{
		return 4;
	}

	// Vérifier que le mouvement de la pièce est valide
	Piece piece = partie->plateau[coup.xFrom][coup.yFrom].p;
	int verif_piece;
	switch(piece)
	{
		case PION:
			verif_piece = verif_pion(partie, coup);
			if(verif_piece != 0)
				return verif_piece;
		break;
		case TOUR:
			verif_piece = verif_tour(partie, coup);
			if(verif_piece != 0)
				return verif_piece;
		break;
		case CAVALIER:
			if(verif_cav(partie, coup) == 0)
				return 5;
		break;
		case FOU:
			verif_piece = verif_diag(partie, coup);
			if (verif_piece != 0)
				return verif_piece;
		break;
		case ROI:
			verif_piece = verif_roi(partie, coup);
			if (verif_piece != 0)
				return verif_piece;
		break;
		case REINE:
			verif_piece = verif_reine(partie, coup);
			if (verif_piece != 0)
				return verif_piece;
		break;
		case VIDE:
			return 5;
		break;
	}

	// Vérifier que le mouvement n'entraine pas une situation d'échec
	if (controle_echec == 1)
	{
		// 1- Jouer le coup
		Position destination = partie->plateau[coup.xTo][coup.yTo];
		partie->plateau[coup.xTo][coup.yTo].p = partie->plateau[coup.xFrom][coup.yFrom].p;
		partie->plateau[coup.xTo][coup.yTo].c = partie->plateau[coup.xFrom][coup.yFrom].c;
		partie->plateau[coup.xFrom][coup.yFrom].p = VIDE;
		partie->plateau[coup.xFrom][coup.yFrom].c = BLANC;
		// 2- mettre éventuellement à jour les coordonnées du roi
		if (partie->plateau[coup.xTo][coup.yTo].p == ROI)
		{
			if (partie->player == BLANC)
			{
				partie->Blanc.xRoi = coup.xTo;
				partie->Blanc.yRoi = coup.yTo;
			}
			else
			{
				partie->Noir.xRoi = coup.xTo;
				partie->Noir.yRoi = coup.yTo;			
			}
		}
		partie->player = 1-partie->player;
		
		// 3- Vérifier si le joueur est en échec
		int validite_echec = est_echec(partie);

		// 4- Annuler le coup
		partie->player = 1-partie->player;
		if (partie->plateau[coup.xTo][coup.yTo].p == ROI)
		{
			if (partie->player == BLANC)
			{
				partie->Blanc.xRoi = coup.xFrom;
				partie->Blanc.yRoi = coup.yFrom;
			}
			else
			{
				partie->Noir.xRoi = coup.xFrom;
				partie->Noir.yRoi = coup.yFrom;			
			}
		}	
		partie->plateau[coup.xFrom][coup.yFrom].p = partie->plateau[coup.xTo][coup.yTo].p;
		partie->plateau[coup.xFrom][coup.yFrom].c = partie->plateau[coup.xTo][coup.yTo].c;
		partie->plateau[coup.xTo][coup.yTo].p = destination.p;
		partie->plateau[coup.xTo][coup.yTo].c = destination.c;
		// 5- Retourner code d'erreur si echec généré par le déplacement
		if (validite_echec == 1)
		{
			return 6;
		}
	}

	// Retourner l'état de la vérification
	return 0;
}

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
int est_col(int v1_x, int v1_y, int v2_x, int v2_y)
{
	return (((v1_x * v2_y) - (v1_y * v2_x)) == 0);
}

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

int **trajectoire(Coup coup)
{
	// Calculer la norme du vecteur directeur du déplacement
	int vect_x = coup.xTo - coup.xFrom;
	int vect_y = coup.yTo - coup.yFrom;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	
	// Allouer la mémoire nécessaire au tableau contenant les coordonnées 
	// des cases situées sur la trajectoire de la pièce
	int **traj = malloc(sizeof(*traj) * norme);
	CHECK_MALLOC(traj);
	for(int i = 0; i < norme; i++)
	{
		*(traj + i) = malloc(sizeof(int) * 2);
		CHECK_MALLOC(*(traj + i));
	}
	
	// Parcourir les cases du plateau
	int traj_iter = 0;
	int min_x = vect_x > 0 ? coup.xFrom : coup.xTo;
	int max_x = vect_x > 0 ? coup.xTo : coup.xFrom;
	int min_y = vect_y > 0 ? coup.yFrom : coup.yTo;
	int max_y = vect_y > 0 ? coup.yTo : coup.yFrom;
	for(int x = min_x; x < max_x; x++)
	{
		for(int y = min_y; y < max_y; y++)
		{
			//Ajouter les cases de la trajectoire au plateau
			int vect2_x = x - coup.xFrom;
			int vect2_y = y - coup.yFrom;
			printf("trajectoire %d, %d, %d, %d\n", vect2_x, vect2_y, vect_x, vect_y);
			if(est_col(vect_x, vect_y, vect2_x, vect2_y))
			{
				traj[traj_iter][0] = x;
				traj[traj_iter][1] = y;
				traj_iter++;
			}
		}
	}
	// Retourner le tableau contenant les coordonnées des cases parcourues par la pièce lors de son déplacement
	return traj;
}


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
 int est_echec(Partie *partie){		
	//printf("Debug - Est_echec %s\n", partie->player == BLANC?"Blanc":"Noir");
	// Verifier si une pièce adverse peut prendre le roi
	Coup coup_temp;
	for(int i = 0; i < MAX_CASE; i++)
	{
		for(int j = 0; j < MAX_CASE; j++)
		{
			coup_temp.xFrom = i;
			coup_temp.yFrom = j;
			coup_temp.xTo = partie->player == BLANC?partie->Noir.xRoi:partie->Blanc.xRoi;
			coup_temp.yTo = partie->player == BLANC?partie->Noir.yRoi:partie->Blanc.yRoi;

			int validite_coup = verif_coup(partie, coup_temp, 0);
			//printf("Debug - Est_echec-Verif_coup %d%d-%d%d %d\n", coup_temp.xFrom, coup_temp.yFrom, coup_temp.xTo, coup_temp.yTo, validite_coup);
			if(validite_coup == 0 || validite_coup == 6)
			{
				return 1;
			}
		}
	}
	return 0;
}

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
int est_mat(Partie *partie){
	
	// Initialiser les coordonnées du roi en échec
	int xRoi = partie->player == BLANC?partie->Noir.xRoi:partie->Blanc.xRoi;
	int yRoi = partie->player == BLANC?partie->Noir.yRoi:partie->Blanc.yRoi;
		
	// Déplacer du roi en echec
	partie->player = 1 - partie->player;
	for(int i = -1; i < 2; i++)
	{
		for(int j = -1; j < 2; j++)
		{
			if (i!=0 || j!=0)
			{				
				Coup deplacement_roi = {xRoi, yRoi, xRoi+i, yRoi+j};
				if(verif_coup(partie, deplacement_roi, 1) == 0)
				{
					partie->player = 1 - partie->player;
					return 0;
				}
			}
		}
	}
	partie->player = 1 - partie->player;

	// Rechercher la pièce qui met le roi en échec
	for(int i = 0; i < MAX_CASE; i++)
	{
		for(int j = 0; j < MAX_CASE; j++)
		{
			// 1- Parcourir toute la grille et créer un coup entre la case balayée et la case à vérifier
			Coup coup_test;
			coup_test.xFrom = i;
			coup_test.yFrom = j;
			coup_test.xTo = xRoi;
			coup_test.yTo = yRoi;
			// 2- Si la case contient une pièce adverse au roi en échec
			if ((partie->plateau[i][j].p != VIDE) && partie->plateau[i][j].c == partie->player)
			{
				// 3- Si le coup est valide 
				if (verif_coup(partie, coup_test, 0) == 0)
				{
					// Alors la pièce adverse au roi en échec peut le prendre.
					int vect_x = coup_test.xFrom - coup_test.xTo;
					int vect_y = coup_test.yFrom - coup_test.yTo;
					int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));

					// Vérifier si une pièce du roi en echec peut prendre la pièce qui génère l'échec
					partie->player = 1 - partie->player;
					for(int k = 0; k < MAX_CASE; k++)
					{
						for(int l = 0; l < MAX_CASE;l++)
						{
							Coup coup_prise_echec = { k, l, coup_test.xFrom, coup_test.yFrom };
							if (verif_coup(partie, coup_prise_echec, 1) == 0)
							{
								partie->player = 1 - partie->player;
								return 0;
							}
						}
					}
					partie->player = 1 - partie->player;

					// Vérifier si la pièce qui met le roi en echec est un cavalier 
					if(partie->plateau[coup_test.xFrom][coup_test.yFrom].p == CAVALIER)
					{
						printf("Mat cavalier\n");
						return 1;
					}

					// Calculer la trajectoire de la pièce qui met en échec le roi
					int **traj = trajectoire(coup_test);

					// Vérifier si une pièce du roi en échec peut couper la trajectoire de la pièce qui le met en échec
					partie->player = 1 - partie->player;
					for(int traj_iter = 0; traj_iter < norme; traj_iter++)
					{						
						for(int k = 0; k < MAX_CASE; k++)
						{
							for(int l = 0; l < MAX_CASE;l++)
							{
								Coup coup_prise_echec = { k, l, traj[traj_iter][0], traj[traj_iter][1] };
								if (verif_coup(partie, coup_prise_echec, 1) == 0)
								{
									partie->player = 1 - partie->player;
									return 0;
								}
							}
						}
					}
					partie->player = 1 - partie->player;
				}
			}
		}
	}
		
	partie->player = 1 - partie->player;
	return 1;
}
