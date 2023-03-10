#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <array>
#include <set>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Helper function determine distance between points (edge weights)
float find_weight(std::vector<float> coord1, std::vector<float>  coord2, int dimension) {
    float weight = 0;
    for (int i = 0; i < dimension; i++) {
        float sub = coord1[i] - coord2[i];
        weight += sub*sub;
    }

    // return pow(weight, 0.5); 
    // changed this in order to optimize because square root is pretty slow, 
    // now we only square root the edges that we aren't pruning
    return weight;
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
    final_graph.reserve(numpoints*20);

    float kn = 0;
    if (dimension == 1) {
        kn = 15.99921072082581*pow(numpoints,-1.0691752251222053) + .0004;
    } else if (dimension == 2) {
        kn = 3.5935139096062696 * pow(numpoints,-0.5570087686738145) + 0.0045;
    } else if (dimension == 3) {
        kn = 2.2242548127651576 * pow(numpoints, -0.35594891508401877) + 0.004683;
    } else {
        kn = 2.5278030146479202 * pow(numpoints, -0.30495038437899674) + 0.0245;
    }

    // Calculate edge between each unique pair of vertices and store as triple in final_graph vector
    for (int i = 0; i < numpoints; i++) {
        for (int j = i + 1; j < numpoints; j++) {
            float edge = find_weight(vertices[i], vertices[j], dimension);
            if (edge < kn) {
                std::array<float, 3> arr = {edge, i, j};
                final_graph.push_back(arr);
            }
        }
    }

    // Sort graph in ascending order
    std::sort(final_graph.begin(), final_graph.end(), sortByEdge);

    return final_graph;
};

// For Kruskals algo
struct DisjointSets {
    int *parent, *rank;
    int n;
  
    // Constructor for disjoint sets
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];
  
        // All vertices start as different sets/trees with rank 0.
        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }
  
    // Find the parent of a vertex
    int find(int u)
    {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void link(int x, int y) {
        // Make tree with smaller height
        // a subtree of the other tree 
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
        }  
  
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
  
    // Union (w/ path compression)
    void merge(int x, int y)
    {
        link(find(x), find(y));
    }
};

  
float kruskalMST(std::vector<std::vector<float> > vertices, std::vector<std::array<float, 3> > finalGraph) {
    float mst_wt = 0; // Initialize result
    float largest_wt = 0;
    int edge_counter = 0;
  
    // Create disjoint sets
    DisjointSets disjoint_sets(vertices.size());
  
    // Iterate through the graph
    int i = 0;
    while (edge_counter < vertices.size() - 1)
    {
        float u = finalGraph[i][1];
        float v = finalGraph[i][2];
  
        int set_u = disjoint_sets.find(u);
        int set_v = disjoint_sets.find(v);
  
        // Check if edge endpoints are in the same set/tree already
        if (set_u != set_v)
        {
            edge_counter++;
            // Update MST weight
            float wt = sqrt(finalGraph[i][0]);
            mst_wt += wt;
            if (wt > largest_wt) {
                largest_wt = wt;
            }
  
            // Merge two sets
            disjoint_sets.merge(set_u, set_v);
        }
        i++;
    }

    std::cout << "largest weight in the MST: " << largest_wt << "\n";
  
    return mst_wt;
}

void run_alg(int numpoints, int numtrials, int dimension) {
    std::__1::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

    float mst_total = 0;
    for (int i = 0; i < numtrials; i++) {
        std::vector<std::vector<float> > vertices = get_vertices(numpoints, dimension);
        std::vector<std::array<float, 3> > finalGraph = build_graph(numpoints, dimension, vertices);

        mst_total += kruskalMST(vertices, finalGraph);
    }

    std::__1::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

    std::__1::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "average weight for " << numpoints << " and dimension " << dimension << ": " << mst_total / numtrials << "\n";
    std::cout << "time it took: " << duration.count() << " seconds \n";
}

int main(int argc, char *argv[]) {
    if (argc != 5 && argc != 2) {
        std::cout << "Usage: ./randmst 0 numpoints numtrials dimension\n";
        std::cout << "OR: ./randmst 1\n";
    } else {
        srand(std::time(0));

        int debug_mode = atoi(argv[1]);

        // If debug mode is 0, run the numpoints and numtrials at the dimension requested
        if (debug_mode == 0) {
            int numpoints = atoi(argv[2]);
            int numtrials = atoi(argv[3]);
            int dimension = atoi(argv[4]);

            run_alg(numpoints, numtrials, dimension);
        // If debug mode is 1, run for every numpoints and dimension option for 5 trials each
        } else if (debug_mode == 1) {
            int n[12] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144};
            for (int i = 0; i < 12; i++) {
                for (int d = 1; d < 5; d++) {

                    int numpoints = n[i];
                    int numtrials = 5;
                    int dimension = d;

                    run_alg(numpoints, numtrials, dimension);
                }
            }
        }

    }    
};
