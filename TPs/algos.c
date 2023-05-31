#include "algos.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

size_t degre(graphe const *g, sommet s)
{
    size_t nb_sommets = 0;
    for (size_t i = 0; i < g->nb_aretes; i++){
        if (g->aretes[i].s1 == s || g->aretes[i].s2 == s)
            nb_sommets++;
    }
    return nb_sommets;
}

bool est_regulier(graphe const *g)
{
    if (ordre(g) > 0){
        size_t ordre_base = degre(g, 0);
        for (size_t i = 1; i < ordre(g); i++){
            if (degre(g, i) != ordre_base){
                return false;
            }
        }
    }
    return true;
}

void afficher(graphe const *g)
{
    printf("# sommets = %zu \n", ordre(g));
    printf("# arretes = %zu \n", nb_aretes(g));
    printf("--SOMMETS--\n");
    sommet sa[128];
    for (size_t i = 0; i < ordre(g); i++){
        printf("Sommet %zu : degre = %zu ", i, degre(g, i));
        if (sommets_adjacents(g, i, sa)){
            printf("<-> ");
            for (size_t j = 0; j < degre(g, i); j++){
                printf("%zu ", sa[j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void generer_complet(graphe *g, size_t ordre)
{
    init_graphe(g);
    for (size_t i = 0; i < ordre; i++){
        ajouter_sommet(g);
    }
    for (size_t i = 0; i < ordre; i++){
        for (size_t j = i + 1; j < ordre; j++){
            ajouter_arete(g, (arete){i, j});
        }
    }
}

void visite_composante_connexe(graphe const *g, sommet s, bool *visite)
{
    visite[s] = true;
    sommet sa[128];
    size_t nb_sommets = sommets_adjacents(g, s, sa);
    for (size_t i = 0; i < nb_sommets; i++){
        if (!visite[sa[i]]){
            visite_composante_connexe(g, sa[i], visite);
        }
    }
}

uint32_t nb_composantes_connexes(graphe const *g)
{
    bool *visite = malloc(ordre(g) * sizeof (bool));
    memset(visite, false, ordre(g));
    uint32_t nb_composantes = 0;
    for (size_t i = 0; i < ordre(g); i++){
        if (!visite[i]){
            visite_composante_connexe(g, i, visite);
            nb_composantes++;
        }
    }
    free(visite);
    return nb_composantes;
}

bool sont_connectes(graphe const *g, sommet s1, sommet s2)
{
    bool *visite = malloc(ordre(g) * sizeof (bool));
    memset(visite, false, ordre(g));
    visite_composante_connexe(g, s1, visite);
    bool res = visite[s2];
    free(visite);
    return res;
}

void coloriage_glouton(graphe const *g, uint8_t *couleur_sommet)
{
    sommet sa[128];
    memset(couleur_sommet, 0, ordre(g));
    for (size_t i = 0; i < ordre(g); i++){
        sommet s = i;
        size_t nb_sommets = sommets_adjacents(g, s, sa);
        for (size_t j = 0; j < nb_sommets; j++){
            if (couleur_sommet[sa[j]] == couleur_sommet[s]){
                couleur_sommet[s]++;
                j = 0;
            }
        }
    }
}

void appliquer_permutation(graphe const *src, graphe *dst, size_t const *permutation)
{
    init_graphe(dst);
    for (size_t i = 0; i < ordre(src); i++){
        ajouter_sommet(dst);
    }
    for (size_t i = 0; i < nb_aretes(src); i++){
        ajouter_arete(dst, (arete){permutation[src->aretes[i].s1], permutation[src->aretes[i].s2]});
    }
}

uint32_t estimation_nb_chromatique(graphe const *g, uint32_t n)
{
    graphe g_permute;
    init_graphe(&g_permute);

    size_t permutation[ordre(g)];

    uint8_t* couleurs = malloc(ordre(g) * sizeof(uint8_t));
    uint32_t min = 255;
    for (size_t i = 0; i < n; i++){
        generer_permutation(permutation, ordre(g));
        appliquer_permutation(g, &g_permute, permutation);
        coloriage_glouton(&g_permute, couleurs);
        for (size_t j = 0; j < ordre(g); j++){
            if (couleurs[j] < min){
                min = couleurs[j];
            }
        }
    }
    return 255 - min;
}

void generer_aleatoire(graphe *g, size_t ordre, uint32_t k)
{
    for (size_t i = 0; i < ordre; i++){
        ajouter_sommet(g);
    }
    for (size_t i = 0; i < ordre; i++){
        for (size_t j = i + 1; j < ordre; j++){
            if (rand() % k == 0){
                ajouter_arete(g, (arete){i, j});
            }
        }
    }
}

void dijkstra(graphe const *g, sommet s, double const *poids_arete, double *distance_sommet)
{

    sommet depart = s;
    bool *visite = malloc(ordre(g) * sizeof(bool));
    memset(visite, false, ordre(g));
    for (size_t i = 0; i < ordre(g); i++){
        distance_sommet[i] = DBL_MAX;
    }
    distance_sommet[depart] = 0;
    while (true){
        double min = DBL_MAX;
        sommet s_min = 0;
        for (size_t i = 0; i < ordre(g); i++){
            if (!visite[i] && distance_sommet[i] < min){
                min = distance_sommet[i];
                s_min = i;
            }
        }
        if (min == DBL_MAX){
            break;
        }
        visite[s_min] = true;
        sommet sa[128];
        size_t nb_sommets = sommets_adjacents(g, s_min, sa);
        for (size_t i = 0; i < nb_sommets; i++){
            if (!visite[sa[i]] && distance_sommet[sa[i]] > distance_sommet[s_min] + poids_arete[index_arete(g, (arete){s_min, sa[i]})]){
                distance_sommet[sa[i]] = distance_sommet[s_min] + poids_arete[index_arete(g, (arete){s_min, sa[i]})];
            }
        }
    }
    free(visite);
}

void trier_aretes(arete *aretes_triees, graphe const *g, double const *poids_arete)
{
    for (size_t i = 0; i < nb_aretes(g); i++){
        aretes_triees[i] = g->aretes[i];
    }
    for (size_t i = 0; i < nb_aretes(g); i++){
        for (size_t j = i + 1; j < nb_aretes(g); j++){
            if (poids_arete[index_arete(g, aretes_triees[i])] > poids_arete[index_arete(g, aretes_triees[j])]){
                arete tmp = aretes_triees[i];
                aretes_triees[i] = aretes_triees[j];
                aretes_triees[j] = tmp;
            }
        }
    }
}

void kruskal(graphe const *g, double const *poids_arete, graphe *acm)
{
    arete *aretes_triees = malloc(nb_aretes(g) * sizeof(arete));
    trier_aretes(aretes_triees, g, poids_arete);
    for (size_t i = 0; i < ordre(g); i++){
        ajouter_sommet(acm);
    }
    for (size_t i = 0; i < nb_aretes(g); i++){
        if (!sont_connectes(acm, aretes_triees[i].s1, aretes_triees[i].s2)){
            ajouter_arete(acm, aretes_triees[i]);
        }
    }
    free(aretes_triees);
}
