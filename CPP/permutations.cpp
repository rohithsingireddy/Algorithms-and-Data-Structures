#include<bits/stdc++.h>
#include "containerHelper.h"

using namespace std;
#define pb push_back
#define mp make_pair 
#define x first
#define y second
#define p(i,j) pair< i, j >
#define ll long long
#define all(x) x.begin(), x.end()
#define fr(i,n) for( int i = 0; i < n; ++i )
#define FAST_IO ios::sync_with_stdio(false); cin.tie(NULL);
#define debug_v(v) for (auto i : v) cout << i; cout << '\n';
#define exit_now return cout << -1, 0;
const ll mod = 1e18 + 7;
const int N = 3000;

vector<int> c;
vector<bool> chosen( N , 0 );
int n;

vector<int> kthpermutation(int k)
{
  vector<int> res(n), indices(n, 0);
  fr(i,n) res[i] = i+1; // Initialize the numbers

  int d = 1;
  for( int p = 1; p <= n; p++ )// p -place
  {
    if((k/d) == 0) break;
    indices[n-p] = (k/d) % p; 
   d *= p;
  }
  // take (index)th element of indices and place it at i
  for ( int i = 0; i < n; ++i )
  {
    int index = indices[i] + i;
    if ( index != i )
    {
      int t = res[index];
      for ( int j = index; j > i; j-- )
        res[j] = res[j-1];
      res[i] = t;
    }
  }
  return res;
}

void search()
{
  if(c.size() == n)
  {
    debug_v(c);
  }
  else
  {
    for( int i = 1; i <= n; ++i )
    {
      if( chosen[i] ) continue;
      chosen[i] = 1;
      c.pb(i);
      search();
      chosen[i] = 0;
      c.pop_back();
    }
  }
}

int main(){
  FAST_IO
  int k;
  cin >> n >> k;
  //search();
  cout << kthpermutation(k);
  return 0;
}
