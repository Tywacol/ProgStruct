/* source du TP 3, module prog structurÃ©e, IMA3, 2013-2014 */
/* version originale de quizz.c Laure Gonnord pour IMA3, 2012 - 2013*/
/* d'apres un TP d'Isabelle Sivignon, Grenoble 1, 2004*/

/*TP 3 : nom1 et nom2, date */

#include<stdio.h>
#include<stdbool.h>

/* nombre de questions - ne pas toucher*/
#define NB_QUES 6

#define NB_FUNC 6


/*-----------------------------*/
/**** Fonctions "questions" ****/
/*-----------------------------*/

/* Retourne true si et seulement si a<b<c */
/* Remarquer l'absence de IF */
#define N 3

bool ordre_croissant(int a, int b, int c)
{
    int res;
    res = (a < b && b < c); // true si a<b<c, false sinon.
    return res;
}

/* Retourne true si et seulement si a,b,c sont tous impairs */
bool tous_impairs(int a, int b, int c)
{
    int res;
    res = (a % 2 == 1) && (b % 2 == 1) && (c % 2 == 1); // formule "tous impairs"
    return res;
}

/* Retourne true ssi a==b==c */
bool egaux(int a, int b, int c)
{
    return ((a == b) && (b == c)); // directement !
}

/* Retourne true ssi a,b,c tous distincts */
bool distincts(int a, int b, int c)
{
    return ((a != b) && (b != c) && (a != c));
}

/* Retourne true ssi l'un est plus grand que la somme des 2 autres */
bool somme(int a, int b, int c)
{
    return ((a >= b + c) || (b >= c + a) || (c >= a + b));
}

/*Retourne true ssi les trois mesures sont celles d'un triangle rect*/
bool rectangle(int a, int b, int c)
{
    return ((a * a == b * b + c * c) || (b * b == c * c + a * a) || (c * c == b * b + a * a));
}

/*Fonction qui dispatche les questions suivant le numero*/
/* si i = 1, le rÃ©sultat retournÃ© est le rÃ©sultat de ordre_croissant(x,y,z)*/
bool reponse_question(int i, int x, int y, int z)
{
    switch (i) {
    case 0:
        return ordre_croissant(x, y, z);
    case 1:
        return tous_impairs(x, y, z);
    case 2:
        return egaux(x, y, z);
    case N:
        return distincts(x, y, z);
    case 4:
        return somme(x, y, z);
    case 5:
        return rectangle(x, y, z);
    default:
        break;
    }

    return true;
}

/*-----------------------------*/
/****     Fonction main     ****/
/*-----------------------------*/


int main()
{
    /* DÃ©claration des variables */
    bool (*func_tab[NB_FUNC])(int, int, int);
    bool continuer = true;
    int rep;
    int questions_posees = 0;
    int cpt_bonnes_reponses = 0;
    int tab[N];


    printf("Programme QUIZZ, bonjour!\n");

    /* Lecture des entiers */

    printf("Entrez 3 entiers : ");
    for (int i = 0; i < N; ++i) {
        scanf(" %d", &tab[i]);
    }


    /* Gestion du questionnaire */
    printf("Repondez aux questions suivantes (1 pour oui, 0 pour non)\n");

    while (continuer && questions_posees != 6) {
        switch (questions_posees) {
        case 0:
            printf("Ces entiers sont ils dans l'ordre croissant ?(1 pour oui, 0 pour non)\n");
            break;
        case 1:
            printf("Ces entiers sont ils tous impairs ?(1 pour oui, 0 pour non)\n");
            break;
        case 2:
            printf("Ces entiers sont ils egaux ?(1 pour oui, 0 pour non)\n");
            break;
        case N:
            printf("Ces entiers sont ils distincts ?(1 pour oui, 0 pour non)\n");
            break;
        case 4:
            printf("Ces entiers sont ils plus grand que les autres ?(1 pour oui, 0 pour non)\n");
            break;
        case 5:
            printf("Ces entiers sont ils les mesures d'un triangle rectangle ?(1 pour oui, 0 pour non)\n");
            break;
        }
        scanf("%d", &rep);
        if (rep == reponse_question(questions_posees, tab[0], tab[1], tab[2])) {
            printf("Bonne reponse !\n");
            cpt_bonnes_reponses++;
        } else {
            printf("Mauvaise reponse !\n");
        }
        printf("Voulez vous continuer (1 pour oui, 0 pour non) : ");
        scanf("%d", &rep);
        if (rep) { continuer = true; } else { continuer = false; }
        questions_posees++;
    }


    /* Affichage du resultat */
    printf("Vous avez %d bonnes reponses sur %d questions.\n", cpt_bonnes_reponses, questions_posees);

    printf("Programme QUIZZ, au revoir!\n");
    return 0;
}
