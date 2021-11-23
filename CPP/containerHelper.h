


/*Matrix adjacent
//			 D  R   U   L
map<char, int> dir{ {'D', 0},
					{'R', 1},
					{'U', 2},
					{'L', 3}
					};
v(int) dx = {1, 0, -1,  0};
v(int) dy = {0, 1,  0, -1};
*/

/*Disjoint Set Union
int s[N]; ll mx[N];

int findParent(int i)
{
	if( i == s[i] )
		return i;
	return s[i] = findParent(s[i]);
}

void setUnion(int a, int b, int c){
	int x = findParent(a);
	int y = findParent(b);
	if( x != y ){
		if( mx[x] > mx[y] )
			s[y] = x, mx[x] += mx[y];
		else
			s[x] = y, mx[y] += mx[x];
	}
}

*/

/*Factorization
unordered_map<long long, long long> factors( long long n ){
        long long cnt = 1; // For one
        unordered_map<int, int> m;
        while( !(n&1) )
                m[2]++, n >>= 1;
        for( ll i = 3; i*i <= n; i += 2 )
        {
                while( n%i == 0 )
                        m[i]++, n /= i;
        }
        if( n > 1 ) m[n]++;
        for( auto &&i: m ) cnt *= (i.y+1);
        cout << cnt;
        return m;
}

*/

/* Binary Search Tempaltes
while( low < high ) // For finding a maximum among equals
	{
		ll mid = (low + high +1) >> 1;
		cout << "Q " << mid << endl;
		int k;
		cin >> k;
		if(k)
			low = mid;
		else
			high = mid - 1;
		//cout << low << ' ' << high << '\n';
	}
	//cout << low;
	ll k = low;
	low = 0, high = 1e5;
	while( low < high ) // For finding minimum among equals or a 
	//normal binary search
	{
		ll mid = (low+high) >> 1;
		ll t = noOfZeroes(mid);
		if( t < k )
			low = mid + 1;
		else
			high = mid;
	}
	
*/


