typedef struct _carte{
    int num;    // Numéro de la carte(1 à 10)
    char coul; //Couleur de la carte: R(Rouge), V(Vert), B(Bleu), J(jaune)
}carte;

int aleatoire(int n);

int carteDans(carte X, carte A[], int n);

int siDeja(carte X, carte Jou1[], carte Jou2[], carte Tabl[], int n, int m, int t);

void afficherCartesJ(carte A[], int n);

int carteNonValide(carte A[], int n, char x[], carte Tabl[], int t );

void donnerCarte(carte **A, carte *J1, carte *J2, carte *table, int* a, int n, int m, int l);

void actualiseTable(carte **T, int *n, char *x);

void supprimer(carte **J, int* n, carte **T, int m);

int Gagnant(int n1, int n2);

void distribuer(carte J1[], carte J2[], carte table[], int* a, int* b, int* t);

carte convert(char x[], carte X);

