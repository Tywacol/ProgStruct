#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // peut etre à la fin plus propre

#define LARGEUR 16
#define HAUTEUR 16

#define NB_OBSTACLES 8
#define NB_BONUS 2

/* Variables global */

int VISION_BONUS = 0;
int ITER = 0;
bool WON = false;

/*
* Remplir un tableau de taille N avec
* des entiers positifs inférieurs à 100
*/

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

void init_grid(char grid[HAUTEUR][LARGEUR], int nb_obstacles, int nb_bonus, int c_pos_x, int c_pos_y)
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

    /* placement des bonus */
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


}

/* affiche une tableau */
void output_grid(char grid[HAUTEUR][LARGEUR], int c_pos_x, int c_pos_y)
{
    int vision = 2 + VISION_BONUS;

    
    /* ligne du haut */
    for (int k = 0; k < LARGEUR; ++k) {
        printf(" _");
    }

    printf("\n");
    for (int y = 0; y < HAUTEUR; ++y) {
        printf("|");
        for (int x = 0; x < LARGEUR; ++x) {
            if (y <= c_pos_y + vision && y >= c_pos_y - vision
                && x <= c_pos_x + vision && x >= c_pos_x - vision) {
                if (grid[y][x]) {
                    printf("%c", grid[y][x]);
                } else if (y == c_pos_y - 1 && x == c_pos_x + 2) {
                    printf("1");
                } else if (y == c_pos_y - 2 && x == c_pos_x + 1) {
                    printf("2");
                } else if (y == c_pos_y - 2 && x == c_pos_x - 1) {
                    printf("3");
                } else if (y == c_pos_y - 1 && x == c_pos_x - 2) {
                    printf("4");
                } else if (y == c_pos_y + 1 && x == c_pos_x - 2) {
                    printf("5");
                } else if (y == c_pos_y + 2 && x == c_pos_x - 1) {
                    printf("6");
                } else if (y == c_pos_y + 2 && x == c_pos_x + 1) {
                    printf("7");
                } else if (y == c_pos_y + 1 && x == c_pos_x + 2) {
                    printf("8");
                } else {
                    printf(" ");
                }
            } else {
                printf("%c", 254);
            }
            printf(".");
        }
        printf("|\n");

    }
}

void choixToXY(int c_pos_x, int c_pos_y, int f_pos, int *futur_x, int *futur_y)
{
    // Convertit la position
    switch (f_pos) {
    case 1:
        *futur_y = c_pos_y - 1;
        *futur_x = c_pos_x + 2;
        break;
    case 2:
        *futur_y = c_pos_y - 2;
        *futur_x = c_pos_x + 1;
        break;
    case 3:
        *futur_y = c_pos_y - 2;
        *futur_x = c_pos_x + 1;
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
        *futur_x = c_pos_x + -1;
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


void move(char grid[LARGEUR][HAUTEUR], int *c_pos_x, int *c_pos_y, int f_pos)
{
    int futur_x;
    int futur_y;
    printf("avant conversion. c_pos_x = %d, c_pos_y = %d\n", *c_pos_x, *c_pos_y);
    choixToXY(*c_pos_x, *c_pos_y, f_pos, &futur_x, &futur_y);
    printf("apres conversion. c_pos_x = %d, c_pos_y = %d,\n futur_x = %d,"
           " futur_y = %d\n", *c_pos_x, *c_pos_y, futur_x, futur_y);
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
    printf("**************** BONNE PARTIE ! *****************\n");

    bool Quit = false;
    bool Restart = false;

    int chevalier_pos_x = hasard(5, 10);
    int chevalier_pos_y = hasard(5, 10);


    int futur_pos = 1;
    char grid[HAUTEUR][LARGEUR];
    init_grid(grid, NB_OBSTACLES, NB_BONUS, chevalier_pos_x, chevalier_pos_y);

    do {
        if (WON) {
            //system("cls");
            printf("**************** JEU DU CHEVALIER ****************\n");
            printf("*                                                *\n");
            printf("*             BRAVO ! Vous avez gagne en         *\n");
            printf("*                                                *\n");
            printf("*                 %d iterations !                *\n", ITER);
            printf("*                                                *\n");
            printf("************** 'R' pour recommencer **************\n");
            WON = false;
        }
        if (Restart) {
            chevalier_pos_x = hasard(5, 10);
            chevalier_pos_y = hasard(5, 10);
            init_grid(grid, NB_OBSTACLES, NB_BONUS, chevalier_pos_x, chevalier_pos_y);
        }
        if (Quit) {
            printf("Fin du programme..\n");
            return 0;
        }
        output_grid(grid, chevalier_pos_x, chevalier_pos_y);
        printf("\n");
        printf("Prochaine position (R pour recommencer) : ");
        scanf("%d", &futur_pos);
        Restart = (futur_pos == 'R');

        move(grid, &chevalier_pos_x, &chevalier_pos_y, futur_pos);
        //system("clear");
    } while (!WON && !Quit && !Restart);

    return 0;
}

