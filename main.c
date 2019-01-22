

#include <stdio.h>
#include <stdlib.h>

/*
Algorithme :
*/

#define LIGNE_LABY 3   //labyrinthe de taille LIGNE_LABYxCOLONNE_LABY avec départ en case (0,0) et sortie sur le bord droit
#define COLONNE_LABY 4 //avec une colonne de plus pour les cases de sorties à droite sur nos labyrinthes

typedef struct
{
    unsigned char ligne;
    unsigned char colonne;
} t_case;

typedef struct
{
    unsigned char d_D;
    unsigned char d_G;
    unsigned char d_H;
    unsigned char d_B;
    unsigned char distance;
    t_case predecesseur;
} t_voisinnage;


t_case trajet[];


t_voisinnage tableau[LIGNE_LABY][COLONNE_LABY+1]={
                                                 {{1,255,255,1,0,{0,0}},{255,1,255,1,255,{0,1}},{255,255,255,1,255,{0,2}},{255,255,255,1,255,{0,3}}},
                                                 {{255,255,1,1,255,{1,0}},{1,255,1,255,255,{1,1}},{255,1,1,1,255,{1,2}},{255,255,1,1,255,{1,3}}},
                                                 {{1,255,1,255,255,{2,0}},{1,1,255,255,255,{2,1}},{1,1,1,255,255,{2,2}},{255,1,1,255,255,{2,3}}}
                                                 };

        //  direction == 1 : pas de mur
        //  direction == 255 : mur /impossible de passer



void dijkstra(void);
void affiche_distances(void);
void calcul_trajet(void);


int main()
{
    unsigned char i,j;
    printf("Algo du chemin le plus court!\n");
    dijkstra();
    printf("Distances entre chaque case et la case (0,0) : \n");
	affiche_distances();
    calcul_trajet();
    printf("Algo termine !\n");
    return 0;
}


void dijkstra(void)
{
    unsigned char modif = 1;
    int nb_iter=0;
    int i,j;

    while (    modif==1)
    {
        modif=0;

        for(i=0; i<LIGNE_LABY; i++)
        {
            for (j=0; j<COLONNE_LABY+1; j++) //Pour chaque cas ij donc A, B, C, D .....
            {
                if (tableau[i][j].d_G==1)
                {
                    if (tableau[i][j].distance>tableau[i][j-1].distance+1)
                    {
                        tableau[i][j].distance = tableau[i][j-1].distance+1;
                        tableau[i][j].predecesseur.colonne= j-1;
                        tableau[i][j].predecesseur.ligne= i;
                        modif=1;
                    }
                }

                if (tableau[i][j].d_D==1)
                {
                    if (tableau[i][j].distance>tableau[i][j+1].distance+1)
                    {
                        tableau[i][j].distance = tableau[i][j+1].distance+1;
                        tableau[i][j].predecesseur.colonne= j+1;
                        tableau[i][j].predecesseur.ligne= i;
                        modif=1;
                    }
                }

                if (tableau[i][j].d_B==1)
                {
                    if (tableau[i][j].distance>tableau[i+1][j].distance+1)
                    {
                        tableau[i][j].distance = tableau[i+1][j].distance+1;
                        tableau[i][j].predecesseur.colonne= j;
                        tableau[i][j].predecesseur.ligne= i+1;
                        modif=1;
                    }
                }

                if (tableau[i][j].d_H==1)
                {
                    if (tableau[i][j].distance>tableau[i-1][j].distance+1)
                    {
                        tableau[i][j].distance = tableau[i-1][j].distance+1;
                        tableau[i][j].predecesseur.colonne= j;
                        tableau[i][j].predecesseur.ligne= i-1;
                        modif=1;
                    }
                }
            }
        }
        nb_iter ++;
    }
    printf("\n nb_iteration = %d\n\n", nb_iter);
}

void affiche_distances(void)
{
    int i,j;
    for(i=0; i<LIGNE_LABY; i++)
    {
        for (j=0; j<COLONNE_LABY+1; j++)
        {
            printf("%d\t ",tableau[i][j].distance);
            if (j==COLONNE_LABY)
                printf("\n");
        }
    }
}


void calcul_trajet(){

        ///LE ROBOT RENVOIE LES COORDONNEE DE LA CASE D' ARRIVE
       int d_max = tableau[2][3].distance;
       int i,j,h;

       int i_but,j_but;

       int x_trajet,y_trajet;   //POUR PERMUTATION TAB TRAJET

        trajet[d_max];

        //Case Arrivée :

        i_but=2;    //LE ROBOT RENVOIE CES COORDONNEE APRES LA RECONNAISSANCE
        j_but=3;    //IDEM

        i=tableau[2][3].predecesseur.ligne;
        j=tableau[2][3].predecesseur.colonne;

        //PREMIERE CASE TRAJET (A L ENVER )
        trajet[0].ligne = i_but;
        trajet[0].colonne = j_but;

        printf("\n%d-%d\n",tableau[2][3].predecesseur.ligne,tableau[2][3].predecesseur.colonne);

        ///trajet[]

        ///DETERMINATION CHEMIN
        for(h = 0; h < d_max +1 ; h++){


                        //CAS GAUCHE

                        if( (tableau[i][j-1].distance < tableau[i][j].distance)&&(tableau[i][j].d_G == 1) ){

                        printf("\n(%d/%d)",tableau[i][j].predecesseur.ligne,tableau[i][j].predecesseur.colonne);

                        //REMPLISAGE TAB TRAJET
                        trajet[h+1].colonne = tableau[i][j].predecesseur.colonne;
                        trajet[h+1].ligne = tableau[i][j].predecesseur.ligne;

                        j--;


                        }
                        //CAS DROITE

                        else if( (tableau[i][j+1].distance < tableau[i][j].distance) && (tableau[i][j].d_D == 1)){

                        printf("\n((%d/%d)",tableau[i][j].predecesseur.ligne,tableau[i][j].predecesseur.colonne);
                        //REMPLISAGE TAB TRAJET
                        trajet[h+1].colonne = tableau[i][j].predecesseur.colonne;
                        trajet[h+1].ligne = tableau[i][j].predecesseur.ligne;

                        j++;

                        }
                        //CAS HAUT

                        else if( (tableau[i-1][j].distance < tableau[i][j].distance) && ( tableau[i][j].d_H == 1 ) ){
                        printf("\n(%d/%d)",tableau[i][j].predecesseur.ligne,tableau[i][j].predecesseur.colonne);
                        //REMPLISAGE TAB TRAJET
                        trajet[h+1].colonne = tableau[i][j].predecesseur.colonne;
                        trajet[h+1].ligne = tableau[i][j].predecesseur.ligne;

                        i--;
                        }

                        //CAS BAS

                        else if( (tableau[i+1][j].distance < tableau[i][j].distance) && (tableau[i][j].d_B ==1 ) ){
                        printf("\n(%d/%d)",tableau[i][j].predecesseur.ligne,tableau[i][j].predecesseur.colonne);
                        //REMPLISAGE TAB TRAJET
                        trajet[h+1].colonne = tableau[i][j].predecesseur.colonne;
                        trajet[h+1].ligne = tableau[i][j].predecesseur.ligne;

                        i++;
                        }
                  }
                    ///PERMUTATION TAB TRAJET
                  for(i=0;i< d_max/2;i++){

                        x_trajet=trajet[i].ligne;
                        y_trajet=trajet[i].colonne;

                        trajet[i].ligne = trajet[d_max-i-1].ligne;
                        trajet[i].colonne = trajet[d_max-i-1].colonne;

                        trajet[d_max-i-1].ligne=x_trajet;
                        trajet[d_max-i-1].colonne=y_trajet;

                }

                printf("\n\n");
                ///AFFICHAGE TRAJET DS L ORDRE
                    for(i=0;i<d_max+1;i++){

                printf("  {%d-%d}",trajet[i].ligne,trajet[i].colonne);

            }
}

