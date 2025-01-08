#ifndef INIT_H
#define INIT_H


#include "verif.h"
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
 * Paramètres de retour : 
 * Type                 Description
 * ------------------   ----------------------------------------------
 * Partie               La partie initialisée
 ******************************************************************************/
Partie creer_partie();

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
void liberer_partie(Partie partie);

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
 void liberer_fiche(CoupEnregistre *coup_efface);

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
Position **creer_plateau();

#endif