#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 500000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
extern float p_ch_dir;
extern float p_reproduce_proie;
extern float p_reproduce_predateur;
extern int temps_repousse_herbe;


int main(void) {
  srand(time(NULL));
  FILE *fd;

  Animal *pre = NULL;
  for(int x = 0; x < 20; x++){
    ajouter_animal (rand()%30, rand()%50, rand()%200, &pre);
  }

  Animal *proie = NULL;
  for(int x = 0; x < 20; x++){
    ajouter_animal (rand()%30, rand()%50, rand()%200, &proie);
  }



  int monde[SIZE_X][SIZE_Y];
    for (int i = 0; i < SIZE_X; i++){
      for (int j = 0; j < SIZE_Y; j++){
        monde[i][j] = 0;
      }
  } 

  int a = 0;

  while((proie != NULL)&&(a<200)){
    unsigned int cpt_pre = compte_animal_rec(pre);
    unsigned int cpt_proie = compte_animal_rec(proie);
    printf("nb pre : %d\nnb proie : %d\n", cpt_pre, cpt_proie);
    afficher_ecosys(proie, pre);
    rafraichir_proies(&proie, monde); 
    rafraichir_predateurs(&pre, &proie);
    rafraichir_monde(monde);
    // bouger_animaux(proie);
    // bouger_animaux(pre);
    // reproduce(&proie,p_reproduce_proie);
    printf("%d\n", a);

    if((fd = fopen("Evol_Pop.txt", "a+")) == NULL){
      printf("Error!");
      return 1;
    }
    fprintf(fd,"%d %d %d\n", a, cpt_proie, cpt_pre);
    rewind(fd);
    fclose(fd);
    clear_screen();
    usleep(T_WAIT);

    a++;
  }
    liberer_liste_animaux(pre);
    liberer_liste_animaux(proie);

  return 0;
}

