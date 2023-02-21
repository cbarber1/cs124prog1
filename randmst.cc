#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <array>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Usage: ./randmst 0 numpoints numtrials dimension\n";
    } else {

    }
};

// Helper function determine distance between points (edge weights)
float find_weight(float coord1[], float coord2[], int dimension) {
    int weight = 0;
    for (int i = 0; i < dimension; i++) {
        weight += pow((coord1[i] - coord2[i]), 2);
    }

    return pow(weight, 0.5);
};

// Helper function for sorting edges in ascending order
bool sortByEdge(float arr1[3], float arr2[3]) {
    return (arr1[0] < arr2[0]);
}

// Helper function to build graph (represented as edges in increasing weight)
std::vector<std::array<float, 3>> build_graph(int numpoints, int dimension) {
    // Initialize vector that stores points and edge between them
    std::vector<std::array<float, 3>> final_graph;
    final_graph.reserve((numpoints - 1) * numpoints / 2);

    // Initialize array of vertices
    float vertices[numpoints][dimension];

    // Generate [numpoints] vertices
    for (int i = 0; i < numpoints; i++) {
        for (int j = 0; j < dimension; j++) {
            vertices[i][j] = (float) rand() / (float) (RAND_MAX);
        }
    }
};

// find function to find out if endpoints are in the same tree/set
// returns index of the set 
int find(int x) {
    for (int i = 0; i < sets.length; i++) {
        if (sets[i].find(x) != sets[i].end()) {
            return i;
        };
    }
}

// makeset which is already in the set library

// union which we need to make 
void union(set u, set v) {
    u.insert(v.begin(), v.end());
    // delete v from sets maybe by just setting a boolean variable to false
}

std::set<int> X;
void kruskal(graph G, vertices vertices) {
    // sort edges
    // go through vertices and make a set for each of them 
    for (int i = 0; i < vertices.length, i++) {

    }
    // 
    for (each edge (u, v)) {
        if (find(u) != find(v)) {
            X.insert(edge)
            union(u, v)
        }
    }
}
