#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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

/* affiche une tableau */
void affiche_tableau(int t[], int size) {
	for (int i = 0; i<size; i++) {
		printf("%d ",t[i]);
	}
	printf("\n");
}

/* remplis un tableau avec un entier
 * Donnee/resultat
 */
void remplir_tab_v(int v,int t[], int size) {
	for (int i = 0; i<size; i++) {
		t[i] = v;
	}
}


/* remplis un tableau avec des entiers aleatoires
 * Donnee/resultat
 */
void remplir_tab_alea(int v,int t[], int size) {
	for (int i = 0; i<size; i++) {
		t[i] = hasard(0,400);
	}
}

/* retourne la somme des entiers d'un tableau
 * Resultat
 */
int somme_tab(int t[], int size) {
	int sum = 0;
	for (int i = 0; i<size; i++) {
		sum += t[i];
	}
	return sum;
}

/* retourne le maximum d'un tableau d'entier
 * Resultat
 */
int max_tab(int t[], int size) {
	int max = t[0];
	for (int i = 0; i<size; i++) {
		if (t[i] > max) {
			max = t[i]; 
		}	
	}
	return max;
}

/* Fonction principale.. lalala */
int main(){
	/* Partie 1
	initialise_rand();
	int t[10] = {1,4,10,7,10,-1,-1515,2012,190,200};
	affiche_tableau(t, 10);
	remplir_tab(-1, t, 10);
	affiche_tableau(t, 10);
	remplir_tab_alea(t,10)
	affiche_tableau(t, 10);
	somme_tab(t, 10);
	affiche_tableau(t, 10);
	max_tab(t, 10);
	affiche_tableau(t, 10);
	*/
	
	return 0;
	
}
