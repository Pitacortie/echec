#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvp.h"
#include "verif.h"
#include "init.h"
#include "autotest.h"
#include "structure.h"



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
					if (piece2char(plateau[i][j])== ' ')
					{
						printf("|▒▒▒▒▒"
					}
					else 
					{
						printf("|▒▒%c▒▒",piece2char(plateau[i][j]));
					}
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
					if (piece2char(plateau[i][j])== ' ')
					{
						printf("|▒▒▒▒▒"
					}
					else 
					{
						printf("|▒▒%c▒▒",piece2char(plateau[i][j]));
					}  
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
