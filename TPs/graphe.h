#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef size_t sommet;

typedef struct arete
{
    sommet s1;
    sommet s2;
} arete;

typedef struct graphe
{
    size_t ordre;
    size_t nb_aretes;
    size_t aretes_capacite;
    arete *aretes;
} graphe;

static const size_t UNKNOWN_INDEX = -1;

void init_graphe(graphe *g);
void free_graphe(graphe *g);

size_t ordre(graphe const *g);
size_t nb_aretes(graphe const *g);

void ajouter_sommet(graphe *g);
bool existe_arete(graphe const *g, arete a);
bool ajouter_arete(graphe *g, arete a);
size_t index_arete(graphe const *g, arete a);

size_t sommets_adjacents(graphe const *g, sommet s, sommet sa[]);
