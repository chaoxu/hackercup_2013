#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

#define MOD 1000000007

// m <= 10000, n <=10000
unsigned long long choose(int m, int k) {
  k = min(k, m-k);
  unsigned long long res = 1;
  for (int i=1; i<=k; ++i)
    res = res*(m-k+i) /i;
  return res;
}

// from small to big
// consider only array[0] ~ array[n], you have n+1 elements
// values already Mod'ed.
unsigned int rec(unsigned int* array, int n, int K) {
  if (n+1 < K)
    return 0;
  unsigned int leader = array[n] % MOD;
  unsigned long long cur = (leader * choose(n, K-1)) % MOD;
  //cout << "cur" << cur << endl;
  unsigned int next = rec(array, n-1, K);
  return (cur + next) % MOD;
}

void dump(unsigned int* array, int N) {
  for (int i=0; i<N; ++i)
    cout << array[i] << endl;
}

#define MAX_N 10000

int main() {
  unsigned int array[MAX_N];
  ifstream myReadFile;
  myReadFile.open("card_game.txt");
  int T, round = 1;
  string line;
  myReadFile >> T;
  getline(myReadFile, line);
  while (round <= T) {
    int N, K;
    myReadFile >> N >> K;
    for (int i=0; i<N; ++i) 
      myReadFile >> array[i];
    sort(array, array + N);
   // dump(array, N);
    cout << "Case #" << round << ": " <<  rec(array, N-1, K) << endl;
    round++;
  }
}
