#include<bits/stdc++.h>
using namespace std;
#define pb push_back 
#define pf pop_front
#define mp make_pair 
#define x first
#define y second
typedef long long ll;

ll a[1000000], b[1000000];

ll sum_org(ll i)
{
  ll s = 0;
  while(i > 0)
    s += a[i], i -= ((i) & -(i));
  return s;
}

ll sum_sort(ll i)
{
  ll s = 0;
  while(i > 0)
    s += b[i], i -= ((i) & -(i));
  return s;

}

void add_org(ll i, ll k, ll n)
{
  while ( i <= n) a[i] += k, i += ((i) & -(i)); 
}

void add_sort(ll i, ll k, ll n)
{
  while ( i <= n ) b[i] += k, i += ((i) & -(i));
}




int main(){
		
}