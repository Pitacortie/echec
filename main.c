#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CASE 8

enum piece { VIDE, PION, TOUR, CAVALIER, FOU, REINE, ROI };
typedef enum piece Piece;

enum couleur { BLANC, NOIR };
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

struct fiche
{
	Piece piece;
	Coup coup;
	Bool prise;
	struct fiche *suivant;
}Fiche;	

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
int verif_vert(Partie current, Coup c){
	if(c.yFrom != c.yTo)
		return 0;

	if(c.xTo < c.xFrom){
		for(int i = c.xFrom; i < c.xTo; i++){
			if(current.plateau[i][c.yFrom].p != VIDE){
				return 0;
			}

		}
	}
	else{
		for(int i = c.xFrom; i > c.xTo; i--){
			if(current.plateau[i][c.yFrom].p != VIDE){
				return 0;
			}

		}
	}
	return 1;
}

int verif_hor(Partie current, Coup c){
	if(c.xFrom != c.xTo)
		return 0;
	
	if(c.yTo < c.yFrom){
		for(int i = c.yFrom; i < c.yTo; i++){
			if(current.plateau[c.xFrom][i].p != VIDE){
				return 0;
			}

		}
	}
	else{
		for(int i = c.yFrom; i > c.yTo; i--){
			if(current.plateau[c.xFrom][i].p != VIDE){
				return 0;
			}

		}
	}
	return 1;
}

int verif_diag(Partie current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	if((c.xFrom - c.xTo) == 0)
		return 0;
    int dir = (c.yFrom - c.yTo) / (c.xFrom - c.xTo);
	printf("%d\n", dir);
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
    for(int i = 0; i < norme; i++){ 
        count_x = count_x + (1 * mult_x);
        count_y = count_y + (1 * mult_y);
        if(current.plateau[count_x][count_y].p != VIDE){
				if(current.plateau[count_x][count_y].c == current.player)
            		return 0;
			return 1;
        }
    }

    return 1;
}

int verif_pion(Partie current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
	if(verif_vert(current, c) == 0){
		if((verif_diag(current, c) == 0) || (current.plateau[c.xTo][c.yTo].p == VIDE) || (norme > 1))
			return 0;
		return 1;
	}
	if(norme > 1){
		if(((c.xFrom == 1 && current.player == NOIR) || (c.xFrom == 6 && current.player == BLANC)) && norme == 2)
			return 1;
		return 0;
		}
	
	return 1;
}

int verif_tour(Partie current, Coup c){
	return (verif_hor(current, c) || verif_vert(current, c));
}

int verif_reine(Partie current, Coup c){
	return (verif_tour(current, c) && verif_diag(current, c));
}

int verif_cav(Partie current, Coup c){
	int dx = abs(c.xTo - c.xFrom);
	int dy = abs(c.yTo - c.yFrom);
	if((dx == 2 && dy == 1) || (dy == 2 && dx == 1)){
		if(current.plateau[c.xTo][c.yTo].p == VIDE)
			return 1;
	}
	return 0;
}

int verif_roi(Partie current, Coup c){
	int vect_x = c.xFrom - c.xTo;
	int vect_y = c.yFrom - c.yTo;
	int norme = sqrt(pow(vect_x, 2) + pow(vect_y, 2));
		if(norme > 1)
			return 0;
	return 1;
}

int verif_coup(Partie current, Coup c){
	Piece temp = current.plateau[c.xFrom][c.yFrom].p;
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
	if(current.plateau[c.xTo][c.yTo].p != VIDE){
		if(current.plateau[c.xTo][c.yTo].c == current.plateau[c.xFrom][c.yFrom].c)
			return 0;
		return 2;
	}
	return 1;
}

int est_echec(Partie *current, int *k, Couleur c){
	int x = k[0];
	int y = k[1];
	if(c == NOIR){
		x = k[2];
		y = k[3];
	}
	for(int i = 0; i < MAX_CASE; i++){
		for(int j = 0; j < MAX_CASE; j++){
			if((current->plateau[i][j].p != VIDE) && current->plateau[i][j].c != c){
				Coup temp = {i, j, x, y};
				if(verif_coup(*current, temp) == 1)
					return 1;
			}
		}

	}
	return 0;
}

int jouer_coup(Partie *current, Coup c, int *k){
	Piece new = current->plateau[c.xFrom][c.yFrom].p;
	Piece temp = VIDE;
	int x = k[2];
	int y = k[3];
	if(current->player == BLANC){
		x = k[0];
		y = k[1];
	}
		switch(verif_coup(*current, c)){
		case 0:
			printf("Coup impossible\n");
			return 0;
		break;
		case 1:
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xTo][c.yTo].p = new;
			current->plateau[c.xTo][c.yTo].c = current->player;
		break;
		case 2:
			temp = current->plateau[c.xTo][c.yTo].p;
			current->plateau[c.xFrom][c.yFrom].p = VIDE;
			current->plateau[c.xTo][c.yTo].p = new;
			current->plateau[c.xTo][c.yTo].c = current->player;
		break;
	}
	if(est_echec(current, k, current->player) == 1){
		printf("Impossible, votre roi est en echec\n");
		current->plateau[c.xTo][c.yTo].p = temp;
		current->plateau[c.xFrom][c.yFrom].p = new;
		return 0;
	}
	if(new == ROI){
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

int main(){
    Partie test;
    test.plateau = creer_plateau();
    test.player = BLANC;
	int *k = king();
	Coup temp;
	int x;
	int y;
	x = k[2];
	y = k[3];
	if(test.player == BLANC){
		x = k[0];
		y = k[1];
	}
	while(est_echec(&test, k, test.player) == 0){
		x = k[2];
		y = k[3];
		if(test.player == BLANC){
			x = k[0];
			y = k[1];
		}
			affichage(&test);
			temp = proposition_joueur();
			if(verif_coup(test, temp) == 0){
				printf("Coup non Valide\n");
			}
			else{
				if(jouer_coup(&test, temp, k) == 1)
					test.player = 1-test.player;
			}
		
	}
    return 1;

}
