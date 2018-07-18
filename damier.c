 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int k = 0;
// 0 Noir
// 1 Blanc
 
 
// 0 Blanc
// 1 O
// 2 X
 
 
 
// variables globales pour pouvoir les reutiliser dans les autres fonction comme jeu()
char* joueur1 = NULL; // initialisation de l'allocation memoire
char* joueur2 = NULL; // initialisation de l'allocation memoire
int pion;
int Damier2[10][10];
int fin_de_partie = 0;
int depart_x, depart_y, arrivee_x, arrivee_y;
int damierIsDisplay = 0;
 
// Fonction qui prends en parametre la couleur du texte et la couleur du fond
void color(char* couleur){
   printf("\033[%sm",couleur);
}
 
 
 
// menu du debut
void menu(){
  joueur1 = malloc(sizeof(char)); // allocation de la memoire
  joueur2 = malloc(sizeof(char)); // allocation de la memoire
  if (joueur1 == NULL || joueur2 == NULL){
      exit(0);
  }
  printf("Jeu de dame en C\n");
}
 
char* nameJoueur1(){
  color("31");
  printf("Joueur 1 :");
  color("0");
  printf(" ");
  scanf("%s",joueur1);
  return joueur1;
 }

 char* nameJoueur2(){
  color("35");
  printf("Joueur 2 :");
  color("0");
  printf(" ");
  scanf("%s",joueur2);
  return joueur2;
 }

 void begin(joueur1,joueur2){ 
    printf("\n\n");
    color("31");
    printf(" %s ", joueur1);
    color("0");
    printf(" VS ");
    color("35");
    printf(" %s \n\n\n", joueur2);
    color("0");
}

 
  

 
 
 
// initialisation du plateau de jeux (tableau 2D) a 0
void initialisation_plateau(int Damier[10][10]){
  int i,j;
  for (i=0;i<10; i++){
    for(j=0; j<10;j++){
      Damier[i][j] = 0;
    }
  }
}
 
 
 
// configuration pour le placement des pions sur le damier
void configuration_piont(int Damier[10][10]){
  int i,j;
  // premiere boucle pour les colonnes allant de 0 a 4 car il y a que des X
  for(i=0;i<4;i++){
    for(j=0;j<10;j++){
      if((i+j)%2 == 0){
        Damier[i][j] = 0; // on met la valeur a 0
      }else{
        Damier[i][j] = 2; // on met a 2 ce qui correspond a la croix
      }
    }
  }
 
// pour la deuxieme partie du damier de la 4 eme a la 6 eme colonne car il n'y a pas de pions dans cette partie
  for(i=4;i<6;i++){
    for(j=0;j<10;j++){
      Damier[i][j] = 0; // font blanc sans pions
    }
 
  }
 
// derniere partie du damier ou il y a que des O
  for(i=6;i<10;i++){
    for(j=0;j<10;j++){
      if((i+j)%2 == 0){
        Damier[i][j] = 0;
      }else{
        Damier[i][j] = 1; // O
      }
    }
  }
}
 
 
// affichage du damier
void afficher_plateau(int Damier[10][10]){
  printf(" 0  1  2  3  4  5  6  7  8  9\n");
  int i,j;
  for(i=0; i<10; i++){
    for(j=0;j<10;j++){
      if(Damier[i][j] == 1){
        color("31");;
        printf(" O ");
        color("0");
      }
      else if(Damier[i][j] == 2){
        color("35");
        printf(" X ");
        color("0");
     }else{
       if((j+i)%2 == 0){
         color("40");
         printf("   ");
         color("0");
       }else{
         color("0");
         printf("   ");
         color("0");
        }
      }
    }
    printf("%d\n",i);
  }
}
 
 
int verification (int depart_x, int depart_y, int arrivee_x, int arrivee_y, int pion, int damier[10][10]){
  if (pion == 1){ // si c'est les rond
    if ((damier[arrivee_x][arrivee_y] == 0) && (damier[arrivee_x][arrivee_y] !=1)){ // Si la case de destination est vide et qu(il y a pas de rond dessus
      if (((arrivee_x == depart_x - 1) && (arrivee_y == depart_y - 1)) || ((arrivee_x == depart_x - 1) && (arrivee_y == depart_y + 1))){ // condition pour faire que les 2 mouvements possible diagonale fauche et droite d'une seule case
	return 1;
      }else{
        return 0;
      }
    }
  }else if (pion == 2){ // si c'est les X
     if ((damier[arrivee_x][arrivee_y] == 0 ) && (damier[arrivee_x][arrivee_y] !=2)){ // Si la case de destination est vide et qu'il n'y a pas deja une croix dessus
       if (((arrivee_x == depart_x + 1) && (arrivee_y == depart_y + 1)) || ((arrivee_x == depart_x + 1) && (arrivee_y == depart_y - 1))){
         return 1;
       }else{
         return 0;
       }
     }
   }else{
      return 0; // sinon erreur
   }
} 
 
 
void jeu(int pion){
  if (pion == 1){
    printf("%s Entrez l'ordonnee de depart du pion : ", joueur1);
    scanf("%d", &depart_y);
    printf("%s Entrez l'abcisse de depart du pion : ", joueur1);
    scanf("%d", &depart_x);
    printf("%s Entrez l'ordonnee d'arrivee du pion : ", joueur1);
    scanf("%d", &arrivee_y);
    printf("%s Entrez l'abcisse d'arrivee du pion : ", joueur1);
    scanf("%d", &arrivee_x);
    if (verification(depart_x, depart_y, arrivee_x, arrivee_y, pion, Damier2) == 1){
      Damier2[arrivee_x][arrivee_y]=Damier2[depart_x][depart_y];
      Damier2[depart_x][depart_y] = 0;
    }  
    system("cls");
    afficher_plateau(Damier2);		
  }else{
    
    printf("%s Entrez labcisse de depart du pion : ", joueur2);
    scanf("%d", &depart_y);
    printf("%s Entrez l'ordonnee de depart du pion : ", joueur2);
    scanf("%d", &depart_x);
    printf("%s Entrez labcisse d'arrivee du pion : ", joueur2);
    scanf("%d", &arrivee_y);
    printf("%s Entrez l'ordonnee d'arrivee du pion : ", joueur2);
    scanf("%d", &arrivee_x);
    if (verification(depart_x, depart_y, arrivee_x, arrivee_y, pion, Damier2) == 1){
      Damier2[arrivee_x][arrivee_y]=Damier2[depart_x][depart_y];
      Damier2[depart_x][depart_y] = 0;
    }
    system("cls");
    afficher_plateau(Damier2);	 
  }
}
 
 
int alternance(){
  int i =0;
  while(fin_de_partie !=1){ // tant que aucun joueur a remporter la partie
    if(i%2 == 0){ // systeme pour faire 1 fois sur 2
      jeu(1);
      i++;
    }else{
      jeu(2);
      i++;
    }
  }
}
 
 
 
/*int play(){
  initialisation_plateau(Damier2);
  configuration_piont(Damier2);
  menu();
  nameJoueur1();
  nameJoueur2();
  //begin(); 
  afficher_plateau(Damier2);
  //color(15,0);
  //alternance();
  return 0;
}*/
