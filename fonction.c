#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"

char tabCoul[] = {'0', 'R', 'V', 'B', 'J'};


int aleatoire(int n)
{/**Nous renvoie aléatoirement un entier entre 1 et n**/
    return (rand()%n) +1;
}

int carteDans(carte X, carte A[], int n)
{/**Recherche si une carte x est présent dans un tableau de carte A(de taille n)**/
    //retourne 1 si oui 0 si non
    int i;
    for(i=0; i<n; i++){
        if(A[i].num == X.num && A[i].coul == X.coul)
            return 1;
    }
    return 0;
}
int siDeja(carte X, carte Jou1[], carte Jou2[], carte Tabl[], int n, int m, int t)
{/**vérifie si la carte x est déjà présente dans le jeu( chez J1, J2, ou la table)**/
    //retourne 1 si oui 0 si non
    if( !carteDans(X, Jou1, n) && !carteDans(X, Jou2, m) && !carteDans(X, Tabl, t))
       return 0;
    else
        return 1;
}

void distribuer(carte J1[], carte J2[], carte table[], int* a, int* b, int* t)
{/**les cartes sont initialements distribuées au hazard aux joueurs et une carte sur la table**/
    int i;
    printf("Joueur1 voici vos cartes: ");
    //joueur 1
    for(i=0; i<4; i++)
    {
        do{
            J1[i].num = aleatoire(10);
            J1[i].coul = tabCoul[aleatoire(4)];
        }while(carteDans(J1[i], J1, *a));
        printf("%c%d  ", J1[i].coul, J1[i].num);
        (*a)++;
    }
    printf("\n\nJoueur2 voici vos cartes: ");
    //joueur 2
    for(i=0; i<4; i++)
    {

        do{
            J2[i].num = aleatoire(10);
            J2[i].coul = tabCoul[aleatoire(4)];
        }while(carteDans(J2[i], J2, *b) || carteDans(J2[i], J1, *b));
        printf("%c%d  ", J2[i].coul, J2[i].num);
        (*b)++;
    }

    printf("\n\n*Carte sur la table: ");

    do{
            table[0].num = aleatoire(10);
            table[0].coul = tabCoul[aleatoire(4)];
    }while(carteDans(table[0], J1, *a) || carteDans(table[0], J2, *b));
    *t = 1;
    printf("%c%d\n", table[0].coul, table[0].num);
}

void afficherCartesJ(carte A[], int n)
{/**affiche toutes les cartes d’un joueur (J1 ou J2)**/
    int i;
    printf("Vos cartes: ");
    for(i=0; i<n; i++)
        {printf("%c%d  ", A[i].coul, A[i].num);}
    printf("\n");
}

carte convert(char x[], carte X)
{/**Convertit une carte entrée sous forme de chaine de caractère en structure carte**/

    char xcopie[4];
    strcpy(xcopie, x);

    X.coul = xcopie[0];
    int i=0;
    while(xcopie[i] != '\0')
    {
        xcopie[i] = xcopie[i+1];
        i++;
    }
    X.num = atoi(xcopie);
    return X;
}

int carteNonValide(carte A[], int n, char x[], carte Tabl[], int t )
{/**vérifie si la carte x jouée par un joueur est valide**/
    int i;
    carte X = convert(x, X);
    if(X.coul != Tabl[t-1].coul  &&  X.num != Tabl[t-1].num)
        return 1;
    for(i=0; i<n; i++)
    {
        if(X.coul == '0' || (X.coul == A[i].coul && X.num == A[i].num))
            return 0;
    }
    return 1;
}

void donnerCarte(carte **A, carte *J1, carte *J2, carte *table, int* a, int n, int m, int l)
{/**donne une carte du stock au joueur pointé par A (ça peut être ou J1, J2)**/
    do{
        (*A+*a)->num = aleatoire(10);
        (*A+*a)->coul = tabCoul[aleatoire(4)];
    }while(siDeja(*(*A+*a), J1, J2, table, n, m, l));
    *a = *a + 1;

}

void actualiseTable(carte **T, int *n, char *x)
{/**positionne la nouvelle carte jouée x sur la table**/
    char xcopie[4];
    strcpy(xcopie, x);
    (*T+(*n))->coul = xcopie[0];
    int i = 0;
    while(x[i] != '\0')
    {   xcopie[i] = xcopie[i+1];
        i++;
    }
    (*T+(*n))->num = atoi(xcopie);
    (*n)++;
}

void supprimer(carte **J, int* n, carte **T, int m)
{/**supprime la nouvelle carte jouée chez le joueur qui la jouée**/
    for(int i=0; i<*n; i++)
    {
        if((*J+i)->coul == (*T+m-1)->coul && (*J+i)->num == (*T+m-1)->num)
        {
            for(int k=i; k<*n-1; k++)
            {
                (*J+k)->coul = (*J+k+1)->coul;
                (*J+k)->num = (*J+k+1)->num;
            }
            break;
        }
    }
    *n = *n-1;
}


int Gagnant(int n1, int n2)
{/**determine le gagnant potentielle à la fin de chaque tour**/
    if(n1 == 0) return 1;
    if(n2 == 0) return 2;
}

