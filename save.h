#ifndef SAVE_H
#define SAVE_H

#include "structure.h"
#include "init.h"

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

void save(Partie current);

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

Partie load();

#endif
