#include <stdio.h>
#include <stdlib.h>

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


Position **creer_plateau(){

Position **creer_plateau(){

    Position **tab = malloc(sizeof(*tab) * MAX_CASE);
    for(int i = 0; i < MAX_CASE; i++)
        *(tab + i) = malloc(sizeof(**tab) * MAX_CASE);

    for(int i = 0; i < MAX_CASE; i++){
        tab[1][i].p = PION;
        tab[1][i].c = BLANC;
        tab[6][i].p = PION;
        tab[6][i].c = NOIR;
    }
    Piece temp = TOUR;
    int j;
    for(j = 0; j < (MAX_CASE / 2) + 1; j++){
        tab[0][j].p = temp;
        tab[0][j].c = BLANC;
        tab[7][j].p = temp;
        tab[7][j].c = NOIR;
        temp++;
        
    }
    temp = FOU;
    for(int i = j; i < MAX_CASE + 1; i++){
        tab[0][i].p = temp;
        tab[0][i].c = BLANC;
        tab[7][i].p = temp;
        tab[7][i].c = NOIR;
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
			printf("|\n%d", i+1);
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
	printf("Donnez la position de la piece que vous voulez jouer :\n");
	scanf("%d%d", coup.xFrom, coup.yFrom);
	printf("Donnez la position de la case sur laquelle déplacer la pièce :\n");
	scanf("%d%d", coup.xTo, coup.yTo);
	return coup;
}


int main(){
    Partie test;
    test.plateau = creer_plateau();
    printf("ok");
    affichage(&test);
    for(int i = 0; i < 8; i++)
        free(*(test.plateau) + i);
    free(test.plateau);
    return 1;

}
