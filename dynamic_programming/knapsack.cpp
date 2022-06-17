//Classic DP knapsack problem


#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>

using namespace std;

int knapsack(int capacity, int n, vector<int>& item_price, vector<int>& item_weight){
  vector<vector<int>> F(capacity + 1, vector<int>(n + 1));

  for(int i = 1; i < capacity + 1; ++i){
    for(int j = 1; j < n + 1; ++j){
      if(i - item_weight[j - 1] >= 0)
        F[i][j] = max(item_price[j - 1] + F[i - item_weight[j - 1]][j - 1], F[i][j - 1]);
      else
        F[i][j] = F[i][j - 1];
    }
  }

  return F[capacity][n];
}

int main(){
  int s = 4; // capacity of a knapsack
  int n = 5; //number of items
  vector<int> item_price = {8, 0, 4, 5, 3};
  vector<int> item_weight = {1, 2, 3, 2, 2};

  cout << knapsack(s, n, item_price, item_weight) << endl;
  //Output: 13

  return 0;
}
