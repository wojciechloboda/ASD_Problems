#include <iostream>
#include <vector>
#include <queue>

#define INF INT32_MAX

/*
Implementation of Edmonds-Karp algorithm for finding a Max-Flow with Graph represented as an adjacency matrix
*/


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

    std::cout << edmonds_karp(G, 0, 8) << std::endl;
}
