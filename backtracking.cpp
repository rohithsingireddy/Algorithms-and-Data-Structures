#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair 
//#define x first
//#define y second
#define p(i,j) pair< i, j >
#define ll long long
#define all(x) x.begin(), x.end()
#define fr(i,n) for( int i = 0; i < n; ++i )
#define FAST_IO ios::sync_with_stdio(false); cin.tie(NULL);
#define debug_v(v) for (auto i : v) cout << i; cout << '\n';
#define exit_now return cout << -1, 0;
const ll mod = 1e18 + 7;
const int N = 3000;

vector<bool> diag1(N,0), diag2(N,0), col(N,0);
int n, c = 0;


//N - Queens
bool valid( int x, int y )
{
  if( col[x] || diag1[x+y] || diag2[x-y+n-1] ) return false;
  return true;
}


void search( int y )
{
  if ( y == n )
  {
    c++;
    return;
  }
  for ( int x = 0; x < n; x++)
  {
    if (!(valid(x, y))) continue;
    col[x] = diag1[x+y] = diag2[x-y+n-1] = 1;
    search(y+1);
    col[x] = diag1[x+y] = diag2[x-y+n-1] = 0;
  }
}

int main(){
  FAST_IO
  cin >> n;
  search(0);
  cout << c;
  return 0;
}