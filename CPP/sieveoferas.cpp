
//Sieve of erasthonesis

#include<bits/stdc++.h>
using namespace std;
typedef long long u_64;
const u_64 N = 1e7;
vector<bool> primes(N+1);

void sieveOfEr(){
	
	fill(primes.begin(), primes.end(), 1);
	primes[1] = 1;
	primes[2] = 1;
	for(u_64 i=2;i<=N;i++ )
	{
		if(primes[i] && i*i<=N)
		{
			for(u_64 j=i*i;j<=N;j += i)
				primes[j] = 0;

		}
	}
}

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



int main(int argc, char** argv){
	sieveOfEr();
	ofstream of(argv[1]);

	for(int i=1;i<=N;i++)
	{
		if(primes[i])
			of<<i<<", ";
	}
}
