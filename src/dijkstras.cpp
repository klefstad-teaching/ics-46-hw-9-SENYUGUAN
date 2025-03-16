#include "dijkstras.h"
#include <algorithm>
vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous)
{   
    using P = pair<int,int>;
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    distance[source] = 0;

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, source});

    while(!pq.empty())
    {
        auto [curr, u] = pq.top();
        pq.pop();

        if(visited[u] ) continue;
        visited[u] = true;

        for(auto &e : G[u])
        {
            int v = e.dst;
            int w = e.weight;
            if(!visited[v] && distance[u] != INF && distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }

        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int> & distances, const vector<int> &previous, int destination)
{
    vector<int> path;
    if(destination < 0 || destination >= distances.size() || distances[destination] == INF)
        return { };

    for(int i = destination; i != -1; i = previous[i])
        path.push_back(i);

    reverse(path.begin(), path.end());
    return path;

}

void print_path(const vector<int> &v, int total)
{
    for(int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << "\nTotal cost is " << total << "\n";
}
