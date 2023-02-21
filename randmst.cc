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
}

// Helper function determine distance between points (edge weights)
float find_weight(float coord1[], float coord2[], int dimension) {
    int weight = 0;
    for (int i = 0; i < dimension; i++) {
        weight += pow((coord1[i] - coord2[i]), 2);
    }

    return pow(weight, 0.5);
}

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

    // Calculate edge between each unique pair of vertices and store as triple in final_graph vector
    for (int i = 0; i < numpoints; i++) {
        for (int j = i; j < numpoints; j++) {
            float edge = find_weight(vertices[i], vertices[j], dimension);
            std::array<float, 3> arr = {edge, i, j};
            final_graph.push_back(arr);
        }
    }

    // Sort final_graph in ascending order
    int n = sizeof(final_graph) / sizeof(final_graph[0]);
    std::sort(final_graph.begin(), final_graph.end(), sortByEdge);

    return final_graph;
}

// Greedy alg
// Sort edge in increasing order by weight
// If endpoints are in same tree, then edge is discarded
    // 
// Otherwise, we include it
// Need makeset, find, and union