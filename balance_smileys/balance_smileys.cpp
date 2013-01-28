#include <iostream>
#include <fstream>
using namespace std;

bool normalChar(char c) {
  return ('a' <= c && c <= 'z') 
    || c == ' ';
}

bool recSmile(const string& str, int index, int leftParen) {
  int len = str.length();
  if (index == len) {
    return leftParen == 0; 
  }
  char c = str[index];
  if (normalChar(c))
    return recSmile(str, index + 1, leftParen);
  else if (c == '(') 
    return recSmile(str, index + 1, leftParen + 1);
  else if (c == ')') {
    if (leftParen == 0) 
      return false;
    else
      return recSmile(str, index + 1, leftParen - 1);
  }
  else if (c == ':') {
    // if can be smiley face
    bool tryFace = false;
    if (index + 1 < len 
      && (str[index+1] == ')' || str[index+1] == '(' )) {
      tryFace = recSmile(str, index + 2, leftParen);
    }
    return tryFace || recSmile(str, index + 1, leftParen);  // normal char
  }
  return true;
}

int main() {
  ifstream myReadFile;
  myReadFile.open("balanced_smileystxt.txt");
  int T;
  string line;
  myReadFile >> T;
  getline(myReadFile, line);
  int turn = 1;
  while (turn <= T) {
    getline(myReadFile, line);
    cout << "Case #" << turn << ": ";
    bool yes =  recSmile(line, 0, 0);
    string answer = yes ? "YES" : "NO";
    cout << answer << endl;
    turn++;
  }
}
