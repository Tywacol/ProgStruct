#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* DIMENSIONS */
#define LARGEUR 16
#define HAUTEUR 16

#define NB_WARP 2
#define NB_DUPLICATE 1
#define NB_MALUS 1
#define NB_OBSTACLE_NORMAL 8
#define NB_BONUS_NORMAL 2

/* Variables global */
int NB_OBSTACLES = NB_OBSTACLE_NORMAL;
int NB_BONUS = NB_BONUS_NORMAL;
int VISION_BONUS = 0;
int ITER = 0;
/* Coordonnees de la cible */
int CIBLE_X;
int CIBLE_Y;
bool DEBUG = false; /* Mettre a vrai pour obtenir la vision globale */
bool WON = false;
bool LOST = false;
bool CIBLE_MOBILE = true;
/* -1 pour que la condition if (TOMBE_SUR_MALUS == y)
* soit fausse tant que le joueur n'est pas tombe sur un malus */
int TOMBE_SUR_MALUS = -1;


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


/* Place les different case dans la grille du jeu */
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
        CIBLE_X = hasard(0, 15);
        CIBLE_Y = hasard(0, 15);
    } while (grid[CIBLE_Y][CIBLE_X]);
    grid[CIBLE_Y][CIBLE_X] = 'T';

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

/* affiche une tableau
 * version : CLASSIQUE
 */
void output_grid_classique(char grid[HAUTEUR][LARGEUR], int c_pos_x, int c_pos_y)
{
    int vision = 2 + VISION_BONUS;

    /* Deuxième tableau stockant la position des cases sur lequel le joueur
     * possède la vision
     */
    int cases_vision[HAUTEUR][HAUTEUR];
    for (int l = 0; l < HAUTEUR; ++l) {
        for (int i = 0; i < HAUTEUR; ++i) {
            cases_vision[l][i] = false;
        }
    }

    bool depassement;
    int y_periodique = 0;
    int x_periodique = 0;

    /* Determination des 24 cases visibles autour du cavalier */
    for (int j = c_pos_y - vision; j < c_pos_y + vision + 1; ++j) {
        for (int i = c_pos_x - vision; i < c_pos_x + vision + 1; ++i) {
            depassement = false;
            /* variable gerant les depassement */
            y_periodique = j;
            x_periodique = i;
            if (j < 0) {
                depassement = true;
            } else if (j > (HAUTEUR - 1)) {
                depassement = true;
            }

            if (i < 0) {
                depassement = true;
            } else if (i > (HAUTEUR - 1)) {
                depassement = true;
            }
            if (!depassement) {
                cases_vision[j][i] = true;
            }

            /* Placement des numero de deplacemenent directement dans cases_visions
             * On disitingue 3 cas dans cases visions :
             * 1 - cases_vision[y][x] = false -> pas de vision
             * 2 - cases_vision[y][x] > 0 -> vision
             * 2 bis - cases_vision[y][x] != 1 et != 0-> cases_vision note le numero de deplacement qu'on
             * affiche si la grille est vide a cet endroit
             */
            if (!grid[y_periodique][x_periodique] && cases_vision[y_periodique][x_periodique]) {
                if (j == c_pos_y - 1 && i == c_pos_x + 2) {
                    cases_vision[y_periodique][x_periodique] = -1; /* 1 = true donc code special */
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

    /* affichage de la grille en fonction de la vision */
    printf("\n");
    for (int y = 0; y < HAUTEUR; ++y) {
        for (int x = 0; x < LARGEUR; ++x) {
            if (DEBUG) {
                printf("|");
            }
            if (cases_vision[y][x]) {
                if (grid[y][x]) {
                    /* Case T piege, si le joueur est tombe sur le malus */
                    if (grid[y][x] == 'P') {
                        if (!DEBUG) {
                            printf("T");
                        } else {
                            printf("P");
                        }
                    } else if (grid[y][x] == 'M') {
                        if (!DEBUG) {
                            printf("B");
                        } else {
                            printf("M");
                        }
                    } else {
                        printf("%c", grid[y][x]);
                    }
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
        if (TOMBE_SUR_MALUS == y) {
            printf("\t/!\\ Ce BONUS etait un MALUS ! Un 'T' piege a ete ajoute..!");
            TOMBE_SUR_MALUS = false;
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
            /* On test sur y pour sur i pour etre sur de ne pas depasser les bornes de cases_vision */
            if (j < 0) {
                y_periodique = (HAUTEUR - 1) + (j + 1);

                if (i < 0) {
                    x_periodique = (HAUTEUR - 1) + (i + 1);
                } else if (i > (HAUTEUR - 1)) {
                    x_periodique = i - (HAUTEUR);
                }
                cases_vision[y_periodique][x_periodique] = true;
                depassement = true;
            } else if (j > (HAUTEUR - 1)) {
                y_periodique = j - (HAUTEUR);

                if (i < 0) {
                    x_periodique = (HAUTEUR - 1) + (i + 1);
                } else if (i > (HAUTEUR - 1)) {
                    x_periodique = i - (HAUTEUR);
                }

                cases_vision[y_periodique][x_periodique] = true;
                depassement = true;
            }

            /*
             * pas besoin de tester en y car c'est fait au dessus
             * on verifie juste si le x dépasse
             */
            if (i < 0) {
                x_periodique = (HAUTEUR - 1) + (i + 1);
                cases_vision[y_periodique][x_periodique] = true;
                depassement = true;
            } else if (i > (HAUTEUR - 1)) {
                x_periodique = i - (HAUTEUR);
                cases_vision[y_periodique][x_periodique] = true;
                depassement = true;
            }

            if (!depassement) {
                cases_vision[j][i] = true;
            }

            /* Placement des numero de deplacemenent directement dans cases_visions
             * On disitingue 3 cas dans cases visions :
             * 1 - cases_vision[y][x] = false -> pas de vision
             * 2 - cases_vision[y][x] > 0 -> vision
             * 2 bis - cases_vision[y][x] != 1 et != 0-> cases_vision note le numero de deplacement qu'on
             * affiche si la grille est vide a cet endroit
             */
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

    /* affichage de la grille en fonction de la vision */
    printf("\n");
    for (int y = 0; y < HAUTEUR; ++y) {
        for (int x = 0; x < LARGEUR; ++x) {
            if (DEBUG) {
                printf("|");
            }
            if (cases_vision[y][x]) {
                if (grid[y][x]) {
                    /* Case T piege, si le joueur est tombe sur le malus */
                    if (grid[y][x] == 'P') {
                        if (!DEBUG) {
                            printf("T");
                        } else {
                            printf("P");
                        }
                    } else if (grid[y][x] == 'M') {
                        if (!DEBUG) {
                            printf("B");
                        } else {
                            printf("M");
                        }
                    } else {
                        printf("%c", grid[y][x]);
                    }
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
        if (TOMBE_SUR_MALUS == y) {
            printf("\t/!\\ Ce BONUS etait un MALUS ! Un 'T' piege a ete ajoute..!");
            TOMBE_SUR_MALUS = false;
        }
        printf("\n");
    }

}


/* Renvoie les coordonnees de la futur position en fonction de la position
 * de chevalier et du choix du joueur
 */
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

/* renvoie les futur coordonne corrige en fonction des depassement
 * pour la version periodique du jeu */
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

/* deplacement du chevalier et resolution de l'effet des cases */
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

        /* placement du chevalier */
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
        break;
    case 'W':
        /* placement du chevalier */
        do {
            futur_y = hasard(0, 15);
            futur_x = hasard(0, 15);
        } while (grid[futur_y][futur_x]);
        grid[futur_y][futur_x] = 'C';
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        /* remise a 0 de l'ancienne position */
        grid[*c_pos_y][*c_pos_x] = 0;
        break;
    case 'C' : /* Sortie de la grille en mode classique, la position ne change pas et le nombre d'iteration reste inchangé */
        ITER--;
        break;
    case 'M':
        TOMBE_SUR_MALUS = futur_y;
        /* placement du chevalier */
        grid[*c_pos_y][*c_pos_x] = 0;
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        grid[*c_pos_y][*c_pos_x] = 'C';
        /* placement de la cible piegee */
        do {
            x_tmp = hasard(0, 15);
            y_tmp = hasard(0, 15);
        } while (grid[x_tmp][y_tmp]);
        /* P pour piege, sera affiche comme un T, si le joueur tombe dessus il perd. Pas de chance ! */
        grid[x_tmp][y_tmp] = 'P';
        break;
    case 'P':
        LOST = true;
        break;
    default:
        grid[*c_pos_y][*c_pos_x] = 0;
        *c_pos_x = futur_x;
        *c_pos_y = futur_y;
        grid[*c_pos_y][*c_pos_x] = 'C';
        break;
    }

    /* On essaie de faire bouger la cible suivant la place dans l'ordre suivant :
     *      1
     *    4 T 2
     *      3
     * neanmoins le premier numero tire est aléatoire */
    int roll = hasard(1, 4);
    int nb_tests = 0;
    /* variable pour la gestion des depassement */
    int cible_y_per = CIBLE_Y;
    int cible_x_per = CIBLE_X;
    bool cible_deplacee = false;
    if (CIBLE_MOBILE) {
        do {
            switch (roll) {
            case 1:
                if ((CIBLE_Y - 1) < 0) {
                    cible_y_per = HAUTEUR - 1;
                } else {
                    cible_y_per = CIBLE_Y - 1;
                }
                /* deplacement si la case suivante est vide */
                if (!grid[cible_y_per][CIBLE_X]) {
                    grid[CIBLE_Y][CIBLE_X] = 0;
                    CIBLE_Y = cible_y_per;
                    grid[cible_y_per][CIBLE_X] = 'T';
                    cible_deplacee = true;
                } else {
                    ++roll;
                    ++nb_tests;
                }
                break;
            case 2:
                if ((CIBLE_X + 1) > HAUTEUR - 1) {
                    cible_x_per = CIBLE_X + 1 - HAUTEUR; /* <=> 0 */
                } else {
                    cible_x_per = CIBLE_X + 1;
                }
                /* deplacement si la case suivante est vide */
                if (!grid[CIBLE_Y][cible_x_per]) {
                    grid[CIBLE_Y][CIBLE_X] = 0;
                    CIBLE_X = cible_x_per;
                    grid[CIBLE_Y][CIBLE_X] = 'T';
                    cible_deplacee = true;
                } else {
                    ++roll;
                    ++nb_tests;
                }
                break;
            case 3:
                if ((CIBLE_Y + 1) > HAUTEUR - 1) {
                    cible_y_per = CIBLE_Y + 1 - HAUTEUR; /* <=> 0 */
                } else {
                    cible_y_per = CIBLE_Y + 1;
                }
                if (!grid[cible_y_per][CIBLE_X]) {
                    grid[CIBLE_Y][CIBLE_X] = 0;
                    CIBLE_Y = cible_y_per;
                    grid[CIBLE_Y][CIBLE_X] = 'T';
                    cible_deplacee = true;
                } else {
                    ++roll;
                    ++nb_tests;
                }
                break;
            case 4:
                if ((CIBLE_X - 1) < 0) {
                    cible_x_per = HAUTEUR - 1;
                } else {
                    cible_x_per = CIBLE_X - 1;
                }
                /* deplacement si la case suivante est vide */
                if (!grid[CIBLE_Y][cible_x_per]) {
                    grid[CIBLE_Y][CIBLE_X] = 0;
                    CIBLE_X = cible_x_per;
                    grid[CIBLE_Y][CIBLE_X] = 'T';
                    cible_deplacee = true;
                } else {
                    roll = 1; /* boucle */
                    ++nb_tests;
                }
                break;
            default :
                break;
            }
            /* Si aucun deplacement n'est possible la cible ne bouge pas */
        } while (!cible_deplacee && nb_tests < 4);
    }
    /* icrementation du nombre d'iteration */
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
    /* C = classic; P = Periodique */
    char mode = 'C';
    int diff = 0;

    printf("\n\n\nChoix du mode : (C=Classique, P=Periodique) : \n");
    do {
        scanf(" %c", &mode);
    } while (mode != 'C' && mode != 'P');

    printf("Choix de la difficulte (0..10, 0=EASY, 5=NORMAL, 10=HARD) : \n");
    do {
        scanf(" %d", &diff);
    } while (diff < 0 || diff > 20); /* Easter egg : il existe 10 autres niveaux plus durs que HARD */
    if (diff < 5) {
        NB_BONUS = NB_BONUS_NORMAL * (5 - diff);
    } else if (diff > 5) {
        NB_OBSTACLES = NB_OBSTACLE_NORMAL * (diff - 5);
    } else { /* diff = 5 */
        NB_BONUS = NB_BONUS_NORMAL;
        NB_OBSTACLES = NB_OBSTACLE_NORMAL;
    }


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

        if (LOST) {
            //system("cls");
            printf("**************** JEU DU CHEVALIER ****************\n");
            printf("*                                                *\n");
            printf("*                   PERDU !                      *\n");
            printf("*            LA CIBLE ETAIT PIEGEE               *\n");
            printf("*                                                *\n");
            printf("*       Vous avez perdu en %d iterations !       *\n", ITER);
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
            /* remise à 0 des variables globales */
            chevalier_pos_x = hasard(5, 10);
            chevalier_pos_y = hasard(5, 10);
            VISION_BONUS = 0;
            ITER = 0;
            WON = false;
            LOST = false;
            VISION_BONUS = 0;
            ITER = 0;


            printf("Choix du mode : (C=Classique, P=Periodique) : \n");
            do {
                scanf(" %c", &mode);
            } while (mode != 'C' && mode != 'P');

            printf("Choix de la difficulte (0..10, 0=EASY, 5=NORMAL, 10=HARD) : \n");
            do {
                scanf(" %d", &diff);
            } while (diff < 0 || diff > 20); /* Easter egg : il existe 10 autres niveaux plus durs que HARD */
            if (diff < 5) {
                NB_BONUS = NB_BONUS_NORMAL * (5 - diff);
                NB_OBSTACLES = NB_OBSTACLE_NORMAL;
            } else if (diff > 5) {
                NB_BONUS = NB_BONUS_NORMAL;
                NB_OBSTACLES = NB_OBSTACLE_NORMAL * (diff - 5);
            } else { // diff = 5
                NB_BONUS = NB_BONUS_NORMAL;
                NB_OBSTACLES = NB_OBSTACLE_NORMAL;
            }

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
        printf("Prochaine position (R pour recommencer, D pour debugger) : ");

        /* On aurait pu se simplifier la vie en utilisant char futur_pos, le scan fonctionne ensuite dans tout les cas
         * Ici on utilise le fait que scan f retourne un entier correspondant au nombre d'arguments lu
         * Si on entre 'R', scanf("%d") retourne 0 <=> faux
         */
        if (scanf("%d", &futur_pos)) {
            move(grid, &chevalier_pos_x, &chevalier_pos_y, futur_pos,
                 mode);

            /* On peut alors scanner pour un caractere */
        } else if (scanf(" %c", &restart)) {
            if (restart == 'R') {
                Restart = true;
            }
                /* permet d'enter/sortir du mode debug */
            else if (restart == 'D') {
                DEBUG = !DEBUG;
            }

        }

    } while (!Quit);

    return 0;
}
