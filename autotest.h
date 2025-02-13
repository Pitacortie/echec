/******************************************************************************
 * Nom du fichier : autotest.h
 * Description    : Définition des tableaux de coup préenregistrés pour tester
 *                  l'application ou pour dérouler le début d'une partie.
 *
 *****************************************************************************/
#ifndef AUTOTEST_H
#define AUTOTEST_H



#define MAX_CASE 8

// ****************************************************************************	
// Valeur par défaut pour ne pas lancer de coup automatiquement
// ****************************************************************************	

int COUP_AUTO_MAX = 0;
Coup CoupAuto[1] = {{0,0,0,0}};

// ****************************************************************************	
// AutoTest - Promotion pion blanc en B8
// Succession de coups pour que le pion blanc atteigne la case B8 et demande 
// une promotion. La promotion n'est pas incluse dans le coup et doit être 
// définie 
// par le joueur.
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 9;
Coup CoupAuto[9] = {{6, 0, 4, 0}, {1,1,3,1}, {4,0,3,1}, {0,1,2,2}, {3,1,2,1}, {2,2,4,3}, {2,1,1,1}, {1,7,3,7}, {1,1,0,1}};
*/

// ****************************************************************************	
// AutoTest - Promotion pion noir en B1	
// Succession de coups pour que le pion noir atteigne la case B1 et demande une 
// promotion. La promotion n'est pas incluse dans le coup et doit être définie 
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 10;
Coup CoupAuto[10] = {{6, 0, 4, 0}, {1,1,3,1}, {7,0,5,0}, {3,1,4,0}, {5,0,5,7}, {4,0,5,0}, {6,2,4,2}, {5,0,6,0}, {7,1,5,2}, {6,0,7,0}} ;
*/
// ****************************************************************************	
// AutoTest - mise en échec et mat par la promotion d'un pion
// Succession de coups pour que le pion noir atteigne la case B1, demande une 
// promotion et mette le roi blanc en échec et mat. 
// La promotion n'est pas incluse dans le coup et doit être définie 
// ****************************************************************************	

//int COUP_AUTO_MAX = 14;
//Coup CoupAuto[14] = {{6, 0, 4, 0}, {1 ,1 ,3 ,1}, {7, 0,5 ,0 }, {3, 1, 4 ,0}, {5, 0, 5, 7}, {4, 0, 5, 0}, {6, 2, 4, 2}, {5, 0, 6, 0}, 
//                    {6, 1, 4, 1}, {1, 7, 2, 7}, {7, 2, 5, 0}, {1, 6, 2, 6}, {7, 3, 4, 0}, {6, 0, 7, 1}} ;


// ****************************************************************************	
// AutoTest - Échec contré par un pion sur la trajectoire
// Succession de coups pour que le roi noir soit en échec par la dame blanche
// mais qu'un pion noir se place sur sa trajectoire et contre l'échec au roi.
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 12;
Coup CoupAuto[12] = {{6, 4, 4, 4}, {1, 5, 3, 5}, {7, 3, 3, 7}, {0, 4, 1, 5},  {1, 6, 2, 6}, {3, 7, 5, 5}, {1, 3, 3, 3}, {5, 5, 5, 0}, 
                    {0, 6, 2, 7}, {6, 7, 5, 7}, {2, 7, 1, 5}, {5, 0, 4, 0}};
*/

// ****************************************************************************	
// AutoTest - Coup du berger
// Succession de coups définis par le "coup du berger" et atteindre mat des 
// noirs
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 7;
Coup CoupAuto[7] = {{6, 4, 4, 4}, {1, 4, 3, 4}, {7, 5, 4, 2}, {1, 3, 2, 3}, {7,3,5,5 }, {1,2,3,2 }, {5,5,1,5}} ;
*/

// ****************************************************************************	
// AutoTest - Kasparov vs Topalov 1999 - 1-0 par Abandon
// Coups de la partie de Kasparov contre Topalov de 1999 qui se termine par un 
// abandon de Topalov. 
// Cette partie permet de valider les grand roque blanc et noir, divers 
// déplacements pour chaque pièce avec des prises, la détection  de situation 
// d'échec. 
// Comparatif de la feuille de match:
//   (Reste à faire : différenciation de la pièce jouée lorsque 2 pièces peuvent 
//    atteindre la même destination) 
//
// 1.e4 d6 2.d4 Cf6 3.Cc3 g6 4.Fe3 Fg7 5.Dd2 c6 6.f3 b5 7.Cge2 Cfd7 8.Fh6 Fxh6 
// 1.e4 d6 2.d4 Cf6 3.Cc3 g6 4.Fe3 Fg7 5.Dd2 c6 6.f3 b5 7.Ce2 Cd7 8.Fh6 Fxh6 
//                                                        XXX XXX  
// 9.Dxh6 Fb7 10.a3 e5 11.O-O-O De7 12.Rb1 a6 13.Cc1 O-O-O 14.Cb3 exd4 15.Txd4 c5 16.Td1 Cb6 
// 9.Dxh6 Fb7 10.a3 e5 11.O-O-O De7 12.Rb1 a6 13.Cc1 O-O-O 14.Cb3 exd4 15.Txd4 c5 16.Td1 Cb6 
// 
// 17.g3 Rb8 18.Ca5 Fa8 19.Fh3 d5 20.Df4+ Ra7 21.The1 d4 22.Cd5 Cfxd5 23.exd5 Dd6 24.Txd4 cxd4 
// 17.g3 Rb8 18.Ca5 Fa8 19.Fh3 d5 20.Df4+ Ra7 21.Te1 d4 22.Cd5 CxD5 23.exd5 Dd6 24.Txd4 cxd4 
//                                               XXX           xxxx
// 25.Te7+ Rb6 26.Dxd4+ Rxa5 27.b4+ Ra4 28.Dc3 Dxd5 29.Ta7 Fb7 30.Txb7 Dc4 31.Dxf6 Rxa3 32.Dxa6+ Rxb4 
// 25.Te7+ Rb6 26.Dxd4+ Rxa5 27.b4+ Ra4 28.Dc3 Dxd5 29.Ta7 Fb7 30.Txb7 Dc4 31.Dxf6 Rxa3 32.Dxa6+ Rxb4 
//
// 33.c3+ Rxc3 34.Da1+ Rd2 35.Db2+ Rd1 36.Ff1 Td2 37.Td7 Txd7 38.Fxc4 bxc4 39.Dxh8 Td3 40.Da8 c3 
// 33.c3+ Rxc3 34.Da1+ Rd2 35.Db2+ Rd1 36.Ff1 Td2 37.Td7 Txd7 38.Fxc4 bxc4 39.Dxh8 Td3 40.Da8 c3 
// 
// 41.Da4+ Re1 42.f4 f5 43.Rc1 Td2 44.Da7
// 41.Da4+ Re1 42.f4 f5 43.Rc1 Td2 44.Da7
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 87;
Coup CoupAuto[87] = {{6, 4, 4, 4}, {1, 3, 2, 3}, {6, 3, 4, 3}, {0, 6, 2, 5}, {7, 1, 5, 2}, {1, 6, 2, 6}, {7, 2, 5, 4}, {0, 5, 1, 6}, 
					 {7, 3, 6, 3}, {1, 2, 2, 2}, {6, 5, 5, 5}, {1, 1, 3, 1}, {7, 6, 6, 4}, {0, 1, 1, 3}, {5, 4, 2, 7}, {1, 6, 2, 7},
					 {6, 3, 2, 7}, {0, 2, 1, 1}, {6, 0, 5, 0}, {1, 4, 3, 4}, {7, 4, 7, 2}, {0, 3, 1, 4}, {7, 2, 7, 1}, {1, 0, 2, 0},
					 {6, 4, 7, 2}, {0, 4, 0, 2}, {7, 2, 5, 1}, {3, 4, 4, 3}, {7, 3, 4, 3}, {2, 2, 3, 2}, {4, 3, 7, 3}, {1, 3, 2, 1},
					 {6, 6, 5, 6}, {0, 2, 0, 1}, {5, 1, 3, 0}, {1, 1, 0, 0}, {7, 5, 5, 7}, {2, 3, 3, 3}, {2, 7, 4, 5}, {0, 1, 1, 0},
					 {7, 7, 7, 4}, {3, 3, 4, 3}, {5, 2, 3, 3}, {2, 1, 3, 3}, {4, 4, 3, 3}, {1, 4, 2, 3}, {7, 3, 4, 3}, {3, 2, 4, 3},
					 {7, 4, 1, 4}, {1, 0, 2, 1}, {4, 5, 4, 3}, {2, 1, 3, 0}, {6, 1, 4, 1}, {3, 0, 4, 0}, {4, 3, 5, 2}, {2, 3, 3, 3},
					 {1, 4, 1, 0}, {0, 0, 1, 1}, {1, 0, 1, 1}, {3, 3, 4, 2}, {5, 2, 2, 5}, {4, 0, 5, 0}, {2, 5, 2, 0}, {5, 0, 4, 1}, 
					 {6, 2, 5, 2}, {4, 1, 5, 2}, {2, 0, 7, 0}, {5, 2, 6, 3}, {7, 0, 6, 1}, {6, 3, 7, 3}, {5, 7, 7, 5}, {0, 3, 6, 3}, 
					 {1, 1, 1, 3}, {6, 3, 1, 3}, {7, 5, 4, 2}, {3, 1, 4, 2}, {6, 1, 0, 7}, {1, 3, 5, 3}, {0, 7, 0, 0}, {4, 2, 5, 2}, 
					 {0, 0, 4, 0}, {7, 3, 7, 4}, {5, 5, 4, 5}, {1, 5, 3, 5}, {7, 1, 7, 2}, {5, 3, 6, 3}, {4, 0, 1, 0}};
*/

// ****************************************************************************	
// AutoTest - Computer-01- 1-0
// Coups d'une partie contre un ordinateur qui se termine par un mat des noirs.
// Cette partie permet de valider les petit roques blanc et noir, divers 
// déplacements pour chaque pièce avec des prises, la détection  de situation 
// d'échec et la fin de partie sur mat. 
// Comparatif de la feuille de match:
// 1.d4 d5 2.c4 dxc4 3.e4 b5 4.a4 c6 5.Cc3 b4 6.Ca2 Cf6 7.e5 Cd5 8.Fxc4 e6
// 1.d4 d5 2.c4 dxc4 3.e4 b5 4.a4 c6 5.Cc3 b4 6.Ca2 Cf6 7.e5 Cd5 8.Fxc4 e6
//
// 9.Cf3 a5 10.Fg5 Db6 11.Cc1 Fa6 12.De2 h6 13.Fe3 Fxc4 14.Dxc4 Cd7 15.Cb3 Fe7 16.Tc1 O-O
// 9.Cf3 a5 10.Fg5 Db6 11.Cc1 Fa6 12.De2 h6 13.Fe3 Fxc4 14.Dxc4 Cd7 15.Cb3 Fe7 16.Tc1 O-O
//
// 17.O-O Tc8 18.De2 c5 19.Cd2 Dc6 20.Dh5 Dxa4 21.Cxc5 Cxc5 22.dxc5 Cxe3 23.fxe3 Fxc5 24.Dxf7+ Rh8
// 17.O-O Tc8 18.De2 c5 19.Cd2 Dc6 20.Dh5 Dxa4 21.Cxc5 Cxc5 22.dxc5 Cxe3 23.fxe3 Fxc5 24.Dxf7+ Rh8
//
// 25.Df3 Tf8 26.De4 Dd7 27.Cb3 Fb6 28.Td1 Df7 29.Tf1 Da7 30.Txf8+ Txf8 31.Cd4 a4 32.Cxe6 Fxe3+
// 25.Df3 Tf8 26.De4 Dd7 27.Cb3 Fb6 28.Td1 Df7 29.Tf1 Da7 30.Txf8+ Txf8 31.Cd4 a4 32.Cxe6 Fxe3+
//
// 33.Rh1 Fxc1 34.Cxf8 De3 35.Dh7#
// 33.Rh1 Fxc1 34.Cxf8 De3 35.Dh7#
// ****************************************************************************	
/*
int COUP_AUTO_MAX = 69;
Coup CoupAuto[69] = {{6, 3, 4, 3}, {1, 3, 3, 3}, {6, 2, 4, 2}, {3, 3, 4, 2}, {6, 4, 4, 4}, {1, 1, 3, 1}, {6, 0, 4, 0}, {1, 2, 2, 2}, 
					 {7, 1, 5, 2}, {3, 1, 4, 1}, {5, 2, 6, 0}, {0, 6, 2, 5}, {4, 4, 3, 4}, {2, 5, 3, 3}, {7, 5, 4, 2}, {1, 4, 2, 4},
					 {7, 6, 5, 5}, {1, 0, 3, 0}, {7, 2, 3, 6}, {0, 3, 2, 1}, {6, 0, 7, 2}, {0, 2, 2, 0}, {7, 3, 6, 4}, {1, 7, 2, 7}, 
					 {3, 6, 5, 4}, {2, 0, 4, 2}, {6, 4, 4, 2}, {0, 1, 1, 3}, {7, 2, 5, 1}, {0, 5, 1, 4}, {7, 0, 7, 2}, {0, 4, 0, 6}, 
					 {7, 4, 7, 6}, {0, 5, 0, 2}, {4, 2, 6, 4}, {2, 2, 3, 2}, {5, 5, 6, 3}, {2, 1, 2, 2}, {6, 4, 3, 7}, {2, 2, 4, 0}, 
					 {5, 1, 3, 2}, {1, 3, 3, 2}, {4, 3, 3, 2}, {3, 3, 5, 4}, {6, 5, 5, 4}, {1, 4, 3, 2}, {3, 7, 1, 5}, {0, 6, 0, 7}, 
					 {1, 5, 5, 5}, {0, 2, 0, 5}, {5, 5, 4, 4}, {4, 0, 1, 3}, {6, 3, 5, 1}, {3, 2, 2, 1}, {7, 5, 7, 3}, {1, 3, 1, 5}, 
					 {7, 3, 7, 5}, {1, 5, 1, 0}, {7, 5, 0, 5}, {0, 0, 0, 5}, {5, 1, 4, 3}, {3, 0, 4, 0}, {4, 3, 2, 4}, {2, 1, 5, 4}, 
					 {7, 6, 7, 7}, {5, 4, 7, 2}, {2, 4, 0, 5}, {1, 0, 5, 4}, {4, 4, 1, 7}};
*/

// ****************************************************************************	
// AutoTest - Viktor Korchnoi - Anatoly Karpov 1/2-1/2
// Coups d'une partie entre Korchnoi et Karpov. Les noirs sont pat.
// Cette partie permet de valider les petit roques blanc et noir, divers 
// déplacements pour chaque pièce avec des prises, la détection  de situation 
// d'échec et la fin de partie sur mat. 
// Comparatif de la feuille de match:
// 1.c4 Cf6 2.d4 e6 3.Cc3 Fb4 4.e3 c5 5.Ce2 d5 6.a3 Fxc3+ 7.Cxc3 cxd4 8.exd4 dxc4 
// 1.c4 Cf6 2.d4 e6 3.Cc3 Fb4 4.e3 c5 5.Ce2 d5 6.a3 Fxc3+ 7.Cxc3 cxd4 8.exd4 dxc4 
//
// 9.Fxc4 Cc6 10.Fe3 O-O 11.O-O b6 12.Dd3 Fb7 13.Tad1 h6 14.f3 Ce7 15.Ff2 Cfd5 16.Fa2 Cf4 
// 9.Fxc4 Cc6 10.Fe3 O-O 11.O-O b6 12.Dd3 Fb7 13.Td1  h6 14.f3 Ce7 15.Ff2 Cd5  16.Fa2 Cf4
//                                               XXX                      XXX
// 17.Dd2 Cfg6 18.Fb1 Dd7 19.h4 Tfd8 20.h5 Cf8 21.Fh4 f6 22.Ce4 Cd5 23.g4 Tac8 24.Fg3 Fa6 
// 17.Dd2 Cg6  18.Fb1 Dd7 19.h4 Td8  20.h5 Cf8 21.Fh4 f6 22.Ce4 Cd5 23.g4 Tc8  24.Fg3 Fa6
//        XXX                   XXX                                       XXX
// 25.Tfe1 Tc6 26.Tc1 Ce7 27.Txc6 Dxc6 28.Fa2 Dd7 29.Cd6 Fb7 30.Cxb7 Dxb7 31.De3 Rh8 32.Tc1 Cd5 
// 25.Te1  Tc6 26.Tc1 Ce7 27.Txc6 Dxc6 28.Fa2 Dd7 29.Cd6 Fb7 30.Cxb7 Dxb7 31.De3 Rh8 32.Tc1 Cd5
//    XXX       
// 33.De4 Dd7 34.Fb1 Db5 35.b4 Dd7 36.Dd3 De7 37.Rf2 f5 38.gxf5 exf5 39.Te1 Df6 40.Fe5 Dh4+ 
// 33.De4 Dd7 34.Fb1 Db5 35.b4 Dd7 36.Dd3 De7 37.Rf2 f5 38.gxf5 exf5 39.Te1 Df6 40.Fe5 Dh4+
// 
// 41.Fg3 Df6 42.Th1 Ch7 43.Fe5 Dg5 44.Dxf5 Dd2+ 45.Rg3 Chf6 46.Tg1 Te8 47.Fe4 Ce7 48.Dh3 Tc8 
// 41.Fg3 Df6 42.Th1 Ch7 43.Fe5 Dg5 44.Dxf5 Dd2+ 45.Rg3 Cf6  46.Tg1 Te8 47.Fe4 Ce7 48.Dh3 Tc8
//                                                      XXX  
// 49.Rh4 Tc1 50.Dg3 Txg1 51.Dxg1 Rg8 52.Dg3 Rf7 53.Fg6+ Re6 54.Dh3+ Rd5 55.Fe4+ Cxe4 56.fxe4+ Rxe4 
// 49.Rh4 Tc1 50.Dg3 Txg1 51.Dxg1 Rg8 52.Dg3 Rf7 53.Fg6+ Re6 54.Dh3+ Rd5 55.Fe4+ Cxe4 56.fxe4+ Rxe4
//
// 57.Dg4+ Rd3 58.Df3+ De3 59.Rg4 Dxf3+ 60.Rxf3 g6 61.Fd6 Cf5 62.Rf4 Ch4 63.Rg4 gxh5+ 64.Rxh4 Rxd4 
// 57.Dg4+ Rd3 58.Df3+ De3 59.Rg4 Dxf3+ 60.Rxf3 g6 61.Fd6 Cf5 62.Rf4 Ch4 63.Rg4 gxh5+ 64.Rxh4 Rxd4
//
// 65.Fb8 a5 66.Fd6 Rc4 67.Rxh5 a4 68.Rxh6 Rb3 69.b5 Rc4 70.Rg5 Rxb5 71.Rf5 Ra6 72.Re6 Ra7 
// 65.Fb8 a5 66.Fd6 Rc4 67.Rxh5 a4 68.Rxh6 Rb3 69.b5 Rc4 70.Rg5 Rxb5 71.Rf5 Ra6 72.Re6 Ra7
//
// 73.Rd7 Rb7 74.Fe7 Ra7 75.Rc7 Ra8 76.Fd6 Ra7 77.Rc8 Ra6 78.Rb8 b5 79.Fb4 Rb6 80.Rc8 Rc6 
// 73.Rd7 Rb7 74.Fe7 Ra7 75.Rc7 Ra8 76.Fd6 Ra7 77.Rc8 Ra6 78.Rb8 b5 79.Fb4 Rb6 80.Rc8 Rc6
//
// 81.Rd8 Rd5 82.Re7 Re5 83.Rf7 Rd5 84.Rf6 Rd4 85.Re6 Re4 86.Ff8 Rd4 87.Rd6 Re4 88.Fg7 Rf4 
// 81.Rd8 Rd5 82.Re7 Re5 83.Rf7 Rd5 84.Rf6 Rd4 85.Re6 Re4 86.Ff8 Rd4 87.Rd6 Re4 88.Fg7 Rf4
//
// 89.Re6 Rf3 90.Re5 Rg4 91.Ff6 Rh5 92.Rf5 Rh6 93.Fd4 Rh7 94.Rf6 Rh6 95.Fe3+ Rh5 96.Rf5 Rh4 
// 89.Re6 Rf3 90.Re5 Rg4 91.Ff6 Rh5 92.Rf5 Rh6 93.Fd4 Rh7 94.Rf6 Rh6 95.Fe3+ Rh5 96.Rf5 Rh4
//
// 97.Fd2 Rg3 98.Fg5 Rf3 99.Ff4 Rg2 100.Fd6 Rf3 101.Fh2 Rg2 102.Fc7 Rf3 103.Fd6 Re3 104.Re5 Rf3 
// 97.Fd2 Rg3 98.Fg5 Rf3 99.Ff4 Rg2 100.Fd6 Rf3 101.Fh2 Rg2 102.Fc7 Rf3 103.Fd6 Re3 104.Re5 Rf3
//
// 105.Rd5 Rg4 106.Rc5 Rf5 107.Rxb5 Re6 108.Rc6 Rf6 109.Rd7 Rf7 110.Fe7 Rg8 111.Re6 Rg7 112.Fc5 Rg8 
// 105.Rd5 Rg4 106.Rc5 Rf5 107.Rxb5 Re6 108.Rc6 Rf6 109.Rd7 Rf7 110.Fe7 Rg8 111.Re6 Rg7 112.Fc5 Rg8
//
// 113.Rf6 Rh7 114.Rf7 Rh8 115.Fd4+ Rh7 116.Fb2 Rh6 117.Rg8 Rg6 118.Fg7 Rf5 119.Rf7 Rg5 120.Fb2 Rh6 
// 113.Rf6 Rh7 114.Rf7 Rh8 115.Fd4+ Rh7 116.Fb2 Rh6 117.Rg8 Rg6 118.Fg7 Rf5 119.Rf7 Rg5 120.Fb2 Rh6
//
// 121.Fc1+ Rh7 122.Fd2 Rh8 123.Fc3+ Rh7 124.Fg7 1/2-1/2
// 121.Fc1+ Rh7 122.Fd2 Rh8 123.Fc3+ Rh7 124.Fg7
//

// ****************************************************************************	
/*
int COUP_AUTO_MAX = 247;
Coup CoupAuto[247] = {{6, 2, 4, 2}, {0, 6, 2, 5}, {6, 3, 4, 3}, {1, 4, 2, 4}, {7, 1, 5, 2}, {0, 5, 4, 1}, {6, 4, 5, 4}, {1, 2, 3, 2}, 
                      {7, 6, 6, 4}, {1, 3, 3, 3}, {6, 0, 5, 0}, {4, 1, 5, 2}, {6, 4, 5, 2}, {3, 2, 4, 3}, {5, 4, 4, 3}, {3, 3, 4, 2}, 
					  {7, 5, 4, 2}, {0, 1, 2, 2}, {7, 2, 5, 4}, {0, 4, 0, 6}, {7, 4, 7, 6}, {1, 1, 2, 1}, {7, 3, 5, 3}, {0, 2, 1, 1}, 
					  {7, 0, 7, 3}, {1, 7, 2, 7}, {6, 5, 5, 5}, {2, 2, 1, 4}, {5, 4, 6, 5}, {2, 5, 3, 3}, {4, 2, 6, 0}, {3, 3, 4, 5}, 
 					  {5, 3, 6, 3}, {4, 5, 2, 6}, {6, 0, 7, 1}, {0, 3, 1, 3}, {6, 7, 4, 7}, {0, 5, 0, 3}, {4, 7, 3, 7}, {2, 6, 0, 5}, 
					  {6, 5, 4, 7}, {1, 5, 2, 5}, {5, 2, 4, 4}, {1, 4, 3, 3}, {6, 6, 4, 6}, {0, 0, 0, 2}, {4, 7, 5, 6}, {1, 1, 2, 0}, 
					  {7, 5, 7, 4}, {0, 2, 2, 2}, {7, 3, 7, 2}, {3, 3, 1, 4}, {7, 2, 2, 2}, {1, 3, 2, 2}, {7, 1, 6, 0}, {2, 2, 1, 3}, 
					  {4, 4, 2, 3}, {2, 0, 1, 1}, {2, 3, 1, 1}, {1, 3, 1, 1}, {6, 3, 5, 4}, {0, 6, 0, 7}, {7, 4, 7, 2}, {1, 4, 3, 3}, 
					  {5, 4, 4, 4}, {1, 1, 1, 3}, {6, 0, 7, 1}, {1, 3, 3, 1}, {6, 1, 4, 1}, {3, 1, 1, 3}, {4, 4, 5, 3}, {1, 3, 1, 4}, 
					  {7, 6, 6, 5}, {2, 5, 3, 5}, {4, 6, 3, 5}, {2, 4, 3, 5}, {7, 2, 7, 4}, {1, 4, 2, 5}, {5, 6, 3, 4}, {2, 5, 4, 7}, 
					  {3, 4, 5, 6}, {4, 7, 2, 5}, {7, 4, 7, 7}, {0, 5, 1, 7}, {5, 6, 3, 4}, {2, 5, 3, 6}, {5, 3, 3, 5}, {3, 6, 6, 3}, 
					  {6, 5, 5, 6}, {1, 7, 2, 5}, {7, 7, 7, 6}, {0, 3, 0, 4}, {7, 1, 4, 4}, {3, 3, 1, 4}, {3, 5, 5, 7}, {0, 4, 0, 2}, 
					  {5, 6, 4, 7}, {0, 2, 7, 2}, {5, 7, 5, 6}, {7, 2, 7, 6}, {5, 6, 7, 6}, {0, 7, 0, 6}, {7, 6, 5, 6}, {0, 6, 1, 5}, 
					  {4, 4, 2, 6}, {1, 5, 2, 4}, {5, 6, 5, 7}, {2, 4, 3, 3}, {2, 6, 4, 4}, {2, 5, 4, 4}, {5, 5, 4, 4}, {3, 3, 4, 4}, 
					  {5, 7, 4, 6}, {4, 4, 5, 3}, {4, 6, 5, 5}, {6, 3, 5, 4}, {4, 7, 4, 6}, {5, 4, 5, 5}, {4, 6, 5, 5}, {1, 6, 2, 6}, 
					  {3, 4, 2, 3}, {1, 4, 3, 5}, {5, 5, 4, 5}, {3, 5, 4, 7}, {4, 5, 4, 6}, {2, 6, 3, 7}, {4, 6, 4, 7}, {5, 3, 4, 3}, 
					  {2, 3, 0, 1}, {1, 0, 3, 0}, {0, 1, 2, 3}, {4, 3, 4, 2}, {4, 7, 3, 7}, {3, 0, 4, 0}, {3, 7, 2, 7}, {4, 2, 5, 1}, 
					  {4, 1, 3, 1}, {5, 1, 4, 2}, {2, 7, 3, 6}, {4, 2, 3, 1}, {3, 6, 3, 5}, {3, 1, 2, 0}, {3, 5, 2, 4}, {2, 0, 1, 0}, 
					  {2, 4, 1, 3}, {1, 0, 1, 1}, {2, 3, 1, 4}, {1, 1, 1, 0}, {1, 3, 1, 2}, {1, 0, 0, 0}, {1, 4, 2, 3}, {0, 0, 1, 0}, 
					  {1, 2, 0, 2}, {1, 0, 2, 0}, {0, 2, 0, 1}, {2, 1, 3, 1}, {2, 3, 4, 1}, {2, 0, 2, 1}, {0, 1, 0, 2}, {2, 1, 2, 2}, 
					  {0, 2, 0, 3}, {2, 2, 3, 3}, {0, 3, 1, 4}, {3, 3, 3, 4}, {1, 4, 1, 5}, {3, 4, 3, 3}, {1, 5, 2, 5}, {3, 3, 4, 3}, 
					  {2, 5, 2, 4}, {4, 3, 4, 4}, {4, 1, 0, 5}, {4, 4, 4, 3}, {2, 4, 2, 3}, {4, 3, 4, 4}, {0, 5, 1, 6}, {4, 4, 4, 5}, 
					  {2, 3, 2, 4}, {4, 5, 5, 5}, {2, 4, 3, 4}, {5, 5, 4, 6}, {1, 6, 2, 5}, {4, 6, 3, 7}, {3, 4, 3, 5}, {3, 7, 2, 7}, 
					  {2, 5, 4, 3}, {2, 7, 1, 7}, {3, 5, 2, 5}, {1, 7, 2, 7}, {4, 3, 5, 4}, {2, 7, 3, 7}, {2, 5, 3, 5}, {3, 7, 4, 7},
					  {5, 4, 6, 3}, {4, 7, 5, 6}, {6, 3, 3, 6}, {5, 6, 5, 5}, {3, 6, 4, 5}, {5, 5, 6, 6}, {4, 5, 2, 3}, {6, 6, 5, 5},
					  {2, 3, 6, 7}, {5, 5, 6, 6}, {6, 7, 1, 2}, {6, 6, 5, 5}, {1, 2, 2, 3}, {5, 5, 5, 4}, {3, 5, 3, 4}, {5, 4, 5, 5},
					  {3, 4, 3, 3}, {5, 5, 4, 6}, {3, 3, 3, 2}, {4, 6, 3, 5}, {3, 2, 3, 1}, {3, 5, 2, 4}, {3, 1, 2, 2}, {2, 4, 2, 5}, 
					  {2, 2, 1, 3}, {2, 5, 1, 5}, {2, 3, 1, 4}, {1, 5, 0, 6}, {1, 3, 2, 4}, {0, 6, 1, 6}, {1, 4, 3, 2}, {1, 6, 0, 6},
					  {2, 4, 2, 5}, {0, 6, 1, 7}, {2, 5, 1, 5}, {1, 7, 0, 7}, {3, 2, 4, 3}, {0, 7, 1, 7}, {4, 3, 6, 1}, {1, 7, 2, 7},
					  {1, 5, 0, 6}, {2, 7, 2, 6}, {6, 1, 1, 6}, {2, 6, 3, 5}, {0, 6, 1, 5}, {3, 5, 3, 6}, {1, 6, 6, 1}, {3, 6, 2, 7},
					  {6, 1, 7, 2}, {2, 7, 1, 7}, {7, 2, 6, 3}, {1, 7, 0, 7}, {6, 3, 5, 2}, {0, 7, 1, 7}, {5, 2, 1, 6}};
*/



#endif
