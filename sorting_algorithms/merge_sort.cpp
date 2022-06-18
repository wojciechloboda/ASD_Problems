// implementation of merge sort

#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& v, int p, int q, int r, int n){
  vector<int> tmp(n);
  for(int i = p; i < r + 1; ++i)
    tmp[i] = v[i];

  int i = p;
  int j = q + 1;
  int k = p;

  while(i <= q ||  j <= r){
    if(i <= q && j <= r){
      if(tmp[i] < tmp[j])
        v[k++] = tmp[i++];
      else
        v[k++] = tmp[j++];
    }
    else if(i <= q){
      v[k++] = tmp[i++];
    }
    else{
      v[k++] = tmp[j++];
    }
  }
}

void merge_sort(vector<int>& v, int p, int r, int n){
  if(p == r)
    return;

  int q = (p + r)/2;
  merge_sort(v, p, q, n);
  merge_sort(v, q + 1, r, n);

  merge(v, p, q, r, n);
}

int main(){
  int n = 7;
  vector<int> tab = {1, -10, 4, 89, -9, 89, 12};
  merge_sort(tab, 0, n - 1, n);

  for(int i = 0; i < n; ++i){
    cout << tab[i] << " ";
  }
  cout << endl;

  return 0;
}
