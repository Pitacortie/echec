#ifndef PVP_H
#define PVP_H

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
char piece2char(Position case_courante);

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
void afficher_plateau(Partie *partie);

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
CoupEnregistre *creer_coup_enregistre();

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
void afficher_fiche_partie(CoupEnregistre *fiche_partie, Partie partie);

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
void maj_score(Partie *partie, Piece piece_prise);

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
 Coup proposition_joueur();
 


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
void jouer_coup(Partie *partie, Coup coup);

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
Piece promotion_pion(Partie *partie, Coup coup);

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
void play_pvp();


#endif