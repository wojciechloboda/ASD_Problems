#include <iostream>
#include <vector>
#include <queue>

#define INF INT32_MAX

/*
Implementation of Edmonds-Karp algorithm for finding a Max-Flow with Graph represented as an adjacency matrix
*/

struct Edge{
    int v, weight;
};

void BFS(std::vector<std::vector<int>> &G, std::vector<int> &parents, int s)
{
    int n = (int)G.size();
    int current;
    std::vector<bool> visited(n);
    std::queue<int> q;

    for(int i = 0; i < n; ++i){
        parents[i] = i;
    }

    parents[s] = s;
    visited[s] = true;
    q.push(s);

    while(!q.empty()){
        current = q.front();
        q.pop();

        for(int i = 0; i < n; ++i){
            if (G[current][i] != 0 && !visited[i]){
                visited[i] = true;
                parents[i] = current;
                q.push(i);
            }
        }
    }
}


int edmonds_karp(std::vector<std::vector<int>>& G, int s, int t){
    int n = (int)G.size();
    int current;
    int min_flow;
    std::vector<std::vector<int>> residual(n, std::vector<int>(n));
    std::vector<int> parents(n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            residual[i][j] = G[i][j];
        }
    }



    while(true)
    {
        BFS(residual, parents, s);
        if(parents[t] == t)
            break;

        current = t;
        min_flow = INF;

        while(current != s){
            if(min_flow > residual[parents[current]][current]){
                min_flow = residual[parents[current]][current];
            }
            current = parents[current];
        }

        current = t;

        while(current != s){
            residual[parents[current]][current] -= min_flow;
            residual[current][parents[current]] += min_flow;
            current = parents[current];
        }
    }

    int res = 0;
    for(int i = 0; i < n; ++i){
        res += residual[t][i];
    }

    return res;
}

/*
Finding association in bipartite graph using edmonds-karp
*/

void convert(std::vector<std::vector<Edge>> &Graph, std::vector<std::vector<int>> &G){
    int n = (int)Graph.size();

    for(int v = 0; v < n; ++v){
        for(auto& element : Graph[v]){
            G[v][element.v] = element.weight;
        }
    }
}

int find_association(std::vector<std::vector<Edge>> &Graph){
    int n = (int)Graph.size();
    std::vector<std::vector<int>> G(n + 2, std::vector<int>(n + 2));

    int A = n;
    int B = n + 1;

    Graph.emplace_back();
    Graph.emplace_back();

    for(int i = 0; i < n / 2; ++i){
        Graph[A].push_back({i, 1});
        Graph[i + n / 2].push_back({B, 1});
    }

    convert(Graph, G);

    return edmonds_karp(G, n, n + 1);
}




int main(int, char**) {
    std::vector<std::vector<int>> G = {
            {0, 3, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 3, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 5},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    //Bipartite graph
    std::vector<std::vector<Edge>> Graph = {
            {{4, 1}, {6, 1}},
            {{5, 1}, {7, 1}},
            {{6, 1}},
            {{6, 1}},
            {},
            {},
            {},
            {}
    };

    std::cout << edmonds_karp(G, 0, 8) << std::endl;
    std::cout << find_association(Graph);
}
