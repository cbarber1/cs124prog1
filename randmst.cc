#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <array>
#include <set>
#include <cstdlib>
#include <ctime>

// Helper function determine distance between points (edge weights)
float find_weight(std::vector<float> coord1, std::vector<float>  coord2, int dimension) {
    float weight = 0;
    for (int i = 0; i < dimension; i++) {
        weight += pow((coord1[i] - coord2[i]), 2);
    }

    return pow(weight, 0.5);
};

// Helper function for sorting edges in ascending order
bool sortByEdge(std::array<float, 3> arr1, std::array<float, 3> arr2) {
    return (arr1[0] < arr2[0]);
}

std::vector<std::vector<float> > get_vertices(int numpoints, int dimension) {
     // Initialize vector of vertices
     std::vector<std::vector<float> > vertices(numpoints, std::vector<float>(dimension));

    // Generate [numpoints] vertices
    for (int i = 0; i < numpoints; i++) {
        for (int j = 0; j < dimension; j++) {
            vertices[i][j] = (float) rand() / (float) (RAND_MAX);
        }
    }

    return vertices;
}

// Helper function to build graph (represented as edges in increasing weight)
std::vector<std::array<float, 3> > build_graph(int numpoints, int dimension, std::vector<std::vector<float> > vertices) {
    // Initialize vector that stores points and edge between them
    std::vector<std::array<float, 3> > final_graph;
    final_graph.reserve((numpoints - 1) * numpoints / 2);

    // Calculate edge between each unique pair of vertices and store as triple in final_graph vector
    for (int i = 0; i < numpoints; i++) {
        for (int j = i + 1; j < numpoints; j++) {
            float edge = find_weight(vertices[i], vertices[j], dimension);
            std::array<float, 3> arr = {edge, i, j};
            final_graph.push_back(arr);
        }
    }

    // Sort graph in ascending order
    std::sort(final_graph.begin(), final_graph.end(), sortByEdge);

    return final_graph;
};

// To represent Disjoint Sets
struct DisjointSets {
    int *parent, *rank;
    int n;
  
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];
  
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;
  
            //every element is parent of itself
            parent[i] = i;
        }
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        /* Make tree with smaller height
        a subtree of the other tree */
        if (rank[x] > rank[y])
            parent[y] = x;
        else // If rank[x] <= rank[y]
            parent[x] = y;
  
        if (rank[x] == rank[y])
            rank[y]++;
    }
};

  
float kruskalMST(std::vector<std::vector<float> > vertices, std::vector<std::array<float, 3> > finalGraph) {
    float mst_wt = 0; // Initialize result
    int mst_size = 0;
  
    // Create disjoint sets
    DisjointSets ds(vertices.size());
  
    // Iterate through the graph
    for (int i = 0; i < finalGraph.size(); i++)
    {
        float u = finalGraph[i][1];
        float v = finalGraph[i][2];
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Update MST weight
            mst_wt += finalGraph[i][0];
  
            // Merge two sets
            ds.merge(set_u, set_v);

            mst_size++;
        }
    }
  
    return mst_wt / mst_size;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "Usage: ./randmst 0 numpoints numtrials dimension\n";
    } else {
        srand(std::time(0));
        std::vector<std::vector<float> > vertices = get_vertices(atoi(argv[2]), atoi(argv[4]));
        std::vector<std::array<float, 3> > finalGraph = build_graph(atoi(argv[2]), atoi(argv[4]), vertices);

        std::cout << "average weight: " << kruskalMST(vertices, finalGraph);
    }
};
