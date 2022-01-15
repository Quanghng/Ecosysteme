#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20



int main(void) {

  Animal *pre = NULL;
  ajouter_animal (1,1,5.5, &pre);
  ajouter_animal (3,5,10.5, &pre);
  ajouter_animal (2,4,4.5, &pre);
  ajouter_animal (4,9,7, &pre);

  Animal *proie = NULL;
  ajouter_animal (1,4,14, &proie);
  ajouter_animal (2,3,7, &proie);
  ajouter_animal (8,1,1, &proie);
  ajouter_animal (3,5,2, &proie);


  Animal *a = creer_animal(8, 1, 1);
  pre = ajouter_en_tete_animal(pre, a);


  enlever_animal(&pre, a);

  unsigned int cpt_pre = compte_animal_rec(pre);
  unsigned int cpt_proie = compte_animal_rec(proie);

  printf("nb pre : %d\nnb proie : %d\n", cpt_pre, cpt_proie);
  afficher_ecosys(proie, pre);

  bouger_animaux(proie);
  printf("nb pre : %d\nnb proie : %d\n", cpt_pre, cpt_proie);
  afficher_ecosys(proie, pre);


  liberer_liste_animaux(pre);
  liberer_liste_animaux(proie);
  /* Part 1, exercice 5, question 3 */

  return 0;
}
