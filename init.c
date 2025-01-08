#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvp.h"
#include "verif.h"
#include "init.h"
#include "structure.h"

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
Partie creer_partie()
{
	Partie partie;

	// Initialiser le plateau dans l'état initial
    partie.plateau = creer_plateau();
	// Initialiser les données du joueur des blancs (position du roi, pas d'echec, pas de mat)
	partie.Blanc.xRoi = 7;
	partie.Blanc.yRoi = 4;
	partie.Blanc.echec = 0;
	partie.Blanc.mat = 0;
	partie.Blanc.score = 0;
	partie.Blanc.timer = DUREE_JEU; 
	// Initialiser les données du joueur des noirs (position du roi, pas d'echec, pas de mat)
	partie.Noir.xRoi =  0; 
	partie.Noir.yRoi =  4;
    partie.Noir.echec = 0;
	partie.Noir.mat = 0;
	partie.Noir.score = 0;
	partie.Noir.timer = DUREE_JEU; 
	// Initialise le joueur courant au joueur des blancs
    partie.player = BLANC;
	// Initialise la fiche de partie à vide
	partie.fiche_partie = NULL;
	partie.dernier_coup_joue = NULL;	
	// Retourner la partie initialisée
	return partie;
}

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
void liberer_partie(Partie partie)
{
	// Libération de l'espace mémoire occupé par le plateau
	for(int i = 0; i < MAX_CASE; i++)
	{
		free(*((partie.plateau) + i));
	}
	free(partie.plateau);

	// Libération de l'espace mémoire occupé par la fiche de partie 	
	liberer_fiche(partie.fiche_partie);
}

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
 void liberer_fiche(CoupEnregistre *coup_efface)
 {
	if (coup_efface->suivant == NULL)
	{
		free(coup_efface);
	}
	else
	{
		liberer_fiche(coup_efface->suivant);
		free(coup_efface);
	}
}

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
Position **creer_plateau()
{	
	// Allouer la mémoire nécessaire pour un tableau 8x8
    Position **plateau = malloc(sizeof(*plateau) * MAX_CASE);
	CHECK_MALLOC(plateau);
    for(int i = 0; i < MAX_CASE; i++)
	{
        *(plateau + i) = malloc(sizeof(**plateau) * MAX_CASE);
		CHECK_MALLOC(*(plateau + i));
	}

    // Initialiser les cases VIDE du plateau
    for(int i = 2; i < MAX_CASE-2; i++)
	{
		for(int j = 0; j < MAX_CASE; j++)
		{
			plateau[i][j].p = VIDE;
			plateau[i][j].c = BLANC;			
		}
	}

	// Placer les pions noirs et blancs sur le plateau
    for(int i = 0; i < MAX_CASE; i++)
	{
        plateau[1][i].p = PION;
        plateau[1][i].c = NOIR;
        plateau[6][i].p = PION;
        plateau[6][i].c = BLANC;
    }

	// Placer les 5 premières pièces majeures Tour, Cavalier, Fou, Dame et Roi
    Piece piece_iter = TOUR;
    int j;
    for(j = 0; j < (MAX_CASE / 2) + 1; j++)
	{
        plateau[0][j].p = piece_iter;
        plateau[0][j].c = NOIR;
        plateau[7][j].p = piece_iter;
        plateau[7][j].c = BLANC;
        piece_iter++;        
    }
	
	// Placer les 3 dernières pièces majeures Fou, Cavalier, Tour
    piece_iter = FOU;
    for(int i = j; i < MAX_CASE + 1; i++)
	{
        plateau[0][i].p = piece_iter;
        plateau[0][i].c = NOIR;
        plateau[7][i].p = piece_iter;
        plateau[7][i].c = BLANC;
        piece_iter --;
    }
	
	// Retourner le plateau initialisé
    return plateau;
}