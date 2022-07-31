#include <iostream>
#include <vector>
#include <climits>

#define INF INT_MAX

/*
 * Dijkstra algorithm on graph represented with adjacency matrix O(n^2)
 */


void dijkstra(const std::vector<std::vector<int>>& G, std::vector<int>& dist, int n, int s){
    std::vector<bool> visited(n);
    dist[s] = 0;

    std::pair<int, int> current;
    int min;

    for(int i = 0; i < n; ++i){
        min = INF;
        for(int j = 0; j < n; ++j){
            if(dist[j] < min && !visited[j]){
                min = dist[j];
                current = {dist[j], j};
            }
        }

        visited[current.second] = true;

        for(int j = 0; j < n; ++j){
            if(G[current.second][j] != 0 && dist[j] > dist[current.second] + G[current.second][j]) {
                dist[j] = dist[current.second] + G[current.second][j];
            }
        }
    }
}

int main(){

    int n = 8;
    std::vector<std::vector<int>> G = {
            {0, 1, 10, 0, 0, 0, 0, 10},
            {2, 0, 0, 0, 3, 0, 0, 2},
            {10, 0, 0, 17, 0, 0, 0, 0},
            {0, 0, 6, 0, 18, 0, 2, 0},
            {0, 0, 0, 9, 0, 10, 0, 0},
            {0, 7, 0, 0, 90, 0, 0, 78},
            {0, 0, 0, 2, 0, 0, 0, 89},
            {18, 5, 0, 0, 0, 2, 6, 0}
    };
    std::vector<int> dist(n, INF);

    dijkstra(G, dist, n, 0);

    for(const auto& current : dist){
        std::cout << current << " ";
    }


    return 0;
}
