#include "graphe.h"
#include "algos.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main()
{
    srand(time(NULL));

    graphe g;
    init_graphe(&g);
    generer_aleatoire(&g, 10, 5);
    ajouter_arete(&g, (arete){0, 1});
    double *valeurs = malloc(nb_aretes(&g) * sizeof(double ));

    init_aleatoire(valeurs, nb_aretes(&g), 10.0);



    printf("AFFICHER GRAPHE\n");
    printf("===============\n");
    afficher(&g);

    arete *arretetriee = malloc(nb_aretes(&g) * sizeof(arete));
    memcpy(arretetriee, g.aretes, nb_aretes(&g) * sizeof(arete));
    trier_aretes(arretetriee, &g, valeurs);
    for (size_t i = 0; i < nb_aretes(&g); i++){
        printf("%zu %zu: %f\n", arretetriee[i].s1, arretetriee[i].s2, valeurs[index_arete(&g, arretetriee[i])]);
    }
    graphe g2;
    init_graphe(&g2);
    kruskal(&g, valeurs, &g2);
    afficher(&g2);
    printf("\n");

    free_graphe(&g);


    return EXIT_SUCCESS;
}
