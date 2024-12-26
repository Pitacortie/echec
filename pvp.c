/******************************************************************************
 * Nom du fichier : pvp.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "pvp.h"

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
 * Retour : Partie : La partie initialisée
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
	// Initialiser les données du joueur des noirs (position du roi, pas d'echec, pas de mat)
	partie.Noir.xRoi =  0; 
	partie.Noir.yRoi =  4;
    partie.Noir.echec = 0;
	partie.Noir.mat = 0;
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
 * Paramètres :
 * Paramètre   Type        I/O   Description
 * ---------   ---------   ---   ----------------------------------------------
 * partie     Partie ptr   I/O   La partie en cours dont les différents 
 *								 pointeurs doivent être libérés 
 * 
 * Retour : Aucun 
 ******************************************************************************/
void liberer_partie(Partie partie)
{
	// Libération de l'espace mémoire occupé par le plateau
	for(int i = 0; i < MAX_CASE; i++){
		free(*((partie.plateau) + i));
	}
	free(partie.plateau);

	// Libération de l'espace mémoire occupé par la fiche de partie 	
	liberer_fiche(partie.fiche_partie);
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
 * Retour : Position**
 ******************************************************************************/
Position **creer_plateau()
{	
	// Allouer la mémoire nécessaire pour un tableau 8x8
    Position **plateau = malloc(sizeof(*plateau) * MAX_CASE);
	CHECK_MALLOC(plateau);
    for(int i = 0; i < MAX_CASE; i++){
        *(plateau + i) = malloc(sizeof(**plateau) * MAX_CASE);
		CHECK_MALLOC(*(plateau + i));
	}

    // Initialiser les cases VIDE du plateau
    for(int i = 2; i < MAX_CASE-2; i++){
		for(int j = 0; j < MAX_CASE; j++){
			plateau[i][j].p = VIDE;
			plateau[i][j].c = BLANC;			
		}
	}

	// Placer les pions noirs et blancs sur le plateau
    for(int i = 0; i < MAX_CASE; i++){
        plateau[1][i].p = PION;
        plateau[1][i].c = NOIR;
        plateau[6][i].p = PION;
        plateau[6][i].c = BLANC;
    }

	// Placer les 5 premières pièces majeures Tour, Cavalier, Fou, Dame et Roi
    Piece piece_iter = TOUR;
    int j;
    for(j = 0; j < (MAX_CASE / 2) + 1; j++){
        plateau[0][j].p = piece_iter;
        plateau[0][j].c = NOIR;
        plateau[7][j].p = piece_iter;
        plateau[7][j].c = BLANC;
        piece_iter++;        
    }
	
	// Placer les 3 dernières pièces majeures Fou, Cavalier, Tour
    piece_iter = FOU;
    for(int i = j; i < MAX_CASE + 1; i++){
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
 * Retour : char
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
 * Retour : aucun
 ******************************************************************************/
void afficher_plateau(Partie *partie)
{
    Position **plateau = partie->plateau;
    printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n");
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
					printf("|%c%c%c%c%c",0xB0,0xB0,0xB0,0xB0,0xB0);   
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
					printf("|%c%c%c%c%c", 0xB0,0xB0,piece2char(plateau[i][j])== ' '?0xB0:piece2char(plateau[i][j]),0xB0,0xB0);   
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
					printf("|%c%c%c%c%c",0xB0,0xB0,0xB0,0xB0,0xB0);  
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
					printf("|%c%c%c%c%c",0xB0,0xB0,0xB0,0xB0,0xB0);   
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
					printf("|%c%c%c%c%c", 0xB0, 0xB0, piece2char(plateau[i][j])== ' '?0xB0:piece2char(plateau[i][j]), 0xB0, 0xB0);   
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
					printf("|%c%c%c%c%c",0xB0,0xB0,0xB0,0xB0,0xB0);   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("\n");
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
 * Retour : Aucun 
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
 * Paramètres :
 * Paramètre     Type                 E/S  Description
 * ---------     ------------------   ---  ----------------------------------------------
 * fiche_partie  CoupEnregistre ptr    E   Pointeur sur le premier coup de la 
 *                                         liste des coups de la partie.
 * 
 * Retour : Aucun 
 ******************************************************************************/
void afficher_fiche_partie(CoupEnregistre *fiche_partie){
	printf("Voici votre fiche de partie :\n");
	
	// Controle si des coup ont été joué
	if (fiche_partie == NULL){
		printf("Aucun coup joué !\n");
		return;
	}
	
	// Affiche en tete des colonnes des coups
	printf("\tBLANC\t\tNOIR\n");
	
	CoupEnregistre *coup_joue = fiche_partie;
	int vainqueur = -1;
	int i = 0;
	while (coup_joue != NULL){
		if (i%2==0){
			printf("%d\t", i/2+1);
		}else{
			printf("\t\t");
		}
		
		if (coup_joue->grandRoque){
			// Affiche O-O-O pour le grand roque
			printf("O-O-O");
		}else if (coup_joue->petitRoque){
			// Affiche O-O pour le petit roque
			printf("O-O");
		}else{		
			// Affiche la pièce qui joue
			switch (coup_joue->piece){
				case PION:
					if (coup_joue->prise){
						printf("%c", 'A' + coup_joue->coup.yFrom + 32);					
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
			if (coup_joue->prise){
				printf("x");
			}

			// Affiche la case d'arrivée
			printf("%c%d",'A' + coup_joue->coup.yTo, MAX_CASE - coup_joue->coup.xTo);
			
			// Affiche la promotion
			switch (coup_joue->promotion){
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

		
		if (coup_joue->mat){
			// Affiche # si le coup génère un échec et mat
			printf("#");
			vainqueur = i%2 != 0;
		}else if (coup_joue->echec){
			// Affiche + si le coup génère un échec
			printf("+");
		}
						
		// Affiche un retour à la ligne si l'on a écrit le coup noir
		printf("%s", i%2==0?"":"\n");
		
		// Passe au coup suivant
		coup_joue = coup_joue->suivant;		
		i++;
	}
	
	printf("\nResultat: %d - %d\n", vainqueur == BLANC?1:0, vainqueur == BLANC?0:1);
}

/******************************************************************************
 * Nom de fonction : liberer_fiche
 *
 * Description : Libère récursivement l'espace mémoire pris par les coups 
 *               enregistrés de la fiche de match
 *
 * Paramètres :
 * Paramètre   Type          E/S   Description
 * ---------   ---------     ---   ----------------------------------------------
 * coup_efface CoupEnregistre E   Le coup à libérer 
 * 
 * Retour : Aucun 
 ******************************************************************************/
 void liberer_fiche(CoupEnregistre *coup_efface){
	if (coup_efface->suivant == NULL){
		free(coup_efface);
	}else{
		liberer_fiche(coup_efface->suivant);
		free(coup_efface);
	}
}

//Cette fonction permet de mettre à jour le score du joueur
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
 * Retour : Coup : Le coup que souhaite jouer le joueur
 ******************************************************************************/
 Coup proposition_joueur(){
	Coup coup;
	int n;
	char c;

	// Demander la position de la pièce à jouer
	printf("Donnez la position de la piece que vous voulez jouer :\n");
	scanf("%c", &c);
	scanf("%d", &n); 
	//Permet de traduire les coordonnées joueur en coordonnées réel
	coup.xFrom = MAX_CASE - n;
	coup.yFrom = c - 'A';
	while ((getchar()) != '\n'); //Permet de clear le buffer pour eviter qu'un scanf soit ignoré
		
	// Demander la position de destination de la pièce
	printf("Donnez la position de la case sur laquelle déplacer la pièce :\n");
	scanf("%c", &c);
	scanf(" %d", &n);
	coup.xTo = MAX_CASE - n;
	coup.yTo = c - 'A';
	while ((getchar()) != '\n');
	
	// Retourne le coup du joueur
	printf("Coup: %d%d->%d%d\n", coup.xFrom, coup.yFrom, coup.xTo, coup.yTo);
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
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  11 : Le coup n'est pas un mouvement en diagonale
 *                  12 : Une pièce se trouve sur la diagonale
 ******************************************************************************/
int verif_diag(Partie *current, Coup coup){
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une diagonale
	if (vect_x == 0 || abs(vect_x) != abs(vect_y)){
		return 11;
	}
	
	// Verifier que les cases de la diagonale sont vide	
	int norme = abs(vect_x);
	int x_iter = vect_x >0?1:-1;
	int y_iter = vect_y >0?1:-1;
    for(int i = 1; i < norme ; i++){ 
	    int x_test = coup.xFrom + i * x_iter;
		int y_test = coup.yFrom + i * y_iter;

		if(current->plateau[x_test][y_test].p != VIDE){
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
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  21 : Le coup n'est pas un mouvement en verticale
 *                  22 : Une pièce se trouve sur la diagonale
 ******************************************************************************/
int verif_vert(Partie *current, Coup coup){
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une verticale
	if(coup.yFrom != coup.yTo){
		return 21;
	}
	
	// Verifier que les cases de la verticale sont vide
	int norme = abs(vect_x);
	int x_iter = vect_x >0?1:-1;
    for(int i = 1; i < norme ; i++){ 
	    int x_test = coup.xFrom + i * x_iter;
		int y_test = coup.yFrom;

		if(current->plateau[x_test][y_test].p != VIDE){
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
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  31 : Le coup n'est pas un mouvement en horizontale
 *                  32 : Une pièce se trouve sur l'horizontale
 ******************************************************************************/
int verif_hor(Partie *current, Coup coup){
	int vect_x = coup.xTo - coup.xFrom; // Calcule la coordonnée en x du vecteur du coup
	int vect_y = coup.yTo - coup.yFrom; // Calcule la coordonnée en y du vecteur du coup

	// Verifier que le déplacement est bien une horizontale
	if(coup.xFrom != coup.xTo){
		return 31;
	}
	
	// Verifier que les cases de l'horizontale sont vide
	int norme = abs(vect_y);
	int y_iter = vect_y >0?1:-1;
    for(int i = 1; i < norme ; i++){ 
	    int x_test = coup.xFrom;
		int y_test = coup.yFrom + i * y_iter;

		if(current->plateau[x_test][y_test].p != VIDE){
			return 32;
		}
    }
			
	return 0;
}

//Permet de veifier le déplacement d'un pion
/******************************************************************************
 * Nom de fonction : verif_pion
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement d'un 
 *               pion. Le pion se déplace verticalement d'une case. Il peut se 
 *               déplacer de 2 cases lors de son premier déplacement. Il ne prend
 *               une pièce que d'une case en diagonale.
 *
 * - Verifier que le déplacement correspond à une verticale
 * - Verifier que le déplacement correspond à une diagonale
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  101 : Le mouvement ne correspond pas au déplacement d'un pion
 *                  102 : La destination du mouvement sans prise est occupee
 ******************************************************************************/
 int verif_pion(Partie *partie, Coup coup)
{
	int vect_x = coup.xFrom - coup.xTo;
	
	int verif_v = verif_vert(partie, coup);
	int verif_d = verif_diag(partie, coup);
	
	// Verifier que le déplacement correspond à une verticale
	if (verif_vert(partie, coup) == 0){
		if (partie->plateau[coup.xTo][coup.yTo].p != VIDE)
		{
			return 102;
		}
		if (vect_x == 1 && partie->player == BLANC){
			return 0;
		}
		if (vect_x == -1 && partie->player == NOIR){
			return 0;
		}
		
		if (vect_x == 2 && partie->player == BLANC && coup.xFrom == 6){
			return 0;
		}

		if (vect_x == -2 && partie->player == NOIR && coup.xFrom == 1){
			return 0;
		}		
	}

	// Verifier que le déplacement correspond à une diagonale
	if (verif_diag(partie, coup) == 0){
		if (vect_x == 1 && partie->player == BLANC && partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player){
			return 0;
		}
		if (vect_x == -1 && partie->player == NOIR && partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player){
			return 0;
		}
	}
	
	return 101;
}

/******************************************************************************
 * Nom de fonction : verif_tour
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement de 
 *               la tour. La tour se déplace horizontalement ou verticalement.
 *
 * - Verifier que le déplacement correspond à une verticale ou une horizontale
 * - Verifier que le déplacement n'est pas bloquée par une pièce
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  41 : Le mouvement ne correspond pas au déplacement d'une tour
 *                  42 : Une pièce bloque le déplacement
 ******************************************************************************/
int verif_tour(Partie *current, Coup c){
	int verif_v = verif_vert(current, c);
	int verif_h = verif_hor(current, c);
	
	// Verifier que le déplacement correspond à une verticale ou une horizontale
	if (verif_v == 21 && verif_h == 31)
	{
		return 41;
	}
	
	// Verifier que le déplacement n'est pas bloquée par une pièce
	if (verif_v == 22 || verif_h == 32)
	{
		return 42;
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
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  71 : Le mouvement ne correspond pas au déplacement d'une dame
 *                  72 : Une pièce bloque le déplacement
******************************************************************************/
int verif_reine(Partie *current, Coup c)
{
	int verif_v = verif_vert(current, c);
	int verif_h = verif_hor(current, c);
	int verif_d = verif_diag(current, c);
	
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

//Une fonction de vérification spéciale pour les cavaliers
int verif_cav(Partie *current, Coup c)
{
	//On calcule les différences de x et de y, il reste plus qu'a verifier
	int dx = abs(c.xTo - c.xFrom);
	int dy = abs(c.yTo - c.yFrom);
	if((dx == 2 && dy == 1) || (dy == 2 && dx == 1)){
		if(current->plateau[c.xTo][c.yTo].p == VIDE || current->plateau[c.xTo][c.yTo].c != current->plateau[c.xFrom][c.yFrom].c)
			return 1;
	}
	return 0;
}

/******************************************************************************
 * Nom de fonction : verif_roi
 *
 * Description : Vérifie que le coup proposé est valide pour le déplacement du 
 *               roi. Le roi se déplace d'une case dans tous les sens ou de 
 *               2 cases dans le cas du roque.
 *
 * - Verifier si le déplacement correspond à un roque
 *   - Verifier si le déplacement correspond à un grand roque
 *   - Verifier si le déplacement correspond à un petit roque
 * - Vérifier si le déplacement correspond à un déplacement simple (1 case)
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 * coup           Coup         E    Le coup proposé par le joueur
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  61 : Le mouvement ne correspond pas au déplacement du roi
 *                  62 : La position du roi ne permet pas le roque
 *                  63 : Le roque est impossible
 ******************************************************************************/
int verif_roi(Partie *current, Coup c)
{
	
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	
	// Vérifier si un roque
	if (norme == 2){
		if (c.yFrom != 4 || c.xFrom != c.xTo){
			return 62;
		}
	
		if ((c.xFrom != 0 && current->player == NOIR) || (c.xFrom != 7 && current->player == BLANC)){
			return 62;
		}
		
		// Verifier Grand roque
		if (c.yFrom > c.yTo && current->plateau[c.xFrom][0].p == TOUR && current->plateau[c.xFrom][0].c == current->player)
		{
			Coup coup_tour = { c.xFrom, 0, c.xFrom, 3 };
			Coup coup_roi = { c.xFrom, c.yFrom, c.xTo, c.yTo };
			int verif_t = verif_hor(current, coup_tour);
			int verif_r = verif_hor(current, coup_roi);
			if (verif_t == 0 && verif_r == 0)
			{
				return 0;
			}
		}	

		// Verifier Petit roque
		if (c.yFrom < c.yTo && current->plateau[c.xFrom][MAX_CASE-1].p == TOUR && current->plateau[c.xFrom][MAX_CASE-1].c == current->player)
		{
			Coup coup_tour = { c.xFrom, MAX_CASE-1, c.xFrom, 5 };
			Coup coup_roi = { c.xFrom, c.yFrom, c.xTo, c.yTo };
			int verif_t = verif_hor(current, coup_tour);
			int verif_r = verif_hor(current, coup_roi);
			if (verif_t == 0 && verif_r == 0)
			{
				return 0;
			}
		}	
		
		return 63;
	}
	// Vérifier si un déplacement simple (1 case)
	if(norme == 1){	
		return 0;
	}
	
	return 61;
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
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : Le coup est valide
 *                  1 : La position de départ n'est pas dans les limites de l'échiquier
 *                  2 : La position d'arrivée n'est pas dans les limites de l'échiquier
 *                  3 : La case de départ ne contient pas une pièce du joueur
 *                  4 : La case d'arrivée contient une pièce du joueur
 *                  5 : Le déplacement n'est pas conforme à la piece ou une pièce se trouve sur le trajet
 *                  6 : Le mouvement entraîne une situation d'échec 
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
	switch(piece){
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
		
		// 2- Vérifier si le joueur est en échec
		int validite_echec = est_echec(partie);

		// 3- Annuler le coup
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
		// 4- Retourner code d'erreur si echec généré par le déplacement
		if (validite_echec == 1){
			return 6;
		}
	}

	// Retourner l'état de la vérification
	return 0;
}

//Renvoie 1 si les vect (v1_x, v1_y) et (v2_x, v2_y) sont colinéaire, avec le produit vectorielle
int est_col(int v1_x, int v1_y, int v2_x, int v2_y)
{
	return (((v1_x * v2_y) - (v1_y * v2_x)) == 0);
}


//renvoie la trajectoire d'un coup
int **trajectoire(Coup c)
{
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int bis_x;
	int bis_y;
	int loop = 0;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	int **res = malloc(sizeof(*res) * norme);
	CHECK_MALLOC(res);
	for(int i = 0; i < norme; i++){
		*(res + i) = malloc(sizeof(int) * 2);
		CHECK_MALLOC(*(res + i));
	}

	for(int x = c.xFrom; x < c.xTo; x++){
		for(int y = c.yFrom; y < c.yTo; y++){
			//Pour chaque case de la grille, si le coup entre la case de départ et la case balayé est colinéaire avec notre coup, la case est dans la trajectoire
			bis_x = c.xFrom - x;
			bis_y = c.yFrom - y;
			if(est_col(vect_x, vect_y, bis_x, bis_y)){
				res[loop][0] = x;
				res[loop][1] = y;
				loop++;
			}
		}
	}
	return res;
}


/******************************************************************************
 * Nom de fonction : est_echec
 *
 * Description : Vérifie si la case de coord x, y, et ce couleur c,  est en échec
 *
 * - Vérifier si une pièce adverse peut prendre le roi
 *   (Parcours de chaque case et vérification si la pièce peut prendre le roi)
 * - Retourner l'état de la vérification
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur) 
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : La situation n'est pas en echec
 *                  1 : La situation est en echec
 ******************************************************************************/
 int est_echec(Partie *partie){		
	//printf("Debug - Est_echec %s\n", partie->player == BLANC?"Blanc":"Noir");
	// Verifier si une pièce adverse peut prendre le roi
	Coup coup_temp;
	for(int i = 0; i < MAX_CASE; i++){
		for(int j = 0; j < MAX_CASE; j++){
			coup_temp.xFrom = i;
			coup_temp.yFrom = j;
			coup_temp.xTo = partie->player == BLANC?partie->Noir.xRoi:partie->Blanc.xRoi;
			coup_temp.yTo = partie->player == BLANC?partie->Noir.yRoi:partie->Blanc.yRoi;

			int validite_coup = verif_coup(partie, coup_temp, 0);
			//printf("Debug - Est_echec-Verif_coup %d%d-%d%d %d\n", coup_temp.xFrom, coup_temp.yFrom, coup_temp.xTo, coup_temp.yTo, validite_coup);
			if(validite_coup == 0 || validite_coup == 6){
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
 * - Vérifier si le roi peut se déplacer
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * partie         Partie*      E    La partie en cours (plateau, joueur)
 *
 * Retour : entier : Code d'erreur de la validité du coup
 *                  0 : La situation n'est pas en echec et mat
 *                  1 : La situation est en echec et mat
 ******************************************************************************/
int est_mat(Partie *partie){
	// Modifier le joueur en cour
	// Les Blanc (resp les noirs) viennent de jouer, on va donc regarder 
	// si les noirs(resp les blancs) peuvent jouer un coup pour sortir de 
	// la situation d'echec. On change donc le joueur en cour afin que les 
	// fonctions considèrent que le joueur en cours est le joueur des noirs 
	// (resp des blancs). On rétablie le bon joueur avant de sortir de la fonction.
		
	int xRoi = partie->player == BLANC?partie->Blanc.xRoi:partie->Noir.xRoi;
	int yRoi = partie->player == BLANC?partie->Blanc.yRoi:partie->Noir.yRoi;
		
	// Déplacement du roi en echec
	// Si le roi en echec peut se déplacer sur une des cases autours de lui 
	// sans être en echec, il n'est plus mat.
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if (i!=0 || j!=0){				
				Coup deplacement_roi = {xRoi, yRoi, xRoi+i, yRoi+j};
				if(verif_coup(partie, deplacement_roi, 1) == 0){					
					return 0;
				}
			}
		}
	}

	// Rechercher Echec
	for(int i = 0; i < MAX_CASE; i++){
		for(int j = 0; j < MAX_CASE; j++){
			// On parcourt toute la grille, et on crée un coup entre la case balayée et la case à vérifier
			Coup temp;
			temp.xFrom = i;
			temp.yFrom = j;
			temp.xTo = xRoi;
			temp.yTo = yRoi;
			// Si la case contient une pièce adverse au roi en échec
			if ((partie->plateau[i][j].p != VIDE) && partie->plateau[i][j].c == partie->player){
				// Si le coup est valide 
				if (verif_coup(partie, temp, 0) == 0){
					// La pièce adverse au roi en échec peut le prendre.
					int vect_x = temp.xFrom - temp.xTo;
					int vect_y = temp.yFrom - temp.yTo;
					int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));

					// Vérifier si une pièce du roi en echec peut prendre la pièce qui génère l'échec en sortant de l'échec
					partie->player = 1 - partie->player;
					for(int k = 0; k < MAX_CASE; k++){
						for(int l = 0; l < MAX_CASE;l++){
							Coup priseEchec = { k, l, temp.xFrom, temp.yFrom };
							if (verif_coup(partie, priseEchec, 1) == 0){
								partie->player = 1 - partie->player;
								printf("Piece prend dame\n");
								return 0;
							}
						}
					}
					partie->player = 1 - partie->player;

					// Vérifier si la pièce qui met le roi en echec est un cavalier. 
					// Dans ce ca, il y a echec et mat
					if(partie->plateau[temp.xFrom][temp.yFrom].p == CAVALIER){
						printf("Mat cavalier\n");
						return 1;
					}

					// Vérifier si une pièce du roi en echec peut couper la trajectoire du coup qui met le roi en echec
					int **traj = trajectoire(temp);

					Couleur col = 1 - partie->plateau[temp.xFrom][temp.yFrom].c;
					//Si non, on parcour la trajectoire et on regarde si la case de la trajectoire est en "échec", c'est a dire si on peux aller dessus
					partie->player = 1 - partie->player;
					for(int normeIter = 0; normeIter < norme; normeIter++){						
						for(int k = 0; k < MAX_CASE; k++){
							for(int l = 0; l < MAX_CASE;l++){
								Coup priseEchec = { k, l, traj[normeIter][0], traj[normeIter][0] };
								if (verif_coup(partie, priseEchec, 1) == 0){
									partie->player = 1 - partie->player;
									printf("Trajectoire\n");
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
	printf("Pas de solution\n");

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
 * - Enregistrer le coup joué dans la fiche de match
 * - Changer de joueur
 *  
 * Paramètres :
 * Paramètre     Type                 E/S  Description
 * ---------     ------------------   ---  ----------------------------------------------
 * current       Partie ptr           E/S  Pointeur sur la partie en cours
 * 
 * Retour : Aucun
 ******************************************************************************/
void jouer_coup(Partie *partie, Coup coup){

	// Créer un enregistrement du coup pour la fiche de match
	CoupEnregistre *nouveau_coup_enregistre = creer_coup_enregistre();
	nouveau_coup_enregistre->piece = partie->plateau[coup.xFrom][coup.yFrom].p;
	nouveau_coup_enregistre->coup = coup;

	// Vérifier la prise d'une pièce pour l'affichage de la fiche de match
	nouveau_coup_enregistre->prise = partie->plateau[coup.xTo][coup.yTo].p != VIDE && partie->plateau[coup.xTo][coup.yTo].c != partie->player;
	if (nouveau_coup_enregistre->prise){ 
		Piece piece_prise = partie->plateau[coup.xTo][coup.yTo].p;
		maj_score(partie, piece_prise);
	}
	
	// Vérifier Si le déplacement du roi est un roque pour l'affichage de la feuille de match
	nouveau_coup_enregistre->petitRoque = partie->plateau[coup.xFrom][coup.yFrom].p == ROI
	                                    && coup.yTo > coup.yFrom
										&& coup.yTo - coup.yFrom == 2;
	nouveau_coup_enregistre->grandRoque = partie->plateau[coup.xFrom][coup.yFrom].p == ROI
	                                    && coup.yFrom > coup.yTo
										&& coup.yFrom - coup.yTo == 2;

	
	if (nouveau_coup_enregistre->grandRoque){
		Position new = partie->plateau[coup.xFrom][0];
		partie->plateau[coup.xFrom][0].p = VIDE;
		partie->plateau[coup.xFrom][0].c = BLANC;
		partie->plateau[coup.xTo][3].p = new.p;
		partie->plateau[coup.xTo][3].c = new.c;		
	} else if (nouveau_coup_enregistre->petitRoque){
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
	if(new.p == ROI){
		if(partie->player == BLANC){
			partie->Blanc.xRoi = coup.xTo;
			partie->Blanc.yRoi = coup.yTo;
		}else{
			partie->Noir.xRoi = coup.xTo;
			partie->Noir.yRoi = coup.yTo;
		}
	}

	// Promouvoir un pion	
	if (partie->plateau[coup.xTo][coup.yTo].p == PION){
		nouveau_coup_enregistre->promotion = promotion_pion(partie, coup);
		partie->plateau[coup.xTo][coup.yTo].p = nouveau_coup_enregistre->promotion;
	}
	// Détecter si échec au roi adverse
	nouveau_coup_enregistre->echec = est_echec(partie);

	if (partie->player == BLANC){
		partie->Noir.echec = nouveau_coup_enregistre->echec;
	}else{
		partie->Blanc.echec = nouveau_coup_enregistre->echec;			
	}

	// Détecter si échec et mat au roi adverse
	if (nouveau_coup_enregistre->echec){
		nouveau_coup_enregistre->mat = est_mat(partie);
		if (partie->player == BLANC){
			partie->Noir.mat = nouveau_coup_enregistre->mat;
		}else{
			partie->Blanc.mat = nouveau_coup_enregistre->mat;			
		}
	}
	
	// Mise à jour du temps du joueur
	clock_t end = clock();
	if (partie->player == BLANC)
	{
		partie->Blanc.timer += end - partie->debut_coup;
	}else{
		partie->Noir.timer += end - partie->debut_coup;
	}
	partie->debut_coup = clock();
	
			
	// Enregistrer le coup joué dans la fiche de match		
	if (partie->fiche_partie == NULL){
		partie->fiche_partie = nouveau_coup_enregistre;
		partie->dernier_coup_joue = nouveau_coup_enregistre;
	}else{
		partie->dernier_coup_joue->suivant = nouveau_coup_enregistre;
		partie->dernier_coup_joue = nouveau_coup_enregistre;		
	}

	// Changer de joueur
	partie->player = 1-partie->player;


}

/******************************************************************************
 * Nom de fonction : promotion_pion
 *
 * Description : Demande à l'opérateur en quelle pièce le pion est promu
 *
 * - Vérifier que la pièce est un pion sinon renvoyer la piece
 * - Vérifier que la destination est bien une ligne de fond sinon renvoyer la piece
 * - Demander la promotion au joueur
 * - Renvoyer la promotion
 *
 * Paramètres enrée :
 * Paramètre   Type        E/S   Description
 * ---------   ---------   ---   ----------------------------------------------
 * partie      Partie ptr   E    La partie en cours
 * coup        Coup         E    Le coup joué 
 * 
 * Retour : Piece : La promotion du pion 
 ******************************************************************************/
Piece promotion_pion(Partie *partie, Coup coup){

	// Vérifier que la pièce est un pion sinon renvoyer la piece
	if (partie->plateau[coup.xTo][coup.yTo].p != PION){
		return partie->plateau[coup.xTo][coup.yTo].p;
	}
	
	// Vérifier que la destination est bien une ligne de fond sinon renvoyer la piece
	if (coup.xTo != 0 && coup.xTo != MAX_CASE-1){
		return partie->plateau[coup.xTo][coup.yTo].p;
	}

	// Demander la promotion au joueur
	int temp = PION;
	int loop = 0;
	while(loop == 0){
		loop = 1;
		printf("Votre pion est promu, choissisez une piece pour le remplacer\n");
		printf("1-PION 2-TOUR 3-CAVALIER 4-FOU 5-DAME\n");
		scanf("%d",&temp);
		if(temp < 1 || temp > 5){
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
 * Description : Déroulement du jeux humain contre humain
 *
 * - Créer la partie dans l'état initiale
 * - Tant que pas d'echec et mat
 *   - Afficher le plateau de jeu
 *   - Afficher le temps restant au joueur 
 *   - Lire la définition du coup par le joueur
 *   - Vérifier validité du coup 
 *   - Déplacer les pièces
 *   - Vérifier état de échec et mat
 *  - Fin Tant que
 *  - Afficher le résultat de la partie  
 *  - Libérer l'espace mémoire utilisé par la partie
 *
 * Paramètres : Aucun
 * Retour : Aucun 
 ******************************************************************************/
void play_pvp(){
	// Créer la partie dans l'état initiale
	Partie partie = creer_partie();
	
	// Initialisation du code d'erreur de la verification du coup à Pas d'erreur.
	Coup coup_joueur;
	int code_erreur_verif = 0;
	int CoupAutoMax = 0;
		
	// AutoTest - Promotion pion blanc en B8
	// CoupAutoMax = 9;
	// Coup CoupAuto[9] = {{6, 0, 4, 0}, {1,1,3,1}, {4,0,3,1}, {0,1,2,2}, {3,1,2,1}, {2,2,4,3}, {2,1,1,1}, {1,7,3,7}, {1,1,0,1}};
	
	// AutoTest - Promotion pion noir en B1	
	// CoupAutoMax = 10;
	// Coup CoupAuto[10] = {{6, 0, 4, 0}, {1,1,3,1}, {7,0,5,0}, {3,1,4,0}, {5,0,5,7}, {4,0,5,0}, {6,2,4,2}, {5,0,6,0}, {7,1,5,2}, {6,0,7,0}} ;
	
	// AutoTest - Coup du berger
	// CoupAutoMax = 7;
	// Coup CoupAuto[7] = {{6, 4, 4, 4}, {1, 4, 3, 4}, {7, 5, 4, 2}, {1, 3, 2, 3}, {7,3,5,5 }, {1,2,3,2 }, {5,5,1,5}} ;

	// AutoTest - Kasparov vs Topalov 1999 - 1-0 par Abandon
	// 1.e4 d6 2.d4 Cf6 3.Cc3 g6 4.Fe3 Fg7 5.Dd2 c6 6.f3 b5 7.Cge2 Cfd7 8.Fh6 Fxh6 
    // 1.E4 D6 2.D4 CF6 3.CC3 G6 4.FE3 FG7 5.DD2 C6 6.F3 B5 7.CE2 CD7 8.FH6 FxH6 
    //                                                        XXX XXX  
    // 9.Dxh6 Fb7 10.a3 e5 11.O-O-O De7 12.Rb1 a6 13.Cc1 O-O-O 14.Cb3 exd4 15.Txd4 c5 16.Td1 Cb6 
    // 9.DxH6 FB7 10.A3 E5 11.O-O-O DE7 12.RB1 A6 13.CC1 O-O-O 14.CB3 exD4 15.TxD4 C5 16.TD1 CB6 
    // 
    // 17.g3 Rb8 18.Ca5 Fa8 19.Fh3 d5 20.Df4+ Ra7 21.The1 d4 22.Cd5 Cfxd5 23.exd5 Dd6 24.Txd4 cxd4 
    // 17.G3 RB8 18.CA5 FA8 19.FH3 D5 20.DF4+ RA7 21.TE1 D4 22.CD5 CxD5 23.exD5 DD6 24.TxD4 cxD4 
    //                                               XXX           xxxx
    // 25.Te7+ Rb6 26.Dxd4+ Rxa5 27.b4+ Ra4 28.Dc3 Dxd5 29.Ta7 Fb7 30.Txb7 Dc4 31.Dxf6 Rxa3 32.Dxa6+ Rxb4 
    // 25.TE7+ RB6 26.DxD4+ RxA5 27.B4+ RA4 28.DC3 DxD5 29.TA7 FB7 30.TxB7 DC4 31.DxF6 RxA3 32.DxA6+ RxB4 
    //
    // 33.c3+ Rxc3 34.Da1+ Rd2 35.Db2+ Rd1 36.Ff1 Td2 37.Td7 Txd7 38.Fxc4 bxc4 39.Dxh8 Td3 40.Da8 c3 
    // 33.C3+ RxC3 34.DA1+ RD2 35.DB2+ RD1 36.FF1 TD2 37.TD7 TxD7 38.FxC4 bxC4 39.DxH8 TD3 40.DA8 C3 
    // 
    // 41.Da4+ Re1 42.f4 f5 43.Rc1 Td2 44.Da7
    // 41.DA4+ RE1 42.F4 F5 43.RC1 TD2 44.DA7
	/*CoupAutoMax = 87;
	Coup CoupAuto[87] = {{6, 4, 4, 4}, {1, 3, 2, 3}, {6, 3, 4, 3}, {0, 6, 2, 5}, {7, 1, 5, 2}, {1, 6, 2, 6}, {7, 2, 5, 4}, {0, 5, 1, 6}, 
						 {7, 3, 6, 3}, {1, 2, 2, 2}, {6, 5, 5, 5}, {1, 1, 3, 1}, {7, 6, 6, 4}, {0, 1, 1, 3}, {5, 4, 2, 7}, {1, 6, 2, 7},
						 {6, 3, 2, 7}, {0, 2, 1, 1}, {6, 0, 5, 0}, {1, 4, 3, 4}, {7, 4, 7, 2}, {0, 3, 1, 4}, {7, 2, 7, 1}, {1, 0, 2, 0},
						 {6, 4, 7, 2}, {0, 4, 0, 2}, {7, 2, 5, 1}, {3, 4, 4, 3}, {7, 3, 4, 3}, {2, 2, 3, 2}, {4, 3, 7, 3}, {1, 3, 2, 1},
						 {6, 6, 5, 6}, {0, 2, 0, 1}, {5, 1, 3, 0}, {1, 1, 0, 0}, {7, 5, 5, 7}, {2, 3, 3, 3}, {2, 7, 4, 5}, {0, 1, 1, 0},
						 {7, 7, 7, 4}, {3, 3, 4, 3}, {5, 2, 3, 3}, {2, 1, 3, 3}, {4, 4, 3, 3}, {1, 4, 2, 3}, {7, 3, 4, 3}, {3, 2, 4, 3},
						 {7, 4, 1, 4}, {1, 0, 2, 1}, {4, 5, 4, 3}, {2, 1, 3, 0}, {6, 1, 4, 1}, {3, 0, 4, 0}, {4, 3, 5, 2}, {2, 3, 3, 3},
						 {1, 4, 1, 0}, {0, 0, 1, 1}, {1, 0, 1, 1}, {3, 3, 4, 2}, {5, 2, 2, 5}, {4, 0, 5, 0}, {2, 5, 2, 0}, {5, 0, 4, 1}, 
						 {6, 2, 5, 2}, {4, 1, 5, 2}, {2, 0, 7, 0}, {5, 2, 6, 3}, {7, 0, 6, 1}, {6, 3, 7, 3}, {5, 7, 7, 5}, {0, 3, 6, 3}, 
						 {1, 1, 1, 3}, {6, 3, 1, 3}, {7, 5, 4, 2}, {3, 1, 4, 2}, {6, 1, 0, 7}, {1, 3, 5, 3}, {0, 7, 0, 0}, {4, 2, 5, 2}, 
						 {0, 0, 4, 0}, {7, 3, 7, 4}, {5, 5, 4, 5}, {1, 5, 3, 5}, {7, 1, 7, 2}, {5, 3, 6, 3}, {4, 0, 1, 0}};
	*/
	// AutoTest - Computer-01- 1-0
	CoupAutoMax = 69;
	Coup CoupAuto[69] = {{6, 3, 4, 3}, {1, 3, 3, 3}, {6, 2, 4, 2}, {3, 3, 4, 2}, {6, 4, 4, 4}, {1, 1, 3, 1}, {6, 0, 4, 0}, {1, 2, 2, 2}, 
	 					 {7, 1, 5, 2}, {3, 1, 4, 1}, {5, 2, 6, 0}, {0, 6, 2, 5}, {4, 4, 3, 4}, {2, 5, 3, 3}, {7, 5, 4, 2}, {1, 4, 2, 4},
						 {7, 6, 5, 5}, {1, 0, 3, 0}, {7, 2, 3, 6}, {0, 3, 2, 1}, {6, 0, 7, 2}, {0, 2, 2, 0}, {7, 3, 6, 4}, {1, 7, 2, 7}, 
						 {3, 6, 5, 4}, {2, 0, 4, 2}, {6, 4, 4, 2}, {0, 1, 1, 3}, {7, 2, 5, 1}, {0, 5, 1, 4}, {7, 0, 7, 2}, {0, 4, 0, 6}, 
						 {7, 4, 7, 6}, {0, 5, 0, 2}, {4, 2, 6, 4}, {2, 2, 3, 2}, {5, 5, 6, 3}, {2, 1, 2, 2}, {6, 4, 3, 7}, {2, 2, 4, 0}, 
						 {5, 1, 3, 2}, {1, 3, 3, 2}, {4, 3, 3, 2}, {3, 3, 5, 4}, {6, 5, 5, 4}, {1, 4, 3, 2}, {3, 7, 1, 5}, {0, 6, 0, 7}, 
						 {1, 5, 5, 5}, {0, 2, 0, 5}, {5, 5, 4, 4}, {4, 0, 1, 3}, {6, 3, 5, 1}, {3, 2, 2, 1}, {7, 5, 7, 3}, {1, 3, 1, 5}, 
						 {7, 3, 7, 5}, {1, 5, 1, 0}, {7, 5, 0, 5}, {0, 0, 0, 5}, {5, 1, 4, 3}, {3, 0, 4, 0}, {4, 3, 2, 4}, {2, 1, 5, 4}, 
						 {7, 6, 7, 7}, {5, 4, 7, 2}, {2, 4, 0, 5}, {1, 0, 5, 4}, {4, 4, 1, 7}};
	
	
		
	// Tant que pas d'échec et mat
	int CoupAutoIter = 0;
	while(!partie.Blanc.mat && !partie.Noir.mat){		
		// Afficher le plateau de jeu
		afficher_fiche_partie(partie.fiche_partie);
		afficher_plateau(&partie);
		
		// Afficher le temps restant au joueur 
		if(partie.player == BLANC)
		{
			printf("Voici le temps qu'il vous reste pour jouer votre coup : %f", partie.Blanc.timer);
		}
		else
		{
			printf("Voici le temps qu'il vous reste pour jouer votre coup : %f", partie.Noir.timer);
		}
		
		// Lire la définition du coup par le joueur
		if (code_erreur_verif != 0){
			printf("Code erreur : %d\n", code_erreur_verif);
			printf("\n *** ATTENTION : Le coup proposé n'est pas valide !\n Rejouez !\n");
		}
		if (partie.player == BLANC){
			printf("Les blancs jouent\n");
			if (partie.Blanc.echec){
				printf("Echec au roi\n");
			}
		}else{
			printf("Les noirs jouent\n");
			if (partie.Noir.echec){
				printf("Echec au roi\n");
			}	
		}	
		if (CoupAutoIter < CoupAutoMax){
			coup_joueur = CoupAuto[CoupAutoIter];
			CoupAutoIter ++;
		}else{	
			coup_joueur = proposition_joueur();
		}

		// Vérifier validité du coup
		code_erreur_verif = verif_coup(&partie, coup_joueur, 1);
		
		if(code_erreur_verif == 0){
			// Déplacer les pièces
			jouer_coup(&partie, coup_joueur);		
		}
	}
	
	// Afficher le résultat de la partie
	printf("**** Fin de la partie ****\n");
	int vainceur = 1 - partie.player;
	partie.player = BLANC;
	afficher_plateau(&partie);
	printf("Echec et mat, victoire de %s\n", vainceur == BLANC?"Blanc":"Noir" );
	afficher_fiche_partie(partie.fiche_partie);
	
	// Libérer l'espace mémoire utilisé par la partie
	liberer_partie(partie);
}

/******************************************************************************
 * Nom de fonction : main
 *
 * Description : Programme principal
 *
 * PDL:          - Lancer le jeu humain contre humain
 * Paramètres: Aucun
 * Retour: Aucun 
 ******************************************************************************/
int main(){
	play_pvp();
}
