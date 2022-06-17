//given a vector o n integers, check if given s can be a sum of a subset of vector elements
//solution with reconstructing subset

#include<iostream>
#include<vector>

using namespace std;fsdfsdfsd

bool subsetsum(vector<int>& v, int n, int sum){
  vector<vector<bool>> F(sum + 1, vector<bool>(n + 1));
  vector<vector<bool>> R(sum + 1, vector<bool>(n + 1));

  for(int i = 0; i < sum + 1; ++i){
    for(int j = 0; j < n + 1; ++j){
      if (i == 0)
        F[i][j] = 1;
      else if (j == 0)
        F[i][j] = 0;
      else{
        if (i - v[j - 1] >= 0){
          F[i][j] = F[i][j - 1] || F[i - v[j - 1]][j - 1];
          R[i][j] = F[i - v[j - 1]][j - 1];
        }
        else
          F[i][j] = F[i][j - 1];
      }
    }
  }



  if(F[sum][n]){
    int curr_sum = sum;
    int curr_item = n;
    vector<int> res;

    while(curr_sum != 0){
      if(R[curr_sum][curr_item]){
        res.push_back(v[curr_item - 1]);
        curr_sum -= v[curr_item - 1];
        curr_item--;
      }
      else{
        curr_item--;
      }
    }
    for(int i = 0; i < res.size(); ++i){
      cout << res[i] << " ";
    }
    cout << endl;
  }

  return F[sum][n];
}

int main(){
  vector<int> v = {5, 2, 90, 32, 53, 23, 55};
  int n = 7;
  int s = 175;

  cout << subsetsum(v, n, s) << endl;
}
