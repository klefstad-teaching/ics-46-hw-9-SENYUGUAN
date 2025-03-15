#include "dijkstras.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << argv[0] << " graphfile\n";
        return 1;
    }
    Graph G;
    file_to_graph(argv[1], G);

    if (G.numVertices == 0) {
        cerr << "Error: zero vertices";
        return 1;
    }

    int source = 0;
    vector<int> prev;
    vector<int> dist = dijkstra_shortest_path(G, source, prev);
    
    for(int v = 0; v < G.numVertices; ++v)
    {
        vector<int> path = extract_shortest_path(dist, prev, v);
        print_path(path, path.empty() ? 0 : dist[v]);
    }

    return 0;
}