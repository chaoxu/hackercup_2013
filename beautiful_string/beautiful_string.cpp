#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int cnt[26];

void clear() {
  for (int i = 0; i < 26; ++i)
    cnt[i] = 0;
}

int char2int(char c) {
  if ('a' <= c && c <= 'z')
    return c - 'a';
  else if ('A' <= c && c <= 'Z')
    return c - 'A';
  else
    return -1;
}

void dump() {
  for (int i = 0; i < 26; ++i)
    cout << (char) (i + 'a') << ": " << cnt[i] << endl;
}

int main() {
  ifstream myReadFile;
  myReadFile.open("beautiful_stringstxt.txt");
  int rounds;
  string line;
  myReadFile >> rounds;
  getline(myReadFile, line);
  int round = 1;
  while (round <= rounds) {
    getline(myReadFile, line);
    clear();
    for (int i = 0; i < line.length(); ++i) {
      int index = char2int(line[i]);
      if (index >= 0)
        cnt[index]++;
    }
    sort(cnt, cnt+26);
    int sum = 0;
    for (int i = 25; i>=0; --i) {
      sum += (cnt[i] * (i+1));
    }
    cout << "Case #" << round << ": " << sum << endl;
    round++;
  }
}
