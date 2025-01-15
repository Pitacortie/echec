#include <stdio.h>
#include <stdlib.h>
#include "save.h"

void save(Partie current){
    FILE *fichier = NULL;
    fichier = fopen("partie.txt", "w");
    CoupEnregistre *temp = current.fiche_partie;
    if(fichier != NULL){
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
        while(temp->suivant != NULL){
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
        for(int x = 0; x < MAX_CASE; x++){
            for(int y = 0; y < MAX_CASE; y++){
                fprintf(fichier, "%d", current.plateau[x][y].p);
                fprintf(fichier, "%d", current.plateau[x][y].c);
            }
        }
        fprintf(fichier, "%ld", current.debut_coup);
    }
    fclose(fichier);
}

Partie load(){
    FILE *fichier = NULL;
    Partie res = creer_partie();
    res.fiche_partie = creer_coup_enregistre();
    CoupEnregistre *begin = res.fiche_partie;
    CoupEnregistre *suiv;
    fichier = fopen("partie.txt", "r");
    int ch;
    int loop = 1;
    float Btimer;
    float Ntimer;
    if(fichier != NULL){
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
        while(loop == 1){
            ch = fgetc(fichier);
            if(ch != 32){
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
                loop = 0;
        }
        for(int x = 0; x < MAX_CASE; x++){
            for(int y = 0; y < MAX_CASE; y++){
                res.plateau[x][y].p = fgetc(fichier) - '0';
                res.plateau[x][y].c = fgetc(fichier) - '0';
            }
        }
        long temp;
        fscanf(fichier, "%ld", &temp);
        res.debut_coup = temp;
        res.dernier_coup_joue = suiv;
        res.fiche_partie = begin;
        fclose(fichier);
        remove("partie.txt");
    }
    else{
        printf("Aucune partie trouve, nouvelle partie\n");
        res = creer_partie();
    }
    return res;
}
