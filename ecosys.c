#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x <= SIZE_X && y <= SIZE_Y);
  assert(x >= 0 && y >= 0);
  Animal *pred = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, pred);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  assert(liste);
  assert(animal);
  Animal *p, *t;

  if(*liste == animal){
    p = *liste;
    *liste = (*liste)->suivant;
    free(p);
    return ;
  }
  p = *liste;
  while(p->suivant != NULL && p->suivant != animal){
    p = p->suivant;
  }
  t = p->suivant;
  p->suivant = t->suivant;
  free(t);
  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal *p = liste;
   while (p != NULL){
     liste = p -> suivant;
     free(p);
     p = liste;
   }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];


  /* on initialise le tableau */
    for (i = 0; i < SIZE_X; i++){
      for (j = 0; j < SIZE_Y; j++){
        if(((i == 0) && (j == 0)) || ((i == SIZE_X -1)&&(j == SIZE_Y -1)) || ((i == SIZE_X -1) && (j == 0)) || ((i == 0) && (j == SIZE_Y -1)))
          ecosys[i][j] = '+';
        else if ((i == 0) || (i == SIZE_X - 1))
          ecosys[i][j] = '-';
        else if ((j == 0) || (j == SIZE_Y - 1))
          ecosys[i][j] = '|';
        else
          ecosys[i][j] = ' ';
      }
    }

  /* on ajoute les proies */
    while (liste_proie != NULL){
      ecosys[liste_proie->x][liste_proie->y] = '*';
      liste_proie = liste_proie->suivant;
    }


  /* on ajoute les predateurs */
  while(liste_predateur != NULL){
    if ((ecosys[liste_predateur->x][liste_predateur->y]) == '*'){
      ecosys[liste_predateur->x][liste_predateur->y] = '@';
    }
    else{
      ecosys[liste_predateur->x][liste_predateur->y] = '0';
    }
    liste_predateur = liste_predateur->suivant;
  }


  /* on affiche le tableau */
  for (i = 0; i < SIZE_X; i++){
    for (j = 0; j < SIZE_Y; j++){
      printf("%c", ecosys[i][j]);
    }
    printf("\n");
  }

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  Animal *tmp = la;
  while(tmp != NULL){
    if ((rand() / (float)RAND_MAX) < p_ch_dir){
      tmp -> x = ((tmp -> x) + (tmp -> dir[0]) + SIZE_X) % SIZE_X; //Si dir[0] < 0 => dir[0] % nb == -1 mais on veut x%SIZE_X = SIZEX - 1
      tmp -> y = ((tmp -> y) + (tmp -> dir[1]) + SIZE_Y) % SIZE_Y;
    }
    tmp = tmp -> suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *cpt = *liste_animal;
  while(cpt){
    if ((rand() / (float)RAND_MAX) < p_reproduce){
      Animal *a = creer_animal((cpt -> x), (cpt->y), ((cpt-> energie)/2));
      cpt->energie /= 2;
      *liste_animal = ajouter_en_tete_animal(*liste_animal, a);
    }
      cpt = cpt -> suivant;
  }
  return ;
}


// /* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
  Animal *p = *liste_proie;
  while(p){
    (p -> energie)--;
    if(monde[p->x][p->y] >= 0){
      (p -> energie) += monde[p->x][p->y];
      (monde[p->x][p->y]) = temps_repousse_herbe;
    }
    if(p -> energie < 0){
      enlever_animal(liste_proie, p);
    }
    p = p -> suivant; 
  }
  reproduce(liste_proie, p_reproduce_proie);
  return ;
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    while(l){
      if ((l->x == x) && (l->y == y)){
        return l;
      }
      l = l->suivant;
    }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal *ppre = *liste_predateur;
  while(ppre){
    (ppre -> energie)--;
    Animal *proie = animal_en_XY(*liste_proie, ppre->x, ppre->y);
    if(proie != NULL){
      ppre -> energie += proie->energie;
      enlever_animal(liste_proie, proie);
    }
    if(ppre -> energie < 0){
      enlever_animal(liste_predateur, ppre);
    }
    ppre = ppre->suivant; 
  }
  reproduce(liste_predateur, p_reproduce_predateur);

  return ;
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      (monde[i][j])++;
    }
  }
  return ;
}


