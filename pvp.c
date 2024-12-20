#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pvp.h"



//Fonction permettant de créer un maillion pour la liste chainé d'enregistrement de coup
Fiche *creer_maillon()
{
	Fiche *nv_maillon = malloc(sizeof(Fiche));
	CHECK_MALLOC(nv_maillon);
	nv_maillon->suivant = NULL;
	return nv_maillon;
}

//Permet de créer le plateau
Position **creer_plateau()
{
	//On alloue la mémoire dynamique pour le tableau de pieces, en verifiant leur bon fonctionnement
    Position **tab = malloc(sizeof(*tab) * MAX_CASE);
	CHECK_MALLOC(tab);
    for(int i = 0; i < MAX_CASE; i++){
        *(tab + i) = malloc(sizeof(**tab) * MAX_CASE);
		CHECK_MALLOC(*(tab + i));
	}

	//On initialise les pions Noir et Blanc
    for(int i = 0; i < MAX_CASE; i++){
        tab[1][i].p = PION;
        tab[1][i].c = NOIR;
        tab[6][i].p = PION;
        tab[6][i].c = BLANC;
    }
	//Puis les 5 premieres pieces : Tour, Cavalier, Fou, Reine, et le Roi
    Piece temp = TOUR;
    int j;
    for(j = 0; j < (MAX_CASE / 2) + 1; j++){
        tab[0][j].p = temp;
        tab[0][j].c = NOIR;
        tab[7][j].p = temp;
        tab[7][j].c = BLANC;
        temp++;
        
    }
	//Et enfin les trois dernieres
    temp = FOU;
    for(int i = j; i < MAX_CASE + 1; i++){
        tab[0][i].p = temp;
        tab[0][i].c = NOIR;
        tab[7][i].p = temp;
        tab[7][i].c = BLANC;
        temp --;
    }
    return tab;
}


char piece2char(Position case_courante)
{
	switch (case_courante.p)
		{
			case PION: 
				return((case_courante.c == BLANC )? 'P' : 'p' );
			
			case TOUR: 
				return((case_courante.c == BLANC )? 'R' : 'r' );
				
			case CAVALIER:
				return((case_courante.c == BLANC )? 'N' : 'n' );
				
			case FOU: 
				return((case_courante.c == BLANC )? 'B' : 'b' );
			
			case REINE:
				return((case_courante.c == BLANC )? 'Q' : 'q' );
			
			case ROI:
				return((case_courante.c == BLANC )? 'K' : 'k' );
			default :
				return(' ');
		}
}

void affichage(Partie *partie)
{
    Position **plateau = partie->plateau;
    printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n");
	if (partie->player == BLANC)
	{
		for (int i = 0; i < MAX_CASE; i++)
		{
			printf(" ");
			for (int j = 0; j < MAX_CASE; j++)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|░░░░░");   
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
					printf("|░░%c░░", piece2char(plateau[i][j]));   
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
					printf("|░░░░░");   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("|\n");
			printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n\n");
		}
		printf("    A     B     C     D     E     F     G     H\n");
	}
	else 
	{
		for (int i = MAX_CASE-1; i >= 0; i--)
		{
			printf(" ");
			for (int j = MAX_CASE-1; j >= 0; j--)
			{
				if ((i+j) % 2 == 0)
				{
					printf("|░░░░░");   
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
					printf("|░░%c░░", piece2char(plateau[i][j]));   
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
					printf("|░░░░░");   
				}
				else
				{
					printf("|     ");   
				}
			}
			printf("\n");
			printf(" +-----+-----+-----+-----+-----+-----+-----+-----+\n\n");
		}
		printf("    H     G     F     E     D     C     B     A\n");
	}
}


//Permet d'enregistrer le coup du joueur
Coup proposition_joueur()
{
	Coup coup;
	int n;
	char c;
	int loop = 1;
	//Tant que le coup n'est pas dans la grille, on ne le valide pas 
	while(loop){
		loop = 0;
		//Enregistre la position de départ
		printf("Donnez la position de la piece que vous voulez jouer :\n");
		scanf("%c", &c);
		scanf("%d", &n); 
		//Permet de traduire les coordonnées joueur en coordonnées réel
		coup.xFrom = MAX_CASE - n;
		coup.yFrom = c-'A';
		while ((getchar()) != '\n'); //Permet de clear le buffer pour eviter qu'un scanf soit ignoré
		//Enregistre la posotion d'arrivée
		printf("Donnez la position de la case sur laquelle déplacer la pièce :\n");
		scanf("%c", &c);
		scanf(" %d", &n);
		coup.xTo = MAX_CASE - n;
		coup.yTo = c-'A';
		if(coup.xFrom < 0 || coup.xTo > 7 || coup.yFrom < 0 || coup.yTo > 7){ //Verifie que le coup se trouve dans la grille
			printf("Votre coup est invalide, essayer encore !\n");
			while ((getchar()) != '\n');
			loop = 1;
		}
		while ((getchar()) != '\n');
	}
	return coup;
}

//Fonction qui créer un tableau dynamique, afin de connaitre la position des rois a tout instant
int *king()
{
	int *tab = malloc(sizeof(int) * 4);
	CHECK_MALLOC(tab);
	tab[0] = 7;
	tab[1] = 4;
	tab[2] = 0;
	tab[3] = 4;
	return tab;
}

//Cette fonction vérifie la validité vertical d'un coup
int verif_vert(Partie *current, Coup c)
{
	if(c.yFrom != c.yTo) // Si les y sont différents, ça ne peux pas être vertical
		return 0;
	if(c.xTo > c.xFrom){//Pour connaitre le sens de parcour
		for(int i = c.xFrom + 1; i < c.xTo; i++){
			if(current->plateau[i][c.yFrom].p != VIDE)//Si il y a un pion sur la trajectoire, le coup n'est pas possible
				return 0;
		}
	}
	else{
		for(int i = c.xFrom -1; i > c.xTo; i--){
			if(current->plateau[i][c.yFrom].p != VIDE)
				return 0;
		}
	}
	//Verifie que si la case d'arrive n'est pas vide, il est de la couleur ennemie
	if((current->plateau[c.xTo][c.yTo].p != VIDE) && (current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c))
		return 0;
	return 1;
}

//Cette fonction est la même que la précedente, mais pour la vérification horizontal
int verif_hor(Partie *current, Coup c){
	if(c.xFrom != c.xTo)
		return 0;
	
	if(c.yTo > c.yFrom){
		for(int i = c.yFrom + 1; i < c.yTo; i++){
			if(current->plateau[c.xFrom][i].p != VIDE)
				return 0;
		}
	}
	else{
		for(int i = c.yFrom - 1; i > c.yTo; i--){
			if(current->plateau[c.xFrom][i].p != VIDE)
				return 0;
		}
	}
	if(current->plateau[c.xTo][c.yTo].p != VIDE && current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c)
		return 0;
	return 1;
}

//Cette fonction verifie la validité d'un coup en diagonal
int verif_diag(Partie *current, Coup c)
{
	int vect_x = c.xFrom - c.xTo;//Calcule la coordonnée en x du vecteur du coup
	int vect_y = c.yFrom - c.yTo;//Calcule la coordonnée en y du vecteur du coup
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));// Calcule la norme de ce vecteur 
	if(vect_x == 0)//Verifie que vect_x n'est pas égale a 0, pour eviter une erreur
		return 0;
    int dir = (c.yFrom - c.yTo) / (c.xFrom - c.xTo);//Calcule le coefficiant directeur de la droite porter pas notre vecteur
    if(abs(dir) != 1)//Si le coefficiant est different de 1 ou -1, ce n'est pas une diagonal;
        return 0;

	//Permet de déterminer le sens de parcour de la diagonale parmi les 4 possible 
    int mult_x = 1;
    int mult_y = 1;
    if(c.xFrom > c.xTo)
        mult_x = -1;
    if(c.yFrom > c.yTo)
        mult_y = -1;
	
	//Initialisaion des compteurs
    int count_x = c.xFrom;
    int count_y = c.yFrom;
    for(int i = 0; i < norme ; i++){ //Parcour de la diagonale
        count_x = count_x + (1 * mult_x);
        count_y = count_y + (1 * mult_y);
		if(count_x == c.xTo && count_y == c.yTo)//Arrete le parcour si on arrive
			break;
		if(current->plateau[count_x][count_y].p != VIDE){//Si la case n'est pas vide, le coup n'est pas possible
            return 0;
        }
    }
	if((current->plateau[c.xTo][c.yTo].p != VIDE) && (current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c))
		return 0;

    return 1;
}

//Permet de veifier le déplacement d'un pion
int verif_pion(Partie *current, Coup c)
{
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	if(verif_vert(current, c) == 0){
		//Si le mouvement demandé est en vertical est pas possible, c'ets que l'on veux manger en diagonale
		if((verif_diag(current, c) == 0) || (current->plateau[c.xTo][c.yTo].p == VIDE) || (norme > 1))
			return 0;
		return 1;
	}
	if(norme > 1){
		//Si on veux faire un deplacement de plus de 1, on doit etre sur notre case de départ
		if(((c.xFrom == 1 && current->player == NOIR) || (c.xFrom == 6 && current->player == BLANC)) && norme == 2)
			return 1;
		return 0;
		}
	
	return 1;
}

//Combinbe la vérification vertical et horizontal
int verif_tour(Partie *current, Coup c)
{
	return (verif_hor(current, c) || verif_vert(current, c));
}

//Combine la vérification de la tour et celle diagonale
int verif_reine(Partie *current, Coup c)
{
	return (verif_tour(current, c) || verif_diag(current, c));
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

int verif_roi(Partie *current, Coup c)
{
	//ici on vérifie juste que le deplacement sois de 1 case
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
		if(norme > 1)
			return 0;
	return 1;
}

//Cette fonction regroupe toutes les vérifications
int verif_coup(Partie *current, Coup c)
{
	Piece temp = current->plateau[c.xFrom][c.yFrom].p;
	//Selon la pieces, on appel une fonction particulière
	switch(temp){
		case PION:
			if(verif_pion(current, c) == 0)
				return 0;
		break;
		case TOUR:
			if(verif_tour(current, c) == 0)
				return 0;
		break;
		case CAVALIER:
			if(verif_cav(current, c) == 0)
				return 0;
		break;
		case FOU:
			if(verif_diag(current, c) == 0)
				return 0;
		break;
		case ROI:
			if(verif_roi(current, c) == 0)
				return 0;
		break;
		case REINE:
			if(verif_reine(current, c) == 0)
				return 0;
		break;
		case VIDE:
			return 0;
		break;
	}
	//Si la case d'arrivé n'est pas vide, soit c'est de notre coleur donc impossible, sois il y a une piece a manger
	if(current->plateau[c.xTo][c.yTo].p != VIDE && current->plateau[c.xTo][c.yTo].c == current->plateau[c.xFrom][c.yFrom].c){
		return 0;
	return 2;
	}
	return 1;
}

//Cette fonction renvoie 1 si la case de coord x, y, et ce couleur c,  est en échec
int est_echec(Partie *current, int x, int y, Couleur c, Coup *ech)
{
	Coup temp;
	for(int i = 0; i < MAX_CASE; i++){
		for(int j = 0; j < MAX_CASE; j++){
			//On parcoure toute la grille, et on créer un coup entre la case balayé et notre case a vérifier
			temp.xFrom = i;
			temp.yFrom = j;
			temp.xTo = x;
			temp.yTo = y;
			if((current->plateau[i][j].p != VIDE) && current->plateau[i][j].c != c && verif_coup(current, temp) != 0){
					//Si le coup est possible, et qu'il ne s'agis pas de la même couleur, on renvoie 1 et on note le coup dans ech
					*ech = temp;
					return 1;
			}
		}

	}
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


//Vérifie si le roi est en echec est mat
int est_mat(Partie *current, int *k, Coup *ech)
{
	int vect_x = ech->xFrom - ech->xTo;
	int vect_y = ech->yFrom - ech->yTo;
	int norme = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	int x = k[0];
	int y = k[1]; 
	if(current->player == NOIR){
		x = k[2];
		y = k[3];
	}
	//Le but ici est de balayé toute les case autour du roi pour determiner si le roi peux s'en sortir de lui même
	//On créer doncdes bornes pour savoir ou balayé selon les coord du roi
	int sup = x + 1;
	int inf = x - 1;
	if(x == 0)
		inf = 0;
	if(x == 7)
		sup = 7;
	for(int i = inf; i < sup + 1; i++){
		if(est_echec(current, x, y, current->player, ech) == 0)
			return 0;
	}

	sup = y + 1;
	inf = y - 1;
	if(y == 0)
		inf = 0;
	if(y == 7)
		sup = 7;
	for(int i = inf; i < sup + 1; i++){
		if(est_echec(current, x, y, current->player, ech) == 0)
			return 0;
	}
	
	//Si le roi ne peux pas s'en sortir, on regarde si une pieces peux venir couper la trajectoire du coup qui met le roi en echec
	int **traj = trajectoire(*ech);
	Coup temp = *ech;
	//si c'est un cavalier, le seul moyen est de tuer le cavalier
	if(current->plateau[temp.xFrom][temp.yFrom].p == CAVALIER && est_echec(current, temp.xFrom, temp.yFrom, current->plateau[temp.xFrom][temp.yFrom].c, ech) == 0)
		return 1;
	Couleur col = 1 - current->plateau[temp.xFrom][temp.yFrom].c;
	//Si non, on parcour la trajectoire et on regarde si la case de la trajectoire est en "échec", c'est a dire si on peux aller dessus
	for(int i = 0; i < norme; i++){
		if(est_echec(current, traj[i][0], traj[i][1], col, ech) == 1)
			return 0;
	}
	*ech = temp;

	return 1;
}

//Cette fonction permet d'appliquer un coup
int jouer_coup(Partie *current, Coup c, int *k, Coup *ech, Fiche *nv_maillon){
	Position new = current->plateau[c.xFrom][c.yFrom];
	Position temp = {VIDE, BLANC};
	int x = k[2];
	int y = k[3];
	if(current->player == BLANC){
		x = k[0];
		y = k[1];
	}
	int prise = verif_coup(current, c); //Sauvegarde la possibilité du coup
	switch(prise){ //Selon si le coup est impossible, possible et possible en mangeant une piece
		case 0:
			printf("Coup impossible\n");
			return 0;
		break;
		case 1:
			//Pour un coup simple, remplace la case de départ par une case vide, et la case d'arrivé par notre piece
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xFrom][c.yFrom].c = BLANC;
			current->plateau[c.xTo][c.yTo].p = new.p;
			current->plateau[c.xTo][c.yTo].c = new.c;
		break;
		case 2:
			//Ici, on supprime la piece ennemie sur la case d'arriver avant 
			temp = current->plateau[c.xTo][c.yTo];
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xFrom][c.yFrom].c = BLANC;
			current->plateau[c.xTo][c.yTo].p = new.p;
			current->plateau[c.xTo][c.yTo].c = new.c;
		break;
	}
	if(est_echec(current, x, y, current->plateau[x][y].c, ech) == 1){ // Si le coup qu'on vien de jouer est impossible car met le roi en échec
		printf("Impossible, votre roi est en echec\n"); 
		//On annule le coup
		current->plateau[c.xTo][c.yTo].p = temp.p;
		current->plateau[c.xTo][c.yTo].p = temp.c;
		current->plateau[c.xFrom][c.yFrom].p = new.p;
		current->plateau[c.xFrom][c.yFrom].c = new.c;
		return 0;
	}
	//Actualise les coord des rois
	if(new.p == ROI){
		if(current->player == BLANC){
			k[0] = c.xTo;
			k[1] = c.yTo;
		}
		else{
			k[2] = c.xTo;
			k[3] = c.yTo;
		}
	}
	//Permet de noter le coup dans la fiche (Fonctionnalité par terminer: beuguer)
	Fiche *maillon_suivant;
	maillon_suivant = creer_maillon();
	nv_maillon->suivant = maillon_suivant;
	nv_maillon->piece = current->plateau[c.xTo][c.yTo].p;
	nv_maillon->coup = c;
	nv_maillon->prise = prise;
	return 1;
}

//Permet de gérer la promotion des pions 
void prom(Partie *current){
	int temp;
	int loop = 0;
	for(int i = 0; i < MAX_CASE; i++){
		//On regarde une extrémité, si il y a un pion d'une bonne couleur, on demande au joueur de choisir sa promotion
		if(current->plateau[0][i].p == PION && current->plateau[0][i].c == BLANC){
			while(loop == 0){
				loop = 1;
				printf("Votre pion est promu, choissisez une piece pour le remplacer\n");
				printf("1-PION 2-TOUR 3-CAVALIER 4-FOU 5-REINE\n");
				scanf("%d",&temp);
				if(temp < 1 || temp > 5){
					printf("Erreur de saisi\n");
					loop = 0;
				}
			}
			current->plateau[0][i].p = temp;
		}
	}

		for(int i = 0; i < MAX_CASE; i++){
		if(current->plateau[7][i].p == PION && current->plateau[7][i].c == NOIR){
			while(loop == 0){
				loop = 1;
				printf("Votre pion est promu, choissisez une piece pour le remplacer\n");
				printf("1-PION 2-TOUR 3-CAVALIER 4-FOU 5-REINE\n");
				scanf("%d",&temp);
				if(temp < 1 || temp > 5){
					printf("Erreur de saisi\n");
					loop = 0;
				}
			}
			current->plateau[7][i].p = temp;
		}
	}
}


//Cette fonction permet d'afficher la fiche en fin de partie, pas terminer beugué 
void feuille_partie(Fiche *premier_tour)
{
	printf("Voici votre fiche de partie :\n");
	Fiche *tour = premier_tour;
	int i = 0;
	while (tour != NULL)
	{
		if (i / 2 == 0)
		{
			printf("BLANC \t ");
		}
		else 
		{
			printf("NOIR \t ");
		}
		i++;
		switch (tour->piece)
		{
			case TOUR: 
				printf("T ");
				
			case CAVALIER:
				printf("C ");
				
			case FOU: 
				printf("F ");
				
			case REINE:
				printf("D ");
			
			case ROI:
				printf("R ");
		}
		if (tour->prise == 2)
		{
			printf("X ");
		}
		printf("%c %d\n",65 + tour->coup.yTo, tour->coup.xTo + 1);
		tour = tour->suivant;		
	}
}

//Libère l'espace pris par la liste chainé de la fiche
void supprimer_feuille(Fiche *feuille)
{
	Fiche *efface = feuille;
	while(feuille->suivant != NULL)
	{
		feuille = efface->suivant;
		free(efface);
	}
}

//Algorithme de Jeux
void play_pvp()
{
	//Creer le plateur et les variables 
	Coup *ech = malloc(sizeof(Coup));
	CHECK_MALLOC(ech);
	Fiche *maillon = malloc(sizeof(Fiche));
	Fiche *fiche_partie = maillon;
	Partie test;
    test.plateau = creer_plateau();
    test.player = BLANC;
	int *k = king();
	Coup temp;
	int loop = 0;
	int x = k[2];
	int y = k[3];
	if(test.player == BLANC){
		x = k[0];
		y = k[1];
	}
	while(loop == 0){
		//tant que aucun roi n'est en echet et mat
		x = k[2];
		y = k[3];
		if(test.player == BLANC){
			x = k[0];
			y = k[1];
		}
			affichage(&test);
			if(est_echec(&test, x, y, test.player, ech) && est_mat(&test, k, ech)){
				loop = 1;
				break;
			}
			//on demande un coup
			temp = proposition_joueur();
			if(verif_coup(&test, temp) == 0){ //On le verifie
				printf("Coup non Valide\n");
			}
			else{
				if(jouer_coup(&test, temp, k, ech, maillon) == 1){//On le joue 
					//on change de joueur et on verifie la promotions
					maillon = maillon->suivant;
					prom(&test);
					test.player = 1-test.player;
				}
			}
	}
	//Fin de partie et libération de la mémoire
	printf("Echec et mat, victoire de %d\n", test.player);
	feuille_partie(fiche_partie);
	supprimer_feuille(fiche_partie);
	for(int i = 0; i < MAX_CASE; i++){
		free(*((test.plateau) + i));
	}
	free(test.plateau);
	free(k);

}
