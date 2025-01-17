Notice d'utilisation du jeu d'échec

Pour compiler le jeu, utiliser le makefile qui se situe dans le répertoire. Taper "make" dans le terminal (Il faut que vous soyez dans le répertoire où se situent les fichiers.) Le makefile crée un executable appelé "main",

Pour commencer à jouer, exécuter "main".

Pour jouer, suivre les indications du terminal. Une fois la partie commencée les coups s'écrivent de la manière suivante : lettre majuscule de la colonne suivie du chiffre de la ligne. Ex : A2. Appuyer sur Entrée pour valider la case. 

La partie se sauvegarde automatiquement à chaque tour. Pour arrêter le programme, fermer l'exécutable. Lors de votre prochaine partie, vous pouvez au choix commencer une nouvelle partie ou recharger la dernière partie sauvegardée.

Pour utiliser les autotests, dans le fichier autotest.h retirer les commentaires afin de définir la constante COUP_AUTO_MAX (taille du tableau de coup automatique) et 
CoupAuto le tableau de coup automatique. 

Attention à ne définir qu'une seule fois ces variables. 
Attention sans modifications il n'y aura pas d'autotest.

Certains tests se concluent par des échecs et mat (le jeu est terminé), d'autres par des échecs et pat (il est impossible de continuer à jouer même si le programme le propose car les situations d'échec et pat ne sont pas vérifiés enfin d'autres tests vérifient des situations particulières et laissent les joueurs le choix de continuer à jouer. 
