#include <iostream>
#include <fstream>
using namespace std;

#define K_MAX 100000

int m[K_MAX + K_MAX + 1];
int cnt[K_MAX + 1 + 1]; // 0, 1, ... K_MAX + 1

int main () {
  ifstream myReadFile; 
  myReadFile.open("find_the_mintxt.txt"); 
  int rounds; 
  string line; 
  myReadFile >> rounds; 
  getline(myReadFile, line); 
  int round = 1; 
  while (round <= rounds) { 
    int N, K;
    long long int A, B, C, R;
    myReadFile >> N >> K;
    myReadFile >> A >> B >> C >> R;
    // 1. init
    B %= R;
    C %= R;
    for (int i = 1; i <= K_MAX + 1; ++i) 
      cnt[i] = 0;
    
    // 2. calcualte first K elements (0 .. K-1)
    m[0] = A;
    if (A <= K_MAX + 1)
      cnt[A]++;
    for (int i = 1; i < K; ++i) {
      long long S = m[i-1] * B + C;
      S %= R;
      m[i] = S;
      if (m[i] <= K_MAX + 1)
        cnt[m[i]]++;
    }
    // 3. calculate K ... 2K (number K + 1)
    for (int i = K; i <= 2*K; ++i) {
      for (int j = 0; j <= K_MAX + 1; ++j) {
        if (cnt[j] == 0) {
          m[i] = j;
          break;
        }
      }
      if (m[i - K] <= K_MAX + 1) {
        cnt[m[i - K]]--;
      }
      if (m[i] <= K_MAX + 1)
        cnt[m[i]]++;
    }
    // 4. calculate answer
    int index = N - K - 1; // since N > K, N - K > 0
    index %= (K + 1);
    index = K + index;
    cout << "Case #" << round << ": ";
    cout << m[index] << endl;
    round++;
  }
}
