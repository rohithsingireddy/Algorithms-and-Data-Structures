#include<bits/stdc++.h>
using namespace std;
#define pb push_back 
#define x first
#define y second
#define p(i,j) pair< i, j >
#define v(i) vector< i >
#define ll long long
#define all(x) x.begin(), x.end()
#define fr(i,n) for( int i = 0; i < n; ++i )
#define FAST_IO ios::sync_with_stdio(false); cin.tie(NULL);
#define debug_v(v) for (auto i : v) cout << i << ' '; cout << '\n';
#define exit_now return cout << -1, 0;
const ll mod = 1e10 + 7;
const int N = 3000;



int main(){
	FAST_IO
	ll n;
	cin >> n;
	ll a[n];
	fr(i,n) cin >> a[i];
	/*v(int) st;
	for( int i = 0; i < n; ++i )
	{
		if(st.empty()) st.pb(a[i]), cout << -1 << ' ';
		else if(st.back() < a[i] ) cout << st.back() << ' ', st.pb(a[i]);
		else{
		 while( !st.empty() && st.back() >= a[i] ) st.pop_back();
		 if(!st.empty()) cout << st.back() << ' ';
		 st.pb(a[i]);
		}
	}*/
	/*

	deque<int> dq;
	ll m = INT_MAX;
	for( int i = 0; i < k; ++i )
	{
		m = min(m, a[i]);
	}
	//cout << m << ' ';
	dq.push_front(m);
	int l = 0, r = k-1;
	for( l,r; r < n; l++, r++ )
	{	
		while( !dq.empty() && dq.back() > a[r] ) dq.pop_back();
		dq.push_back(a[r]);
		cout << dq.front() << ' ';
		if(a[l] == dq.front()) dq.pop_front();
	}

	*/
	return 0;
}