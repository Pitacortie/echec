in#include <stdio.h>
#include <stdlib.h>
#include "save.h"


/******************************************************************************
 * Nom de fonction : save
 *
 * Description : Sauvegarde les informations relatives àà la partie dans un fichier texte nommé "partie"
 *
 * -Créer un pointeur de type FILE
 * -Ouvrir et créer si n'existe pas un fichier en mode écriture
 * -Sauvegarder les informations des joueurs
 * -Sauvegarder les informations de chaque maillon de la fiche de partie
 * -Sauvegarder les cases du plateau
 * -Fermer le fichier
 *
 * Paramètres d'entrée : 
 * Paramètre      Type        E/S   Description
 * -------------  ---------   ---   -------------------------------------------
 * current         Partie      E    La partie à sauvegarder
 * 
 * Paramètres de retour : aucun
 *
 ******************************************************************************/
void save(Partie current)
{
    //Créer un pointeur de type FILE
    FILE *fichier = NULL;
    //Ouvrir et créer si n'existe pas un fichier en mode écriture
    fichier = fopen("partie.txt", "w");
    CoupEnregistre *temp = current.fiche_partie;
    //Si le fichier est bien o=créer
    if(fichier != NULL)
    { 
        // Sauvegarder les informations des joueurs
        fprintf(fichier, "%d", current.player);
        fprintf(fichier, "%d", current.Blanc.xRoi);
        fprintf(fichier, "%d", current.Blanc.yRoi);
        fprintf(fichier, "%d", current.Blanc.mat);
        fprintf(fichier, "%d", current.Blanc.score);
        fprintf(fichier, "%f", current.Blanc.timer);
        fprintf(fichier, ";");
        fprintf(fichier, "%d", current.Noir.xRoi);
        fprintf(fichier, "%d", current.Noir.yRoi);
        fprintf(fichier, "%d", current.Noir.mat);
        fprintf(fichier, "%d", current.Noir.score);
        fprintf(fichier, "%f", current.Noir.timer);
        fprintf(fichier, ";");
        while(temp->suivant != NULL)
        { 
            //Sauvegarder les informations de chaque maillon de la fiche de partie
            fprintf(fichier, "%d", current.fiche_partie->piece);
            fprintf(fichier, "%d", current.fiche_partie->coup.xFrom);
            fprintf(fichier, "%d", current.fiche_partie->coup.yFrom);
            fprintf(fichier, "%d", current.fiche_partie->coup.xTo);
            fprintf(fichier, "%d", current.fiche_partie->coup.yTo);
            fprintf(fichier, "%d", current.fiche_partie->prise);
            fprintf(fichier, "%d", current.fiche_partie->grandRoque);
            fprintf(fichier, "%d", current.fiche_partie->petitRoque);
            fprintf(fichier, "%d", current.fiche_partie->promotion);
            fprintf(fichier, "%d", current.fiche_partie->echec);
            fprintf(fichier, "%d", current.fiche_partie->mat);
            temp = temp->suivant;
        }
        fprintf(fichier ," ");
        //Sauvegarder les cases du plateau
        for(int x = 0; x < MAX_CASE; x++)
        { 
            for(int y = 0; y < MAX_CASE; y++)
            {
                fprintf(fichier, "%d", current.plateau[x][y].p);
                fprintf(fichier, "%d", current.plateau[x][y].c);
            }
        }
        fprintf(fichier, "%ld", current.debut_coup);
    }
    //Fermer le fichier
    fclose(fichier);
}

/******************************************************************************
 * Nom de fonction : load
 *
 * Description : Renvoie une structure Partie en lisant le fichier texte "partie"
 *
 * -Créer un pointeur de type FILE
 * -Créer une partie et une fiche de partie
 * -Ouvrir le fichier en mode lecture
 * -Charger les informations des joueurs enregistrées dans le fichier texte
 * -Charger les informations de la fiche de partie enregistrées dans le fichier texte
 * -Charger les informations du plateau enregistrées dans le fichier texte
 * -Fermer le fichier 
 *
 * Paramètres d'entrée : aucun
 
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Partie               Partie sauvegardée à charger
 ******************************************************************************/
Partie load()
{
    // Créer un pointeur de type FILE
    FILE *fichier = NULL;
    // Créer une partie et une fiche de partie
    Partie res = creer_partie();
    res.fiche_partie = creer_coup_enregistre();
    CoupEnregistre *begin = res.fiche_partie;
    CoupEnregistre *suiv;
    // Ouvrir le fichier en mode lecture
    fichier = fopen("partie.txt", "r");
    int ch;
    int loop = 1;
    float Btimer;
    float Ntimer;
    if(fichier != NULL)
    {
        // Charger les informations des joueurs enregistrées dans le fichier texte
        res.player = fgetc(fichier) - '0';
        res.Blanc.xRoi = fgetc(fichier) - '0';
        res.Blanc.yRoi = fgetc(fichier) - '0';
        res.Blanc.mat = fgetc(fichier) - '0';
        res.Blanc.score = fgetc(fichier) - '0';
        fscanf(fichier, "%f", &Btimer);
        res.Blanc.timer = Btimer;
        fgetc(fichier);
        res.Noir.xRoi = fgetc(fichier) - '0';
        res.Noir.yRoi = fgetc(fichier) - '0';
        res.Noir.mat = fgetc(fichier) - '0';
        res.Noir.score = fgetc(fichier) - '0';
        fscanf(fichier, "%f", &Ntimer);
        res.Noir.timer = Ntimer;
        fgetc(fichier);
        while(loop == 1)
        {
            ch = fgetc(fichier);
            if(ch != 32)
            {
                //Charger les informations de la fiche de partie enregistrées dans le fichier texte
                suiv = creer_coup_enregistre();
                res.fiche_partie->piece = ch - '0';
                res.fiche_partie->coup.xFrom = fgetc(fichier) - '0';
                res.fiche_partie->coup.yFrom = fgetc(fichier) - '0';
                res.fiche_partie->coup.xTo = fgetc(fichier) - '0';
                res.fiche_partie->coup.yTo = fgetc(fichier) - '0';
                res.fiche_partie->prise = fgetc(fichier) - '0';
                res.fiche_partie->grandRoque = fgetc(fichier) - '0';
                res.fiche_partie->petitRoque = fgetc(fichier) - '0';
                res.fiche_partie->promotion = fgetc(fichier) - '0';
                res.fiche_partie->echec = fgetc(fichier) - '0';
                res.fiche_partie->mat = fgetc(fichier) - '0';
                res.fiche_partie->suivant = suiv;
            }
            else
            {
                loop = 0;
            }
        }
        for(int x = 0; x < MAX_CASE; x++)
        {
            for(int y = 0; y < MAX_CASE; y++)
            {
                //Charger les informations du plateau enregistrées dans le fichier texte
                res.plateau[x][y].p = fgetc(fichier) - '0';
                res.plateau[x][y].c = fgetc(fichier) - '0';
            }
        }
        long temp;
        fscanf(fichier, "%ld", &temp);
        res.debut_coup = temp;
        res.dernier_coup_joue = suiv;
        res.fiche_partie = begin;
        // Fermer le fichier 
        fclose(fichier);
        remove("partie.txt");
    }
    else
    {
        printf("Aucune partie trouve, nouvelle partie\n");
    }
    return res;
}
