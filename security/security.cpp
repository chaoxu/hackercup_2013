#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment{
  string s;
  int matched;
};

// true if s1 <= s2; 
// >0 : s1 > s2
// principle: the former, the easier to be matched / eliminated
int Compare(const Segment& s1, const Segment& s2) {
  return s1.s < s2.s;
}

vector<Segment> Tokenize(string s, int L) {
  vector<Segment> segs;
  int len = s.length();
  for (int i=0; i<len; ++i) {
    if (i % L == L-1) {
      Segment seg;
      seg.s = s.substr(i-L+1, L);
      seg.matched = -1;
      segs.push_back(seg);
    }
  }
  return segs;
}

string CreateMatch(const string s1, const string s2) {
  string s = s1;
  int len = s.length();
  for (int i=0; i<len; ++i) {
    if (s1[i] == '?') {
      if (s2[i] == '?')
        s[i] = 'a';
      else
        s[i] = s2[i];
    }
  }
  return s;
}


bool CanMatch(string s1, string s2) {
  int len = s1.length();
  if (s1 == s2) return true;
  for (int i=0; i<len; ++i) {
    if (s1[i] != '?' &&
        s2[i] != '?' && 
        s1[i] != s2[i]) 
        return false; 
  }
  return true;
}

int Char2Int(char c) {
  if (c == '?')
    return 6;
  else 
    return c - 'a';
}


vector<string> answers;
bool rec(vector<Segment>& s1, vector<Segment>& s2, int index) {
  //for (int i=0;i<index;++i)
   // cout << " ";
  //cout << index << endl;
  if (index < 0) {
    // perfect, dump to answers
    //cout << "success" << endl;
    vector<string> ans;
    for (int i=0; i<s1.size(); ++i) 
      ans.push_back(CreateMatch(s1[i].s, s2[s1[i].matched].s));
    
    sort(ans.begin(), ans.end());
    string ans_str = "";
    for (int i=0; i<ans.size(); ++i) 
      ans_str += ans[i];
    answers.push_back(ans_str);
    return true;
  }

  string t1 = s1[index].s;
  for (int i= 0; i< s2.size(); ++i) {
    // Brute force here.
    if (s2[i].matched == -1
      && CanMatch(s1[index].s, s2[i].s)) {
      
      s1[index].matched = i;
      s2[i].matched = index;
   
      bool heuristic = true;
      // pruning here
      for (int bit=0; bit < t1.length(); ++bit) {
        int cnt_1[7] = {0};
        for (int k=index - 1; k >= 0; --k) {
          cnt_1[Char2Int(s1[k].s[bit])]++;
        }
        int cnt_2[7] = {0};
        for (int k=0; k<s2.size(); ++k) {
          if (s2[k].matched == -1) 
            cnt_2[Char2Int(s2[k].s[bit])]++;
        }
        
        for (int k=0; k<6; ++k) {
          if (cnt_1[k] > cnt_2[k]) {
            int diff = cnt_1[k] - cnt_2[k];
            cnt_2[6] -= diff;
          } else if (cnt_1[k] < cnt_2[k]) {
            int diff = cnt_2[k] - cnt_1[k];
            cnt_1[6] -= diff;
          }
          if (cnt_1[6] <0 || cnt_2[6] <0) {
            heuristic = false;
            break;
          }
        }
      }

      if (heuristic) {
        if (rec(s1, s2, index - 1))
          return true; 
      }
      s1[index].matched = -1;
      s2[i].matched = -1;
    }
  }
  return false;
}

int main() {
  int T;
  cin >> T;
  int round = 1;
  while (round <= T) {
    answers.clear();
    int m;
    cin >> m;
    string k1, k2;
    cin >> k1 >> k2;
    int len = k1.length();
    vector<Segment> s1 = Tokenize(k1, len/m);
    vector<Segment> s2 = Tokenize(k2, len/m);
    sort(s1.begin(), s1.end(), Compare);
    sort(s2.begin(), s2.end(), Compare);
    
    
    rec(s1, s2, s1.size() - 1);
    
    cout << "Case #" << round << ": ";
    if (answers.size() > 0) {
      // we actuallly return only the first result
      sort(answers.begin(), answers.end());
      cout << answers[0] << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
    round++;
  }

}
