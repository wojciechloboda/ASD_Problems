// A vector of n integers describing lengths of cars is given
// Cars wait in line for a ferry ride. Ferry has 2 decks of length capacity1 and capacity2
// Write a program that returns maximum number of cars that can get on a ferry ride

#include<iostream>
#include<vector>

using namespace std;

int ferry(vector<int>& cars, int n, int capacity1, int capacity2){
  vector<vector<vector<int>>> F(n + 1, vector<vector<int>>(capacity1 + 1, vector<int>(capacity2 + 1)));

  for(int i = n; i > 0; --i){
    for(int p1 = 0; p1 < capacity1 + 1; ++p1){
      for(int p2 = 0; p2 < capacity2 + 1; ++p2){
        if(i == n && (p1 - cars[i - 1] >= 0 || p2 - cars[i - 1] >= 0))
          F[i][p1][p2] = 1;
        else if(p1 - cars[i - 1] >= 0 && p2 - cars[i - 1] >= 0)
          F[i][p1][p2] = 1 + max(F[i + 1][p1 - cars[i - 1]][p2], F[i + 1][p1][p2 - cars[i - 1]]);
        else if(p1 - cars[i - 1] >= 0)
          F[i][p1][p2] = 1 + F[i + 1][p1 - cars[i - 1]][p2];
        else if(p2 - cars[i - 1] >= 0)
          F[i][p1][p2] = 1 + F[i + 1][p1][p2 - cars[p2 - cars[i - 1]]];
      }
    }
  }

  return F[1][capacity1][capacity2];
}

int main(){
  vector<int> v = {10, 2, 3, 5, 2};
  cout << ferry(v, 5, 10, 3) << endl;
  return 0;
}
