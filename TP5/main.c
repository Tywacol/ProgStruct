#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define NBL 10
#define NBC 10
#define N 10
#define M 10
#define RANDINF 0
#define RANDMAX 9
char ALPHA[52] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v',
        'w', 'x', 'y', 'z'
};

/* initialisation du generateur */
void initialise_rand()
{
    srand(time(NULL));
}

/* tire un entier au hasard entre inf et sup */
int hasard(int inf, int sup)
{
    int rando = rand();
    return (inf + (rando % (sup - inf + 1)));
}

/* affiche une tableau de char */
void afficher_tableau_char(char t[], int size)
{
    char maj;
    for (int i = 0; i < size; i++) {
        if (t[i] >= 'a' && t[i] <= 'z') {
            maj = t[i] - ('z' - 'Z');
        } else {
            maj = t[i];
        }
        printf("t[%d] = '%c' code = %d maj = '%c' \n", i, t[i], t[i], maj);
    }
    printf("\n");
}


/* remplis un tableau avec des entiers aleatoires
 * Donnee/resultat
 */
void remplir_tab__alea(char t[], int size)
{
    for (int i = 0; i < size; i++) {
        t[i] = hasard(0, 999);
    }
}

/*
 * Remplis une matrice [N][M] d'entiers aléatoires
 */
void remplir_matrice(int mat[NBL][NBC])
{
    for (int i = 0; i < NBL; i++) {
        for (int j = 0; j < NBC; j++) {
            mat[i][j] = hasard(RANDINF, RANDMAX);
        }
    }
}

/*
 * Imprime une matrice sur le terminal
 */
void imprimeMat(int mat[NBL][NBC])
{
    for (int i = 0; i < NBL; ++i) {
        for (int j = 0; j < NBC; ++j) {
            printf("%d ", mat[i][j]); /* NBL * NBC impression */
        }
        printf("\n");
    }
}

/* retourne le maximum d'un tableau d'entier
 * Resultat
 */
char max_tab(char t[], int size)
{
    char max = t[0];
    for (int i = 0; i < size; i++) {
        if (t[i] > max) {
            max = t[i];
        }
    }
    return max;
}

/*
 * Compte le nombre d'occurence de l'element el dans la matrice mat
 */
int nombre_occurence(int mat[NBL][NBC], int el)
{
    int count = 0;
    for (int i = 0; i < NBL; ++i) {
        for (int j = 0; j < NBC; ++j) {
            if (mat[i][j] == el)
                count++;
        }
    }
    return
            count;
}

/*
 * Construit la matrice symetrique de la matrice d'entree
 */
void construitSym(int mat[N][N], int resu[N][N])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i + 1; ++j) {
            resu[j][i] = mat[i][j]; /* triangle du haut */
            resu[i][j] = mat[i][j]; /*triangle du bas */
        }
    }
}

/*
 * affiche un tableau sur la sortie standard
 */
void afficher_tab(int tab[], int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

/*
 * Recherche une valeur dans un tableau et retourne son indice le cas echeant
 * Cette fonction effectue au pire N tests
 */
bool recherche1(int tab[N], int el)
{
    for (int i = 0; i < N; ++i) {
        if (el == tab[i]) {
            return true;
        }
    }
    return false; /* El n'est pas dans le tableau */
}

/*
 * recherche dichotomique d'un element el dans un tableau tab trie.
 */
bool recherche2(int tab[N], int el)
{
    int debut = 0;
    int fin = N-1;
    int mil;
    while (debut <= fin) {
        printf("Mil = %d, debut = %d, fin = %d \n", mil, debut, fin);
        mil = (fin + debut) / 2;
        if (tab[mil] == el) {
            return true;
        } else if (tab[mil] > el) {
            fin = mil - 1;
        } else {
            debut = mil + 1; /* + 1 pour terminaison */
        }
    }
    return false;
}

/* Fonction principale.. lalala */
int main()
{

    initialise_rand();
    printf("Debut du programme..\n\n");

    int tab[N] = {0, 2, 3, 78, 80, 200, 201, 1515, 2048, 10000};
    /*
    printf("Entrez %d entiers : \n", N);
    for (int i = 0; i < N; ++i) {
        scanf(" %d", &tab[i]);
    }
    */
    afficher_tab(tab, N);
    int el;
    printf("Entrez un entier : ");
    scanf(" %d", &el);
    if (recherche2(tab, el)) {
        printf("%d est dans le tableau.\n", el);
    } else {
        printf("%d n'est pas dans le tableau.\n", el);
    }


    /*
    int mat[NBC][NBC];
    remplir_matrice(mat);
    imprimeMat(mat);
    printf("\n");
    int mat2[NBC][NBC];
    construitSym(mat, mat2);
    imprimeMat(mat2);
     */

    printf("\n");
    printf("Fin du programme..\n");
    return 0;
}

