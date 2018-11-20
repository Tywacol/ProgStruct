#include <stdio.h>

#define N 10


/*
* Remplir un tableau de taille N avec
* des entiers positifs inférieurs à 100 
*/
void remplir_tableau(int tab[], int size)
{
    int tmp;
    int i = 0;
    while (i < size) {
        printf("Entrez un nombre : \n");
        scanf("%d", &tmp);
        if (tmp >= 0 && tmp < 100) {
            tab[i] = tmp;
            i++;
        } else {
            printf("Le nombre doit etre >= 0 et < 100\n");
        }
    }
}

/* affiche une tableau */
void affiche_tableau(int t[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", t[i]);
    printf("\n");
}

/*
* Copie le contenu d'un tableau d'entiers dans un autre de même taile
*/
void copie_tableau(int dest[], int src[], int size)
{
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

/*
* Echange deux entiers
*/
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
* Implementation du tri a bulle
*/

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        /* Les i derniers elements sont déjà triees*/    
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

int main()
{
    printf("Debut du programme..\n");


    int tab[N];
    int tab_sorted[N];
    int tab2[N];

    printf("Entrez 10 entiers >= 0 et < 100\n");
    remplir_tableau(tab, N);

    printf("Tableau entree :\n");
    affiche_tableau(tab, N);

    copie_tableau(tab_sorted, tab, N);
    bubbleSort(tab_sorted, N);
    printf("Voici le tableau triee :\n");
    affiche_tableau(tab_sorted, N);

    printf("Entrez 10 entiers >= 0 et < 100\n");
    remplir_tableau(tab2, N);


    printf("Fin du programme..\n");
    return 0;
}
