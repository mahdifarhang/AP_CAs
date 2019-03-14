#include <iostream>
#include <vector>

using namespace std;

void printtable(vector<vector<int> >a)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

vector<vector<vector<int> > > check(vector<vector< int> > & a) {
  vector<vector<int> >b {{0,0,0},{0,0,0},{0,0,0}};
  vector<vector<int> >c {{0,0,0},{0,0,0},{0,0,0}};
  for (int i = 1; i < 10; i++) {
    b[0][0] = i;
    for (int j = 1; j < 10; j++) {
      b[0][1] = j;
      for (int k = 1; k < 10; k++) {
        b[0][2] = k;
        for (int x = 1; x < 10; x++) {
          b[1][0] = x;
          for (int y = 1; y < 10; y++) {
            b[1][1] = y;
            for (int z = 1; z < 10; z++) {
              b[1][2] = z;
              for (int t = 1; t < 10; t++) {
                b[2][0] = t;
                for (int m = 1; m < 10; m++) {
                  b[2][1] = m;
                  for (int n = 1; n < 10; n++) {
                    b[2][2] = n;
                    for (int p = 0; p < 3; p++)
                      for (int q = 0; q < 3; q++)
                        c[p][q] = 0;
                    if(b[1][0] < b[0][0])
                      c[0][0]++;
                    if(b[0][1] < b[0][0])
                      c[0][0]++;
                    if(c[0][0] != a[0][0])
                      continue;
                    if(b[0][0] < b[1][0])
                      c[1][0]++;
                    if(b[1][1] < b[1][0])
                      c[1][0]++;
                    if(b[2][0] < b[1][0])
                      c[1][0]++;
                    if(c[1][0] != a[1][0])
                      continue;
                    if(b[1][0] < b[2][0])
                      c[2][0]++;
                    if(b[2][1] < b[2][0])
                      c[2][0]++;
                    if(c[2][0] != a[2][0])
                      continue;
                    if(b[0][0] < b[0][1])
                      c[0][1]++;
                    if(b[1][1] < b[0][1])
                      c[0][1]++;
                    if(b[0][2] < b[0][1])
                      c[0][1]++;
                    if(c[0][1] != a[0][1])
                      continue;
                    if(b[1][0] < b[1][1])
                      c[1][1]++;
                    if(b[0][1] < b[1][1])
                      c[1][1]++;
                    if(b[1][2] < b[1][1])
                      c[1][1]++;
                    if(b[2][1] < b[1][1])
                      c[1][1]++;
                    if(c[1][1] != a[1][1])
                      continue;
                    if(b[2][0] < b[2][1])
                      c[2][1]++;
                    if(b[2][2] < b[2][1])
                      c[2][1]++;
                    if(b[1][1] < b[2][1])
                      c[2][1]++;
                    if(c[2][1] != a[2][1])
                      continue;
                    if(b[0][1] < b[0][2])
                      c[0][2]++;
                    if(b[1][2] < b[0][2])
                      c[0][2]++;
                    if(c[0][2] != a[0][2])
                      continue;
                    if(b[0][2] < b[1][2])
                      c[1][2]++;
                    if(b[1][1] < b[1][2])
                      c[1][2]++;
                    if(b[2][2] < b[1][2])
                      c[1][2]++;
                    if(c[1][2] != a[1][2])
                      continue;
                    if(b[1][2] < b[2][2])
                      c[2][2]++;
                    if(b[2][1] < b[2][2])
                      c[2][2]++;
                    if(c[2][2] != a[2][2])
                      continue;
                    printtable(b);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

int main()
{
  vector<vector<int> >a {{0,0,0},{0,0,0},{0,0,0}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      cin >> a[i][j];
  check(a);
}
