/******************************************************************************
 * Nom du fichier : pvp.c
 * Description    : Jeu d'echec pour 2 joueurs.
 *  
 * Représentation du plateau : La convention des pièces est la suivante : Roi: R
 *  Dame : D, Fou : F, Cavalier : C, Tour : T, Pion : P.
 *  Pour un joueur les pièces sont écrites en majuscule, pour l'autre en minuscule.
 *  --Apport personnel-- : Un tour dans la case a été ajouté afin de mieux visualiser 
 *  les cases blanches et les cases noires. De plus le plateau tourne à chaque 
 *  tour afin que le joueur qui doit jouer voit le plateau comme s'il était devant 
 *  un vrai plateau.  
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 * 8|░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 * 7|     |░░░░░|     |░░░░░|     |░░R░░|     |░░r░░|
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 * 6|░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 * 5|     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 * 4|░░p░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 * 3|  P  |░░░░░|  F  |░░░░░|     |░░░░░|     |░░░░░|
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 * 2|░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|     |
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 * 1|     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  |     |░░░░░|     |░░░░░|     |░░░░░|     |░░░░░|
 *  +-----+-----+-----+-----+-----+-----+-----+-----+
 *    A     B     C     D     E     F     G     H
 *
 * Validité des coups : La fonction de vérification vérifie que la case de départ 
 *  contient une pièce du joueur et que la case d'arrivée ne contient pas une 
 *  pièce du joueur.
 *  --Apport personnel-- : La fonction de vérification vérifie que seul les 
 *  déplacement légaux sont autorisés. Notamment que la trajectoire de déplacement
 *  ne contient pas de pièce. Que le roi ne se déplace que d'une case. Que le pion 
 *  se déplace d'une case en avant ou de deux s'il n'a pas encore bougé et en diagonale 
 *  d'une case pour prendre. Le pion se déplace uniquement vers l'avant. 
 *  Le petit roque et le grand roque sont autorisés. 
 *  Détection de la situation d'échec et interdiction du mouvement si le mouvement 
 *  conduit à un échec. L'information est clairement affichée pour le joueur.
 *
 * Déplacement :
 *  --Apport personnel-- :
 *  Le pion peut être promu lorsqu'uil arrive en bout d'échiquier.
 *  Auto-test par lancement de coups préenregistrés avant de donner la main au joueur
 *
 * Fin de programme : Sur détection du mat
 *  --Apport personnel-- :
 *  Affichage de la feuille de score
 *
 * Amélioration en attente : 
 * -----------------------
 *  - Interdire le roque lorsque la tour ou le roi ont déjà bougé.
 *  - Fin de programme sur Pat
 *  - Fin de programme sur abandon d'un joueur
 *  - Fin de programme sur match null
 *  - Sauvegarde et enregistrement de la partie
 *  - Calcule et affichage de la valeur des pièces (Score)
 *  - Gestion du temps, affichage du temps disponible à chaque joueur, défaite 
 *    en cas de temps dépassé
 *  - Feuille de match : identifier lorsqu'un déplacement peut être joué par 
 *    deux pièces identiques pour les diférencier par la colonne ou la ligne 
 *    dans la feuille de match 
 *  - Feuille de match : n'afficher le résultat que lorsque le match est terminé
 *  - Feuille de match : Ne pas afficher la feuille de match au cours de la partie
 *    mais uniquement le dernier coup.
 *  - IA minimale qui joue des coups légaux contre le joueur
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvp.h"
#include "autotest.h"

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
char piece2char(Position case_courante)
{
	switch (case_courante.p)
	{
		case PION: 
			return((case_courante.c == BLANC )? 'P' : 'p' );
		
		case TOUR: 
			return((case_courante.c == BLANC )? 'T' : 't' );
			
		case CAVALIER:
			return((case_courante.c == BLANC )? 'C' : 'c' );
			
		case FOU: 
			return((case_courante.c == BLANC )? 'F' : 'f' );
		
		case REINE:
			return((case_courante.c == BLANC )? 'D' : 'd' );
		
		case ROI:
			return((case_courante.c == BLANC )? 'R' : 'r' );
		default :
			return(' ');
	}
}

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
void afficher_plateau(Partie *partie)
{
    Position **plateau = partie->plateau;
    printf("\n +-----+-----+-----+-----+-----+-----+-----+-----+\n");
	if (partie->player == BLANC)
	{
		// Afficher le plateau avec la case A1 en bas à gauche
		for (int i = 0; i < MAX_CASE; i++)
		{
			printf(" ");
			for (int j = 0; j < MAX_CASE; j++)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒▒▒▒");   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("|\n%d", MAX_CASE-i);
			for (int j = 0; j < MAX_CASE; j++)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒%c▒▒",piece2char(plateau[i][j])== ' '?'▒':piece2char(plateau[i][j]));   
				}
				else
				{
					printf("|  %c  ", piece2char(plateau[i][j]));   
				}
			}
			printf("|\n ");
			for (int j = 0; j < MAX_CASE; j++)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒▒▒▒");  
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("|\n");
			printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n");
		}
		printf("    A     B     C     D     E     F     G     H\n");
	}
	else 
	{
		// Afficher le plateau avec la case A1 en haut à droite
		for (int i = MAX_CASE-1; i >= 0; i--)
		{
			printf(" ");
			for (int j = MAX_CASE-1; j >= 0; j--)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒▒▒▒");   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("|\n%d", MAX_CASE-i);
			for (int j = MAX_CASE-1; j >= 0; j--)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒▒▒▒", piece2char(plateau[i][j])== ' '?'▒':piece2char(plateau[i][j]));   
				}
				else
				{
					printf("|  %c  ", piece2char(plateau[i][j]));   
				}
			}
			printf("|\n ");
			for (int j = MAX_CASE-1; j >= 0; j--)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|▒▒▒▒▒");   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("|\n");
			printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n");
		}
		printf("    H     G     F     E     D     C     B     A\n");
	}
}

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
CoupEnregistre *creer_coup_enregistre()
{
	CoupEnregistre *nv_coup_enregistre = malloc(sizeof(CoupEnregistre));
	CHECK_MALLOC(nv_coup_enregistre);
	
	nv_coup_enregistre->suivant = NULL;
	nv_coup_enregistre->piece = VIDE;
	nv_coup_enregistre->promotion = VIDE;	
	nv_coup_enregistre->prise = 0;
	nv_coup_enregistre->grandRoque = 0;
	nv_coup_enregistre->petitRoque = 0;
	nv_coup_enregistre->echec = 0;
	nv_coup_enregistre->mat = 0;
	return nv_coup_enregistre;
}

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
void afficher_fiche_partie(CoupEnregistre *fiche_partie, Partie partie)
{
	printf("Voici votre fiche de partie :\n");
	
	// Controle si des coup ont été joué
	if (fiche_partie == NULL)
	{
		printf("Aucun coup joué !\n");
		return;
	}
	
	// Affiche en tete des colonnes des coups
	printf("\tBLANC\t\tNOIR\n");
	
	CoupEnregistre *coup_joue = fiche_partie;
	int i = 0;
	while (coup_joue != NULL)
	{
		if (i%2==0)
		{
			printf("%d\t", i/2+1);
		}
		else
		{
			printf("\t\t");
		}
		
		if (coup_joue->grandRoque)
		{
			// Affiche O-O-O pour le grand roque
			printf("O-O-O");
		}
		else if (coup_joue->petitRoque)
		{
			// Affiche O-O pour le petit roque
			printf("O-O");
		}
		else
		{		
			// Affiche la pièce qui joue
			switch (coup_joue->piece)
			{
				case PION:
					if (coup_joue->prise)
					{
						printf("%c", 'a' + coup_joue->coup.yFrom);					
					}
					break;
				case TOUR: 
					printf("T");
					break;
				case CAVALIER:
					printf("C");
					break;				
				case FOU: 
					printf("F");
					break;
				case REINE:
					printf("D");
					break;			
				case ROI:
					printf("R");
					break;
			}

			// Affiche x si le coup est une prise 
			if (coup_joue->prise)
			{
				printf("x");
			}

			// Affiche la case d'arrivée
			printf("%c%d",'a' + coup_joue->coup.yTo, MAX_CASE - coup_joue->coup.xTo);
			
			// Affiche la promotion
			switch (coup_joue->promotion)
			{
				case TOUR: 
					printf("T");
					break;
				case CAVALIER:
					printf("C");
					break;				
				case FOU: 
					printf("F");
					break;
				case REINE:
					printf("D");
					break;			
			}
		}
		
		if (coup_joue->mat)
		{
			// Affiche # si le coup génère un échec et mat
			printf("#");
		}
		else if (coup_joue->echec)
		{
			// Affiche + si le coup génère un échec
			printf("+");
		}
						
		// Affiche un retour à la ligne si l'on a écrit le coup noir
		printf("%s", i%2==0?"":"\n");
		
		// Passe au coup suivant
		coup_joue = coup_joue->suivant;		
		i++;
	}
	if(partie.Blanc.mat)
	{
		printf("\nResultat : 1 - 0\n");
	}
	else if(partie.Noir.mat)
	{
		printf("\nResultat : 0 - 1\n");
	}
}

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
 
void maj_score(Partie *partie, Piece piece_prise)
{
	Joueur *joueur;
	if (partie->player == BLANC)
	{
		joueur = &(partie->Blanc);
	}
	else
	{
		joueur = &(partie->Noir);
	}
	switch (piece_prise)
	{
		case PION:
			joueur->score += 1;
			break;
		case TOUR:
			joueur->score += 5;
			break;			
		case CAVALIER:
			joueur->score += 3;
			break;				
		case FOU: 
			joueur->score += 3;
			break;				
		case REINE:
			joueur->score += 9;
			break;
	}
}

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
 Coup proposition_joueur()
 {
	Coup coup;
	int n;
	char c;

	// Demander la position de la pièce à jouer
	printf("Donnez la position initiale du coup:\n");
	scanf("%c", &c);
	scanf("%d", &n); 
	//Permet de traduire les coordonnées joueur en coordonnées réel
	coup.xFrom = MAX_CASE - n;
	coup.yFrom = c - 'A';
	while ((getchar()) != '\n'); //Permet de clear le buffer pour eviter qu'un scanf soit ignoré
		
	// Demander la position de destination de la pièce
	printf("Donnez la position finale du coup :\n");
	scanf("%c", &c);
	scanf(" %d", &n);
	//Permet de traduire les coordonnées joueur en coordonnées réel
	coup.xTo = MAX_CASE - n;
	coup.yTo = c - 'A';
	while ((getchar()) != '\n');
	
	// Retourne le coup du joueur
	//printf("Coup: %d%d->%d%d\n", coup.xFrom, coup.yFrom, coup.xTo, coup.yTo);
	return coup;
}

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
void jouer_coup(Partie *partie, Coup coup)
{

	// Créer un enregistrement du coup pour la fiche de partie
	CoupEnregistre *nouveau_coup_enregistre = creer_coup_enregistre();
	nouveau_coup_enregistre->piece = partie->plateau[coup.xFrom][coup.yFrom].p;
	nouveau_coup_enregistre->coup = coup;

	// Vérifier la prise d'une pièce pour l'affichage de la fiche de partie
	nouveau_coup_enregistre->prise = partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player;
	if (nouveau_coup_enregistre->prise)
	{ 
		Piece piece_prise = partie->plateau[coup.xTo][coup.yTo].p;
		maj_score(partie, piece_prise);
	}
	
	// Vérifier Si le déplacement du roi est un roque pour l'affichage de la feuille de partie
	nouveau_coup_enregistre->petitRoque = partie->plateau[coup.xFrom][coup.yFrom].p == ROI
	                                    && coup.yTo > coup.yFrom
										&& coup.yTo - coup.yFrom == 2;
	nouveau_coup_enregistre->grandRoque = partie->plateau[coup.xFrom][coup.yFrom].p == ROI
	                                    && coup.yFrom > coup.yTo
										&& coup.yFrom - coup.yTo == 2;

	
	if (nouveau_coup_enregistre->grandRoque)
	{
		Position new = partie->plateau[coup.xFrom][0];
		partie->plateau[coup.xFrom][0].p = VIDE;
		partie->plateau[coup.xFrom][0].c = BLANC;
		partie->plateau[coup.xTo][3].p = new.p;
		partie->plateau[coup.xTo][3].c = new.c;		
	} 
	else if (nouveau_coup_enregistre->petitRoque)
	{
		Position new = partie->plateau[coup.xFrom][MAX_CASE - 1];
		partie->plateau[coup.xFrom][MAX_CASE - 1].p = VIDE;
		partie->plateau[coup.xFrom][MAX_CASE - 1].c = BLANC;
		partie->plateau[coup.xTo][MAX_CASE - 3].p = new.p;
		partie->plateau[coup.xTo][MAX_CASE - 3].c = new.c;
	}

	// Déplacer la pièce jouée 
	Position new = partie->plateau[coup.xFrom][coup.yFrom];
	partie->plateau[coup.xFrom][coup.yFrom].p = VIDE;
	partie->plateau[coup.xFrom][coup.yFrom].c = BLANC;
	partie->plateau[coup.xTo][coup.yTo].p = new.p;
	partie->plateau[coup.xTo][coup.yTo].c = new.c;
	
	// Sauvegarder les coordonnées des rois
	if(new.p == ROI)
	{
		if(partie->player == BLANC)
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

	// Promouvoir un pion	
	if (partie->plateau[coup.xTo][coup.yTo].p == PION)
	{
		nouveau_coup_enregistre->promotion = promotion_pion(partie, coup);
		partie->plateau[coup.xTo][coup.yTo].p = nouveau_coup_enregistre->promotion;
	}
	// Détecter si échec au roi adverse
	nouveau_coup_enregistre->echec = est_echec(partie);

	if (partie->player == BLANC)
	{
		partie->Noir.echec = nouveau_coup_enregistre->echec;
	}
	else
	{
		partie->Blanc.echec = nouveau_coup_enregistre->echec;			
	}

	// Détecter si échec et mat au roi adverse
	if (nouveau_coup_enregistre->echec)
	{
		nouveau_coup_enregistre->mat = est_mat(partie);
		if (partie->player == BLANC)
		{
			partie->Noir.mat = nouveau_coup_enregistre->mat;
		}
		else
		{
			partie->Blanc.mat = nouveau_coup_enregistre->mat;			
		}
	}
	
	// Mise à jour du temps du joueur
	clock_t end = clock();
	if (partie->player == BLANC)
	{
		partie->Blanc.timer += (int) (partie->debut_coup - end) / CLOCKS_PER_SEC;
	}
	else
	{
		partie->Noir.timer += (int) (partie->debut_coup - end) / CLOCKS_PER_SEC;
	}
	partie->debut_coup = clock();
	
			
	// Enregistrer le coup joué dans la fiche de match		
	if (partie->fiche_partie == NULL)
	{
		partie->fiche_partie = nouveau_coup_enregistre;
		partie->dernier_coup_joue = nouveau_coup_enregistre;
	}
	else
	{
		partie->dernier_coup_joue->suivant = nouveau_coup_enregistre;
		partie->dernier_coup_joue = nouveau_coup_enregistre;		
	}

	// Changer de joueur
	partie->player = 1-partie->player;


}

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
Piece promotion_pion(Partie *partie, Coup coup)
{

	// Vérifier que la pièce est un pion sinon renvoyer la piece
	if (partie->plateau[coup.xTo][coup.yTo].p != PION)
	{
		return partie->plateau[coup.xTo][coup.yTo].p;
	}
	
	// Vérifier que la destination est bien une ligne de fond sinon renvoyer la piece
	if (coup.xTo != 0 && coup.xTo != MAX_CASE-1)
	{
		return partie->plateau[coup.xTo][coup.yTo].p;
	}

	// Demander la promotion au joueur
	int temp = PION;
	int loop = 0;
	while(loop == 0)
	{
		loop = 1;
		printf("Votre pion est promu, choissisez une piece pour le remplacer\n");
		printf("1-PION 2-TOUR 3-CAVALIER 4-FOU 5-DAME\n");
		scanf("%d",&temp);
		if(temp < 1 || temp > 5)
		{
			printf("Erreur de saisi\n");
			loop = 0;
		}
	}

	// Renvoyer la promotion
	return temp;
}

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
void play_pvp()
{
	// Créer la partie dans l'état initial
	Partie partie = creer_partie();
	
	// Initialisation du code d'erreur de la vérification du coup à Pas d'erreur.
	Coup coup_joueur;
	int code_erreur_verif = 0;
		
		
	// Afficher le plateau à l'état initial
	afficher_plateau(&partie);
	
	// Demander le premier coup 
	int coup_auto_iter = 0;
	if (coup_auto_iter < COUP_AUTO_MAX)
	{
		coup_joueur = CoupAuto[coup_auto_iter];
		coup_auto_iter ++;
	}
	else
	{	
		coup_joueur = proposition_joueur();
	}
	
	// Tant que pas d'échec et mat
	while(!partie.Blanc.mat && !partie.Noir.mat)
	{	
		// Vérifier la validité du coup
		code_erreur_verif = verif_coup(&partie, coup_joueur, 1);
		
		if(code_erreur_verif == 0)
		{
			// Déplacer les pièces
			jouer_coup(&partie, coup_joueur);
			if (!partie.Blanc.mat && !partie.Noir.mat)
			{
				// Afficher la fiche de partie
				afficher_fiche_partie(partie.fiche_partie, partie);
					
				// Afficher le plateau et le score actuel
				afficher_plateau(&partie);
				printf("Coup: {%d, %d, %d, %d}\n", coup_joueur.xFrom, coup_joueur.yFrom, coup_joueur.xTo, coup_joueur.yTo); // utile pour le débogage
				printf("Score : %d - %d\n", partie.Blanc.score, partie.Noir.score);
				
				// Afficher les informations du joueur (joueur qui joue, temps restant, état echec ou erreur du coup précédent)
				if (partie.player == BLANC)
				{
					if (partie.Blanc.echec)
					{
						printf("Echec au roi\n");
					}
					if (partie.Blanc.timer <= 0)
					{
						printf("Les blancs n'ont plus le temps de jouer.\n");
						partie.Blanc.mat = 1;
						partie.player = 1 - partie.player;
					}
					else
					{
						int min = partie.Blanc.timer / 60;
						int sec = partie.Blanc.timer - min * 60;
						printf("Les blancs jouent (Temps restant : %d min %d s)\n", min, sec);
					}
				}
				else
				{
					if (partie.Noir.echec)
					{
						printf("Echec au roi\n");
					}
					if (partie.Noir.timer <= 0)
					{
						printf("Les noirs n'ont plus le temps de jouer.\n");
						partie.Noir.mat = 1;
						partie.player = 1 - partie.player;
					}
					else
					{
						int min = partie.Noir.timer / 60;
						int sec = partie.Noir.timer - min * 60;
						printf("Les noirs jouent (Temps restant : %d min %d s)\n", min, sec);
					}
				}	
			}
			else
			{
				printf("Coup: {%d, %d, %d, %d}\n", coup_joueur.xFrom, coup_joueur.yFrom, coup_joueur.xTo, coup_joueur.yTo); // utile pour le débogage
				printf("Score : %d - %d\n", partie.Blanc.score, partie.Noir.score);
			}
		}	
		else
		{			
			printf(" *** ATTENTION : Le coup {%d, %d, %d, %d} invalide {err_%d}!\n Rejouez !\n", coup_joueur.xFrom, coup_joueur.yFrom, coup_joueur.xTo, coup_joueur.yTo, code_erreur_verif);
		}		
		
		// Lire le coup à jouer (Joueur ou tableau de test automatique)
		
		if (!partie.Blanc.mat && !partie.Noir.mat)
		{
			if (coup_auto_iter < COUP_AUTO_MAX)
			{
				coup_joueur = CoupAuto[coup_auto_iter];
				coup_auto_iter ++;
			}
			else
			{	
				coup_joueur = proposition_joueur();
			}
		}
	}
	
	// Afficher le résultat de la partie
	printf("**** Fin de la partie ****\n");
	int vainqueur = partie.player;
	partie.player = BLANC;
	afficher_plateau(&partie);
	printf("Echec et mat, victoire de %s\n", vainqueur == BLANC?"Blanc":"Noir" );
	afficher_fiche_partie(partie.fiche_partie, partie);
	
	// Libérer l'espace mémoire utilisé par la partie
	liberer_partie(partie);
}

/******************************************************************************
 * Nom de fonction : main
 *
 * Description : Programme principal
 * - Lancer le jeu humain contre humain
 *
 * Paramètres d'entrée : Aucun
 * Paramètres de retour : Aucun 
 ******************************************************************************/
int main(){
	play_pvp();
}
