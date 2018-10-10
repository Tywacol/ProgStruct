#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 500

/* initialisation du generateur */
void initialise_rand()
{
  srand(time(NULL));  
}

/* tire un entier au hasard entre inf et sup */
int hasard(int inf, int sup)
{
  int rando = rand();
  return (inf + (rando % (sup - inf +1)));
}

/* affiche une tableau de char */
void affiche_tableau_char(char t[], int size) {
	char maj;
	for (int i = 0; i<size; i++) {
		if (t[i] >= 'a' && t[i] <= 'z') {
			maj = t[i] + ('z' - 'Z');
		} else {
			maj = t[i];
		}	
		printf("t[%d] = '%c' code = %d maj = '%c' ",i,t[i],t[i], maj);
	}
	printf("\n");
}



/* remplis un tableau avec des entiers aleatoires
 * Donnee/resultat
 */
void remplir_tab_char_alea(char t[], int size) {
	for (int i = 0; i<size; i++) {
		t[i] = hasard('Z','z');
	}
}



/* retourne le maximum d'un tableau d'entier
 * Resultat
 */
char max_tab(char t[], int size) {
	char max = t[0];
	for (int i = 0; i<size; i++) {
		if (t[i] > max) {
			max = t[i]; 
		}	
	}
	return max;
}

/* Fonction principale.. lalala */
int main(){
	char tN];
	remplir_tab_char_alea(t,N);
	afficher_tableau(t,N);
	printf("La plus grande lettre est : %d.\n",max_tab(t,N);
	printf("Entrez une lettre : ");
	char c = getchar();
	printf("On trouve la lettre dans les cases ");	
	return 0;
	
	
}
