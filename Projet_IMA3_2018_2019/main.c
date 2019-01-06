#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // peut etre à la fin plus propre

#define LARGEUR 16
#define HAUTEUR 16

#define NB_OBSTACLES 8
#define NB_BONUS 2
#define NB_WARP 2
#define NB_DUPLICATE 1
#define NB_MALUS 1

/* Variables global */
int VISION_BONUS = 0;
int ITER = 0;
bool DEBUG = false; /* Mettre a vrai pour obtenir la vision globale */
bool WON = false;

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

void
init_grid(char grid[HAUTEUR][LARGEUR], int nb_obstacles, int nb_bonus, int c_pos_x, int c_pos_y, int nb_warp,
          int nb_duplicate, int nb_malus)
{
    int x_tmp;
    int y_tmp;

    /* mise à 0 de la grid */
    for (int k = 0; k < HAUTEUR; ++k) {
        for (int i = 0; i < LARGEUR; ++i) {
            grid[k][i] = 0;
        }
    }

    /* placement du chevalier */
    grid[c_pos_y][c_pos_x] = 'C';

    /* placement de la cible */
    do {
        x_tmp = hasard(0, 15);
        y_tmp = hasard(0, 15);
    } while (grid[x_tmp][y_tmp]);
    grid[x_tmp][y_tmp] = 'T';

    /* placement des duplicate */
    for (int n = 0; n < nb_duplicate; ++n) {
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'D';
    }


    /* placement des warp */
    for (int n = 0; n < nb_warp; ++n) {
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'W';
    }

    /* placement des bonus de vision */
    for (int m = 0; m < nb_bonus; ++m) {
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'B';
    }

    /* placement des obstacles */
    for (int l = 0; l < nb_obstacles; ++l) {
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'X';

    }
    /* placement des malus */
    for (int l = 0; l < nb_malus; ++l) {
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'M';

    }


}

/* affiche une tableau */
// VERSION CLASSIQUE
void output_grid_classique(char grid[HAUTEUR][LARGEUR], int c_pos_x, int c_pos_y)
{
    int vision = 2 + VISION_BONUS;

    int cases_vision[HAUTEUR][HAUTEUR];
    for (int l = 0; l < HAUTEUR; ++l) {
        for (int i = 0; i < HAUTEUR; ++i) {
            cases_vision[l][i] = false;
        }
    }

    bool depassement;
    int y_periodique = 0;
    int x_periodique = 0;

    for (int j = c_pos_y - vision; j < c_pos_y + vision + 1; ++j) {
        for (int i = c_pos_x - vision; i < c_pos_x + vision + 1; ++i) {
            depassement = false;
            y_periodique = j;
            x_periodique = i;
            if (j < 0) {
                depassement = true;
            } else if (j > (HAUTEUR - 1)) {
                depassement = true;
            }
            //work to do here
            if (i < 0) {
                depassement = true;
            } else if (i > (HAUTEUR - 1)) {
                depassement = true;
            }
            if (!depassement) {
                cases_vision[j][i] = true;
            }

            if (!grid[y_periodique][x_periodique] && cases_vision[y_periodique][x_periodique]) {
                if (j == c_pos_y - 1 && i == c_pos_x + 2) {
                    cases_vision[y_periodique][x_periodique] = -1;
                } else if (j == c_pos_y - 2 && i == c_pos_x + 1) {
                    cases_vision[y_periodique][x_periodique] = 2;
                } else if (j == c_pos_y - 2 && i == c_pos_x - 1) {
                    cases_vision[y_periodique][x_periodique] = 9;
                } else if (j == c_pos_y - 1 && i == c_pos_x - 2) {
                    cases_vision[y_periodique][x_periodique] = 4;
                } else if (j == c_pos_y + 1 && i == c_pos_x - 2) {
                    cases_vision[y_periodique][x_periodique] = 5;
                } else if (j == c_pos_y + 2 && i == c_pos_x - 1) {
                    cases_vision[y_periodique][x_periodique] = 6;
                } else if (j == c_pos_y + 2 && i == c_pos_x + 1) {
                    cases_vision[y_periodique][x_periodique] = 7;
                } else if (j == c_pos_y + 1 && i == c_pos_x + 2) {
                    cases_vision[y_periodique][x_periodique] = 8;
                }
            }


        }
    }


    printf("\n");
    for (int y = 0; y < HAUTEUR; ++y) {
        //printf("|");
        for (int x = 0; x < LARGEUR; ++x) {
            if (cases_vision[y][x]) {
                if (grid[y][x]) {
                    printf("%c", grid[y][x]);
                } else if (cases_vision[y][x] != 1) {
                    // code spécial pour 1 care 1 == true, on note la position 1 par -1 dans case visions
                    if (cases_vision[y][x] == -1) {
                        printf("1");
                    } else {
                        printf("%d", cases_vision[y][x]);
                    }
                } else {
                    printf(" ");
                }
            } else {
                if (DEBUG) {
                    printf("%c", grid[y][x]);
                } else {
                    printf("%c", 254); // 254 est le caractère carre  : ■
                }
            }
            printf(" ");
        }
        printf("\n");
    }

}


/* affiche une tableau */
// VERSION PERIODIQUE
void output_grid_periodique(char grid[HAUTEUR][LARGEUR], int c_pos_x, int c_pos_y)
{
    int vision = 2 + VISION_BONUS;

    int cases_vision[HAUTEUR][HAUTEUR];
    for (int l = 0; l < HAUTEUR; ++l) {
        for (int i = 0; i < HAUTEUR; ++i) {
            cases_vision[l][i] = false;
        }
    }

    bool depassement;
    int y_periodique = 0;
    int x_periodique = 0;

    for (int j = c_pos_y - vision; j < c_pos_y + vision + 1; ++j) {
        for (int i = c_pos_x - vision; i < c_pos_x + vision + 1; ++i) {
            depassement = false;
            y_periodique = j;
            x_periodique = i;
            if (j < 0) {
                y_periodique = (HAUTEUR - 1) + (j + 1);
                cases_vision[y_periodique][i] = true;
                depassement = true;
            } else if (j > (HAUTEUR - 1)) {
                //PSEUDO
                // SI PB EN I :
                //SINON :
                // Utilisation de %??
                // new
                y_periodique = j - (HAUTEUR);
                cases_vision[y_periodique][i] = true; // PB pas de verif sur i, utilisation de %?
                depassement = true;
            }

            //work to do here
            if (i < 0) {
                // new2
                x_periodique = (HAUTEUR - 1) + (i + 1);
                cases_vision[j][x_periodique] = true;
                depassement = true;
            } else if (i > (HAUTEUR - 1)) {
                x_periodique = i - (HAUTEUR);
                cases_vision[j][x_periodique] = true;
                depassement = true;
            }

            // Maybe a special case for each corner..
            // Tried that -> no effect
            // Bottom right corner
            /*
            if (i > (HAUTEUR - 1) && j > i > (HAUTEUR - 1)) {
                cases_vision[y_periodique][x_periodique] = true;
            }
            */

            if (!depassement) {
                cases_vision[j][i] = true;
            }

            if (!grid[y_periodique][x_periodique]) {
                if (j == c_pos_y - 1 && i == c_pos_x + 2) {
                    cases_vision[y_periodique][x_periodique] = -1;
                } else if (j == c_pos_y - 2 && i == c_pos_x + 1) {
                    cases_vision[y_periodique][x_periodique] = 2;
                } else if (j == c_pos_y - 2 && i == c_pos_x - 1) {
                    cases_vision[y_periodique][x_periodique] = 3;
                } else if (j == c_pos_y - 1 && i == c_pos_x - 2) {
                    cases_vision[y_periodique][x_periodique] = 4;
                } else if (j == c_pos_y + 1 && i == c_pos_x - 2) {
                    cases_vision[y_periodique][x_periodique] = 5;
                } else if (j == c_pos_y + 2 && i == c_pos_x - 1) {
                    cases_vision[y_periodique][x_periodique] = 6;
                } else if (j == c_pos_y + 2 && i == c_pos_x + 1) {
                    cases_vision[y_periodique][x_periodique] = 7;
                } else if (j == c_pos_y + 1 && i == c_pos_x + 2) {
                    cases_vision[y_periodique][x_periodique] = 8;
                }
            }


        }
    }


    printf("\n");
    for (int y = 0; y < HAUTEUR; ++y) {
        //printf("|");
        for (int x = 0; x < LARGEUR; ++x) {
            if (cases_vision[y][x]) {
                if (grid[y][x]) {
                    printf("%c", grid[y][x]);
                } else if (cases_vision[y][x] != 1) {
                    // code spécial pour 1 care 1 == true, on note la position 1 par -1 dans case visions
                    if (cases_vision[y][x] == -1) {
                        printf("1");
                    } else {
                        printf("%d", cases_vision[y][x]);
                    }
                } else {
                    printf(" ");
                }
            } else {
                if (DEBUG) {
                    printf("%c", grid[y][x]);
                } else {
                    printf("%c", 254); // 254 est le caractère carre  : ■
                }
            }
            printf(" ");
        }
        printf("\n");
    }

    printf("c_pos_y = %d, c_pos_x = %d\n",c_pos_y, c_pos_x);

}


/* Renvoie les coordonnees de la futur position */
void choixToXY(int c_pos_x, int c_pos_y, int f_pos, int *futur_x, int *futur_y)
{

    switch (f_pos) {
    case 1:
        *futur_y = c_pos_y - 1;
        *futur_x = c_pos_x + 2;

        break;
    case 2:
        *futur_y = c_pos_y - 2;
        *futur_x = c_pos_x + 1;
        if (*futur_y < 0) {

            break;
        case 3:
            *futur_y = c_pos_y - 2;
            *futur_x = c_pos_x - 1;

            break;
        case 4:
            *futur_y = c_pos_y - 1;
            *futur_x = c_pos_x - 2;

            break;
        case 5:
            *futur_y = c_pos_y + 1;
            *futur_x = c_pos_x - 2;

            break;
        case 6:
            *futur_y = c_pos_y + 2;
            *futur_x = c_pos_x - 1;

            break;
        case 7:
            *futur_y = c_pos_y + 2;
            *futur_x = c_pos_x + 1;

            break;
        case 8:
            *futur_y = c_pos_y + 1;
            *futur_x = c_pos_x + 2;

            break;
        default:
            break;
        }
    }
}

void periodize(int *futur_x, int *futur_y)
{
    if (*futur_y < 0) {
        *futur_y = (HAUTEUR - 1) + (*futur_y + 1);
    }
    if (*futur_y > (HAUTEUR - 1)) {
        *futur_y = *futur_y - (HAUTEUR);
    }
    if (*futur_x < 0) {
        *futur_x = (HAUTEUR - 1) + (*futur_x + 1);
    }
    if (*futur_x > (HAUTEUR - 1)) {
        *futur_x = *futur_x - (HAUTEUR);
    }
}


void move(char grid[LARGEUR][HAUTEUR], int *c_pos_x, int *c_pos_y, int f_pos, char mode)
{
    int futur_x;
    int futur_y;
    int x_tmp;
    int y_tmp;
    choixToXY(*c_pos_x, *c_pos_y, f_pos, &futur_x, &futur_y);
    if (mode == 'P') {
        periodize(&futur_x, &futur_y);
    }

    if (mode == 'C') {
        if (futur_x < 0 || futur_x > HAUTEUR - 1 || futur_y < 0 || futur_y > HAUTEUR - 1) {
            /* Pas de deplacement */
            futur_x = *c_pos_x;
            futur_y = *c_pos_y;
        }
    }

    switch (grid[futur_y][futur_x]) {
    case 'T':
        WON = true;
        break;
    case 'B':
        VISION_BONUS++;

        grid[*c_pos_y][*c_pos_x] = 0;
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        grid[*c_pos_y][*c_pos_x] = 'C';
        break;
    case 'X':
        break;
    case 'D':
        /* placement du chevalier */


        grid[*c_pos_y][*c_pos_x] = 0;
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        grid[*c_pos_y][*c_pos_x] = 'C';

        /* placement de deuxieme cible */
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        grid[x_tmp][y_tmp] = 'T';
    case 'W':
        /* placement du chevalier */
        do {
            futur_y = hasard(0, 15);
            futur_x = hasard(0, 15);
        } while (grid[futur_y][futur_x]);
        grid[futur_y][futur_x] = 'C';
        // remise a 0 de l'ancienne position
        grid[*c_pos_y][*c_pos_x] = 0;
    case 'C' : /* Sortie de la grille en mode classique, la position ne change pas et le nombre d'iteration reste inchangé */
        ITER--;
    default:
        grid[*c_pos_y][*c_pos_x] = 0;
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        grid[*c_pos_y][*c_pos_x] = 'C';
        break;
    }

    ITER++;
}


int main()
{
    initialise_rand();

    printf("**************** JEU DU CHEVALIER ****************\n");
    printf("*                                                *\n");
    printf("*     Deplacez le pion C jusqu'a la case T       *\n");
    printf("*                                                *\n");
    printf("*       'R' a tout moment pour recommencer       *\n");
    printf("*                                                *\n");
    printf("**************** BONNE PARTIE ! ******************\n");

    bool Quit = false;
    bool Restart = false;
    char restart;
    // C = classic; P = Periodique
    char mode = 'C';

    printf("\n\n\nChoix du mode : (C=Classique, P=Periodique) : \n");
    do {
        scanf(" %c", &mode);
    } while (mode != 'C' && mode != 'P');

    int chevalier_pos_x = hasard(5, 10);
    int chevalier_pos_y = hasard(5, 10);


    int futur_pos = 0;
    char grid[HAUTEUR][LARGEUR];


    init_grid(grid, NB_OBSTACLES, NB_BONUS, chevalier_pos_x, chevalier_pos_y, NB_WARP,
              NB_DUPLICATE, NB_MALUS);

    do {
        if (WON) {
            //system("cls");
            printf("**************** JEU DU CHEVALIER ****************\n");
            printf("*                                                *\n");
            printf("*                   BRAVO !                      *\n");
            printf("*                                                *\n");
            printf("*       Vous avez gagne en %d iterations !      *\n", ITER);
            printf("*                                                *\n");
            printf("************** 'R' pour recommencer **************\n");
            scanf(" %c", &restart);
            if (restart == 'R') {
                Restart = true;
            } else {
                Quit = true;
            }

        }
        if (Restart) {
            chevalier_pos_x = hasard(5, 10);
            chevalier_pos_y = hasard(5, 10);
            VISION_BONUS = 0;
            ITER = 0;
            WON = false;
            printf("Choix du mode (Classique = C, Periodique = P) : \n");
            do {
                scanf(" %c", &mode);
            } while (mode != 'C' && mode != 'P');

            init_grid(grid, NB_OBSTACLES, NB_BONUS, chevalier_pos_x, chevalier_pos_y, NB_WARP,
                      NB_DUPLICATE, NB_MALUS);
            Restart = false;
        }
        if (Quit) {
            printf("Fin du programme..\n");
            return 0;
        }
        if (mode == 'P') {
            output_grid_periodique(grid, chevalier_pos_x, chevalier_pos_y);
        } else if (mode == 'C') {
            output_grid_classique(grid, chevalier_pos_x, chevalier_pos_y);
        } else {
            printf("MODE ERROR : %c\n", mode);
        }
        printf("\n");
        printf("Prochaine position (R pour recommencer) : ");

        // On aurait pu se simplifier la vie en utilisant char futur_pos, le scan fonctionne ensuite dans tout les cas
        // Ici on utilise le fait que scan f retourne un entier correspondant au nombre d'arguments lu
        // Si on entre 'R', scanf("%d") retourne 0 <=> faux
        if (scanf("%d", &futur_pos)) {
            move(grid, &chevalier_pos_x, &chevalier_pos_y, futur_pos,
                 mode); // note : mode pourrait etre globale
            //system("clear");

            // On peut alors scanner pour un caractere
        } else if (scanf(" %c", &restart)) {
            if (restart == 'R') {
                Restart = true;
            }
            // permet d'enter en mode debug
            if (restart == 'D') {
                DEBUG = true;
            }

        }

    } while (!Quit);

    return 0;
}
