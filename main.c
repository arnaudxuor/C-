/* MASTERMIND Version2 
Version très simplifiée :
----> chaque chiffre n'est utilisé qu'une fois
*/

#include <stdio.h>
#define COUP_MAX 10 // Nombre de coup Maximal
#define NB_CHIFFRE 4 // Nombre de chiffre dans le code
#define CHIFFRE_MAX 6 // Chiffre de 1 à 6

void afficher_acceuil();
void saisir_comb(int *tab);
void comparer_comb(int* chiff_S,int* chiff_J,int* bien_place,int* mal_place);
void affiche_resultat(int* bien_place,int* mal_place);
void affiche_score_final(int bien_place,int nbre_coups);

int main(void)
{
    /* Variables */
    int chiff_S[NB_CHIFFRE];//chiffre Secret
    int chiff_J[NB_CHIFFRE];//chiffre Joué
    int bien_place;
    int mal_place;
    int nbre_coups;

    /* Initialisation de la partie et des conditions */
    afficher_acceuil();
    nbre_coups=0;
    bien_place=0;
    mal_place=0;

    /* Saisie de la combinaison secrète */
    printf("\n\n\t\tCOMBINAISON SECRETE ");
    saisir_comb(&chiff_S);
    printf("\n\n\n");
    printf("\n\t\tDEBUT DE LA PARTIE");

    /* Structure de contrôle principale */
    do
    {
        /* Saisie de la proposition de combinaison */
        saisir_comb(&chiff_J);
        /* Vérifier la combinaison */
        comparer_comb(&chiff_S, &chiff_J,&bien_place, &mal_place);
        /* Mettre à jour les conditions */
        affiche_resultat(&bien_place, &mal_place);

        nbre_coups++;
    }
    while( (bien_place!=NB_CHIFFRE) && (nbre_coups!=COUP_MAX));

    /* FIN Structure de contrôle principale */
    /* Affichage du résultat de la partie */

    affiche_score_final(bien_place, nbre_coups);
    return 0;
}

void afficher_acceuil()
{

    printf("************************************\n");
    printf("****                            ****\n");
    printf("****        MASTERMIND          ****\n");
    printf("****                            ****\n");
    printf("************************************\n");

    printf("\nVous avez 10 essais pour trouver une combinaison de 4 chiffres.\n");
    printf("Les chiffres sont compris entre 1 et 6.\nExemple de combinaison :\n>2 6 5 5\n");
    printf("\n\tBien place : #\n\tMal place : *\n\tFaux : . \n");
}

void saisir_comb(int *n)
{
    int i;

    printf("\n\n\n//***********************************//\n");

    for(i=0; i<NB_CHIFFRE; i++)
    {

        printf("\n\t\tChiffre %d :",i+1);
        scanf("%d",&n[i]);

    }

}
void comparer_comb(int* chiff_S,int* chiff_J,int* bien_place,int* mal_place)
{
    int i,j;

    *bien_place = 0;
    *mal_place = 0;

    for(i=0; i<NB_CHIFFRE; i++)
    {

        if(chiff_S[i]==chiff_J[i])
        {
            *bien_place= *bien_place + 1;
        }

        for(j=0; j<NB_CHIFFRE; j++)
        {

            if(chiff_S[i]==chiff_J[i])
            {
                /* Nothing */

            }else{



            if( chiff_J[i] == chiff_S[j] )
            {

                *mal_place = *mal_place + 1;

            }

            }

        }

    }

    if(*bien_place==COUP_MAX)
    {
        *mal_place = 0;
    }

}


void affiche_resultat(int* bien_place,int* mal_place)
{

    printf("\tBien placee : %d \t\t Mal Placee : %d", *bien_place, *mal_place );

}
void affiche_score_final(int bien_place, int nbre_coups)
{
    if(bien_place==NB_CHIFFRE)
    {
        printf("\n\n\t\tFELICITATION");
        printf("\n\n\t\tVous avez gagne en %d coups", nbre_coups);
    }
    else
    {
        printf("\n\n\t\tPERDU");
        printf("\n\n\t\tVous avez ecoule vos %d coups", COUP_MAX);
    }
}
