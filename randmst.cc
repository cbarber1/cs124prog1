#include <iostream>
#include <cmath>
#include <map>

struct D2coords {
    int x1;
    int x2;
};

struct D3coords {
    int x1;
    int x2;
    int x3;
}

struct D4coords {
    int x1;
    int x2;
    int x3;
    int x4;
}

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

// Helper function to build graph (as adjacency list)
// Incomplete 
build_graph(int numpoints, int dimension) {
    void* vertices[numpoints];

    for (int i = 0; i < numpoints; i++) {
        if (dimension == 2) {
            D2coords* coords = new D2coords;
            coords->x1 = (float) rand() / (float) (RAND_MAX);
            coords->x2 = (float) rand() / (float) (RAND_MAX);
        } else if (dimension == 3) {
            D3coords* coords = new D3coords;
            coords->x1 = (float) rand() / (float) (RAND_MAX);
            coords->x2 = (float) rand() / (float) (RAND_MAX);
            coords->x3 = (float) rand() / (float) (RAND_MAX);
        } else if (dimension == 4) {
            D4coords* coords = new D4coords;
            coords->x1 = (float) rand() / (float) (RAND_MAX);
            coords->x2 = (float) rand() / (float) (RAND_MAX);
            coords->x3 = (float) rand() / (float) (RAND_MAX);
            coords->x4 = (float) rand() / (float) (RAND_MAX);
        }
    }
}