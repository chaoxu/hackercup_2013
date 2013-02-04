#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
 
struct Point{
  int x;
  int y; 
};

struct PointCompare{
  bool operator()(Point const & lhs, Point const & rhs) {
    if (lhs.y == rhs.y)
      return lhs.x < rhs.x;
    else
      return lhs.y < rhs.y;
  }
};

// TODO: optimize to eat a vector of count, each > 0 if too slow
int VerticalPts(int cnt[], int W, int P) {
  // TEST
  /*
  for (int i=0;i<W;++i)
    cout << cnt[i] << ",";
  cout << endl;
  */
  int sum = 0;
  int wall = W-1; 
  for (int i=W-1; i>=0; --i) {
    if (cnt[i] >0) {
      // update wall
      wall = i - 1;
    } else if (wall - i + 1 >= P) {
      sum++;
    }
  }
  return sum;
}

int main () {
  int T;
  cin >> T;
  int round = 1;
  set<Point, PointCompare> deadpts;
  set<Point, PointCompare>::iterator iter;
  unsigned int W, H, P, Q, N, x, y, A, B, C, D;
  int CNT[40000];

  while (round <= T) {
    // 0. initialization
    deadpts.clear();
    for (int i=0; i<W; ++i)
      CNT[i] = 0;

    // 1. build dead ponits sorting by Y 
    cin >> W >> H >> P >> Q >> N >> x >> y >> A >> B >> C >> D;
    Point p;
    p.x = x; p.y = y;
    deadpts.insert(p);


    for (int n=1; n < N; ++n) {
      unsigned int nx = (x*A + y*B + 1) % W;
      unsigned int ny = (x*C + y*D + 1) % H;
      p.x = nx; p.y = ny;
      deadpts.insert(p);
     // cout << "point: " << p.x << p.y << endl;
      x = nx; y = ny;
    }
    // TEST
    /*
    for (iter=deadpts.begin(); iter!=deadpts.end(); ++iter)
      cout << iter->x << "," << iter->y << endl;
   */
    
    // 2. scan line!
    int sum = 0;
    set<Point, PointCompare>::iterator add_iter = deadpts.begin();
    set<Point, PointCompare>::iterator del_iter = deadpts.begin();
    int len = 0;
    for (int h=0; h<H; ++h) {
      // 1. add points y ==h 
      while (add_iter->y == h) {
        CNT[add_iter->x]++;
        add_iter++;
      }

      len++;
      // 2. test if len is enough
      if (len == Q) {
        int npts = VerticalPts(CNT, W, P); 
      //  cout << "h=" << h << ": " << npts << endl;
        sum += npts;
        while(del_iter->y == h-Q+1) {
          CNT[del_iter->x]--;
          del_iter++;
        }
        len--;
      }
    }

    cout << sum << endl;
    round++;
  }
}
