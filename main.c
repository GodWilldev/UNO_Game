#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.c"
#define Malloc(type, N) (type*)malloc(N*sizeof(type))
#define Free(pt) free(pt)


int main()
{
    srand((time(NULL)));    //initialisation du générateur de nombre aléatoire

    int i, k;
    carte J1[40]; int nbrCarteJ1 = 0;
    carte J2[40]; int nbrCarteJ2 = 0;
    carte table[40]; int nbrCarteTbl = 0;
    int nbrCarteStk;


/***DEBUT DE LA PARTIE***/

    printf("\t\t\t*************************************\t\t\t\n");
    printf("\t\t\t*******  JEU DE CARTES 'UNO'  *******\t\t\t\n");
    printf("\t\t\t*************************************\t\t\t\n");
    printf("\nBienvenue a cette nouvelle partie.\n");
    printf("\nAu cours de cette partie vous pouvez passer votre tour en tapant sur 0\n");
    printf("\nOn commence!\n\n");
    printf("---------------------------------Distribution des cartes--------------------------------\n\n");

    distribuer(J1, J2, table, &nbrCarteJ1, &nbrCarteJ2, &nbrCarteTbl);

    /***SUITE ET FIN***/
    int tour = 0;
    int *n, *m;
    char x[4], c[2];
    carte X;
    carte *p = Malloc(carte, 40);   //pointeur sur le joueur qui joue
    carte *q = Malloc(carte, 40);   //pointeur sur l'autre joueur
    carte *pt = Malloc(carte, 40);  //pointeur sur la table


    printf("\n-----------------------------------JOUEUR%d----------------------------------------------\n", (tour%2)+1);
    printf("A vous de jouer joueur%d. ||Table: %c%d||\n", (tour%2)+1, table[nbrCarteTbl-1].coul, table[nbrCarteTbl-1].num);
    p = J1; n = &nbrCarteJ1; pt = table;
    afficherCartesJ(p, *n);
            do{
                scanf("%s", x);
                if(x[0] != '0' && carteNonValide(p, *n, x, pt, nbrCarteTbl))
                    printf("Carte non valide\n");
                else
                    break;
            }while(1);

    while(nbrCarteJ1 != 0 && nbrCarteJ2 != 0)
    {
        nbrCarteStk = 40-nbrCarteJ1-nbrCarteJ2-nbrCarteTbl;
        if(nbrCarteStk <= 2)
        {//Si le stock est presque vide on remelange toutes les cartes
            table[0].num = table[nbrCarteTbl-1].num;
            table[0].coul = table[nbrCarteTbl-1].coul;
            nbrCarteTbl = 1;
        }

        pt = table;
        if((tour%2)+1 == 1) {p = J1; q = J2; n = &nbrCarteJ1; m = &nbrCarteJ2;}
        else    {p = J2; q = J1; n = &nbrCarteJ2; m = &nbrCarteJ1;}



        if(x[0] == '0')
        {//PASSER TOUR
            donnerCarte(&p, J1, J2, table, n, nbrCarteJ1, nbrCarteJ2, nbrCarteTbl);
            //*n = *n+1;
            afficherCartesJ(p, *n);
            tour++;
        }

        else if(x[1] == '2')
        {//donner 2 cartes
            actualiseTable(&pt, &nbrCarteTbl, x);
            //nbrCarteTbl++;
            supprimer(&p, n, &pt, nbrCarteTbl);
            //*n = *n-1;
            if(nbrCarteJ1 == 0 || nbrCarteJ2 == 0)
                break;

            donnerCarte(&q, J1, J2, table, m, nbrCarteJ1, nbrCarteJ2, nbrCarteTbl);
            //*m = *m+1;
            donnerCarte(&q, J1, J2, table, m, nbrCarteJ1, nbrCarteJ2, nbrCarteTbl);
            //*m = *m+1;

            afficherCartesJ(p, *n);
            tour++;
        }

        else if(x[1] == '7')
        {//choisir une couleur
            actualiseTable(&pt, &nbrCarteTbl, x);
            supprimer(&p,n, &pt, nbrCarteTbl);
            if(nbrCarteJ1 == 0 || nbrCarteJ2 == 0) break;
            do{
                printf("Choisissez une couleur: R, V, B, J \n");
                scanf("%s", c);
            }while(c!='B' && c!='V' && c!='J' && c!='R');
            afficherCartesJ(p, *n);
            tour++;
            printf("\n-----------------------------------JOUEUR%d----------------------------------------------\n", (tour%2)+1);
            printf("A vous de jouer joueur%d:\n", (tour%2)+1);
            afficherCartesJ(q, *m);

            do{
                printf("Vous devez mettre une carte de couleur %s: \n", c);
                scanf("%s", x);
            }while((x[0] != c[0] && x[0] != '0'));
            continue;

        }
        else if(x[1] == '1' && x[2] == '\0')
        {
            actualiseTable(&pt, &nbrCarteTbl, x);
            //nbrCarteTbl++;
            supprimer(&p,n, &pt, nbrCarteTbl);
            //*n = *n-1;
            if(nbrCarteJ1 == 0 || nbrCarteJ2 == 0)
                break;

            afficherCartesJ(p, *n);

            printf("\n***Jouez encore joueur%d. ||Table: %c%d||\n", (tour%2)+1, table[nbrCarteTbl-1].coul, table[nbrCarteTbl-1].num);
            afficherCartesJ(p, *n);
            do{
                scanf("%s", x);
                if(x[0] != '0' && carteNonValide(p, *n, x, pt, nbrCarteTbl))
                    printf("Carte non valide\n");
                else
                    break;
            }while(1);
            continue;
        }

        else
        {
            actualiseTable(&pt, &nbrCarteTbl, x);
            //nbrCarteTbl++;
            supprimer(&p, n, &pt, nbrCarteTbl);
            //*n = (*n)-1;
            if(nbrCarteJ1 == 0 || nbrCarteJ2 == 0)
                break;
            afficherCartesJ(p, *n);
            tour++;
        }

        printf("\n-----------------------------------JOUEUR%d----------------------------------------------\n", (tour%2)+1);
        printf("A vous de jouer joueur%d. ||Table: %c%d||\n", (tour%2)+1, table[nbrCarteTbl-1].coul, table[nbrCarteTbl-1].num);
        afficherCartesJ(q, *m);
        do{
            scanf("%s", x);
            if(x[0] != '0' && carteNonValide(q, *m, x, pt, nbrCarteTbl))
                printf("Carte non valide\n");
            else
                break;
        }while(1);
    }

    printf("\n\nFELICITATIONS!  LE JOUEUR%d A GAGNE\n", Gagnant(nbrCarteJ1, nbrCarteJ2));

    Free(p);
    Free(q);
    Free(pt);

    return 0;
}
