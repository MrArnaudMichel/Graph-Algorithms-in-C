# Graph Algorithms in C

This repository provides implementations of graph algorithms in C, including Dijkstra's algorithm, Kruskal's algorithm, and Prim's algorithm, along with basic graph operations.

## Graph Representation

Graphs are represented using an adjacency list. Each vertex maintains a list of its adjacent vertices, allowing for efficient representation of graph structures.

## Usage

To use the algorithms provided in this repository, include the necessary header files (`graphe.h`, `algos.h`, `utils.h`) in your C program and call the appropriate functions. Examples of usage are provided in the `main.c` file.

### Dijkstra's Algorithm

Dijkstra's algorithm finds the shortest paths from a source vertex to all other vertices in a weighted graph.

### Kruskal's Algorithm

Kruskal's algorithm finds the minimum spanning tree of a connected, undirected graph.

### Prim's Algorithm

Prim's algorithm also finds the minimum spanning tree of a connected, undirected graph, starting from an arbitrary vertex and growing the tree by adding the smallest edge that connects a vertex in the tree to a vertex outside the tree.

## Graph Operations

The repository also provides basic operations on graphs, including:

- Checking if two vertices are connected.
- Finding the degree of a vertex.
- Checking if a graph is regular.
- Finding the number of connected components in a graph.
- Coloring vertices of a graph using a greedy algorithm.
- Estimating the chromatic number of a graph.

## Example

```c
#include "graphe.h"
#include "algos.h"
#include "utils.h"
#include <stdio.h>

int main() {
    graphe g;
    init_graphe(&g);

    // Add vertices and edges to the graph
    // ...

    // Use graph algorithms
    // ...

    free_graphe(&g);
    return 0;
}
