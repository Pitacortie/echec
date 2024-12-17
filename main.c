#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CASE 8

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


Position **creer_plateau(){
    Position **tab = malloc(sizeof(*tab) * MAX_CASE);
    for(int i = 0; i < MAX_CASE; i++)
        *(tab + i) = malloc(sizeof(**tab) * MAX_CASE);

    for(int i = 0; i < MAX_CASE; i++){
        tab[1][i].p = PION;
        tab[1][i].c = NOIR;
        tab[6][i].p = PION;
        tab[6][i].c = BLANC;
    }
    Piece temp = TOUR;
    int j;
    for(j = 0; j < (MAX_CASE / 2) + 1; j++){
        tab[0][j].p = temp;
        tab[0][j].c = NOIR;
        tab[7][j].p = temp;
        tab[7][j].c = BLANC;
        temp++;
        
    }
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
			printf("\n");
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


Coup proposition_joueur()
{
	Coup coup;
	int n;
	char c;
	int loop = 1;
	while(loop){
		loop = 0;
		printf("Donnez la position de la piece que vous voulez jouer :\n");
		scanf("%c", &c);
		scanf("%d", &n); 
		coup.xFrom = MAX_CASE - n;
		coup.yFrom = c-'A';
		while ((getchar()) != '\n');
		printf("Donnez la position de la case sur laquelle déplacer la pièce :\n");
		scanf("%c", &c);
		scanf(" %d", &n);
		coup.xTo = MAX_CASE - n;
		coup.yTo = c-'A';
		if(coup.xFrom < 0 || coup.xTo > 7 || coup.yFrom < 0 || coup.yTo > 7){
			printf("Votre coup est invalide, essayer encore !\n");
			while ((getchar()) != '\n');
			loop = 1;
		}
		while ((getchar()) != '\n');
	}
	return coup;
}

int *king(){
	int *tab = malloc(sizeof(int) * 4);
	tab[0] = 7;
	tab[1] = 4;
	tab[2] = 0;
	tab[3] = 4;
	return tab;
}
int verif_vert(Partie *current, Coup c){
	if(c.yFrom != c.yTo)
		return 0;
	if(c.xTo > c.xFrom){
		for(int i = c.xFrom + 1; i < c.xTo; i++){
			if(current->plateau[i][c.yFrom].p != VIDE){
				return 0;
			}

		}
	}
	else{
		for(int i = c.xFrom -1; i > c.xTo; i--){
			if(current->plateau[i][c.yFrom].p != VIDE){
				return 0;
			}

		}
	}
	if((current->plateau[c.xTo][c.yTo].p != VIDE) && (current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c))
		return 0;
	return 1;
}

int verif_hor(Partie *current, Coup c){
	if(c.xFrom != c.xTo)
		return 0;
	
	if(c.yTo > c.yFrom){
		for(int i = c.yFrom + 1; i < c.yTo; i++){
			if(current->plateau[c.xFrom][i].p != VIDE){
				return 0;
			}

		}
	}
	else{
		for(int i = c.yFrom - 1; i > c.yTo; i--){
			if(current->plateau[c.xFrom][i].p != VIDE){
				return 0;
			}

		}
	}
	if(current->plateau[c.xTo][c.yTo].p != VIDE && current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c)
		return 0;
	return 1;
}

int verif_diag(Partie *current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	if((c.xFrom - c.xTo) == 0)
		return 0;
    int dir = (c.yFrom - c.yTo) / (c.xFrom - c.xTo);
    if(abs(dir) != 1)
        return 0;

    int mult_x = 1;
    int mult_y = 1;
    if(c.xFrom > c.xTo)
        mult_x = -1;
    if(c.yFrom > c.yTo)
        mult_y = -1;

    int count_x = c.xFrom;
    int count_y = c.yFrom;
    for(int i = 0; i < norme ; i++){ 
        count_x = count_x + (1 * mult_x);
        count_y = count_y + (1 * mult_y);
		if(count_x == c.xTo && count_y == c.yTo)
			return 1;
		if(current->plateau[count_x][count_y].p != VIDE){
            return 0;
        }
    }
	if((current->plateau[c.xTo][c.yTo].p != VIDE) && (current->plateau[c.xFrom][c.yFrom].c == current->plateau[c.xTo][c.yTo].c))
		return 0;

    return 1;
}

int verif_pion(Partie *current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	if(verif_vert(current, c) == 0){
		if((verif_diag(current, c) == 0) || (current->plateau[c.xTo][c.yTo].p == VIDE) || (norme > 1))
			return 0;
		return 1;
	}
	if(norme > 1){
		if(((c.xFrom == 1 && current->player == NOIR) || (c.xFrom == 6 && current->player == BLANC)) && norme == 2)
			return 1;
		return 0;
		}
	
	return 1;
}

int verif_tour(Partie *current, Coup c){
	return (verif_hor(current, c) || verif_vert(current, c));
}

int verif_reine(Partie *current, Coup c){
	return (verif_tour(current, c) || verif_diag(current, c));
}

int verif_cav(Partie *current, Coup c){
	int dx = abs(c.xTo - c.xFrom);
	int dy = abs(c.yTo - c.yFrom);
	if((dx == 2 && dy == 1) || (dy == 2 && dx == 1)){
		if(current->plateau[c.xTo][c.yTo].p == VIDE || current->plateau[c.xTo][c.yTo].c != current->plateau[c.xFrom][c.yFrom].c)
			return 1;
	}
	return 0;
}

int verif_roi(Partie *current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
		if(norme > 1)
			return 0;
	return 1;
}

int verif_coup(Partie *current, Coup c){
	Piece temp = current->plateau[c.xFrom][c.yFrom].p;
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
	if(current->plateau[c.xTo][c.yTo].p != VIDE && current->plateau[c.xTo][c.yTo].c == current->plateau[c.xFrom][c.yFrom].c){
		return 0;
	return 2;
	}
	return 1;
}

int est_echec(Partie *current, int x, int y, Couleur c, Coup *ech){
	Coup temp;
	for(int i = 0; i < MAX_CASE; i++){
		for(int j = 0; j < MAX_CASE; j++){
			temp.xFrom = i;
			temp.yFrom = j;
			temp.xTo = x;
			temp.yTo = y;
			if((current->plateau[i][j].p != VIDE) && current->plateau[i][j].c != c && verif_coup(current, temp) != 0){
					*ech = temp;
					return 1;
			}
		}

	}
	return 0;
}

int est_col(int v1_x, int v1_y, int v2_x, int v2_y){
	return (((v1_x * v2_y) - (v1_y * v2_x)) == 0);
}


int **trajectoire(Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int bis_x;
	int bis_y;
	int loop = 0;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	int **res = malloc(sizeof(*res) * norme);
	for(int i = 0; i < norme; i++)
		*(res + i) = malloc(sizeof(int) * 2);

	for(int x = c.xFrom; x < c.xTo; x++){
		for(int y = c.yFrom; y < c.yTo; y++){
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


int est_mat(Partie *current, int *k, Coup *ech){
	int vect_x = ech->xFrom - ech->xTo;
	int vect_y = ech->yFrom - ech->yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	int x = k[0];
	int y = k[1]; 
	if(current->player == NOIR){
		x = k[2];
		y = k[3];
	}
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
	
	int **traj = trajectoire(*ech);
	Coup temp = *ech;
	if(current->plateau[temp.xFrom][temp.yFrom].p == CAVALIER && est_echec(current, temp.xFrom, temp.yFrom, current->plateau[temp.xFrom][temp.yFrom].c, ech) == 0)
		return 1;
	
	Couleur col = 1 - current->plateau[temp.xFrom][temp.yFrom].c;
	for(int i = 0; i < norme; i++){
		if(est_echec(current, traj[1][0], traj[i][1], col, ech) == 1)
			return 0;
	}
	*ech = temp;

	return 1;
}


int jouer_coup(Partie *current, Coup c, int *k, Coup *ech){
	Position new = current->plateau[c.xFrom][c.yFrom];
	Position temp = {VIDE, BLANC};
	int x = k[2];
	int y = k[3];
	if(current->player == BLANC){
		x = k[0];
		y = k[1];
	}
		switch(verif_coup(current, c)){
		case 0:
			printf("Coup impossible\n");
			return 0;
		break;
		case 1:
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xFrom][c.yFrom].c = BLANC;
			current->plateau[c.xTo][c.yTo].p = new.p;
			current->plateau[c.xTo][c.yTo].c = new.c;
		break;
		case 2:
			temp = current->plateau[c.xTo][c.yTo];
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xFrom][c.yFrom].c = BLANC;
			current->plateau[c.xTo][c.yTo].p = new.p;
			current->plateau[c.xTo][c.yTo].c = new.c;
		break;
	}
	if(est_echec(current, x, y, current->plateau[x][y].c, ech) == 1){
		printf("Impossible, votre roi est en echec\n");
		current->plateau[c.xTo][c.yTo].p = temp.p;
		current->plateau[c.xTo][c.yTo].p = temp.c;
		current->plateau[c.xFrom][c.yFrom].p = new.p;
		current->plateau[c.xFrom][c.yFrom].c = new.c;
		return 0;
	}
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
	return 1;
}

void prom(Partie *current){
	int temp;
	int loop = 0;
	for(int i = 0; i < MAX_CASE; i++){
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


int main(){
	Coup *ech = malloc(sizeof(Coup));
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
		x = k[2];
		y = k[3];
		if(test.player == BLANC){
			x = k[0];
			y = k[1];
		}
			affichage(&test);
			temp = proposition_joueur();
			if(verif_coup(&test, temp) == 0){
				printf("Coup non Valide\n");
			}
			else{
				if(jouer_coup(&test, temp, k, ech) == 1){
					prom(&test);
					test.player = 1-test.player;
				}
			}
		if(est_echec(&test, x, y, test.player, ech) && est_mat(&test, k, ech))
			loop = 1;
		
	}
	for(int i = 0; i < MAX_CASE; i++){
		
		free(*((test.plateau) + i));
	}
	free(test.plateau);
	free(k);
    return 1;

}
