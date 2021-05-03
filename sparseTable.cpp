#include <bits/stdc++.h>
#ifdef NANANA
	#include "containerHelper.h"
#endif
using namespace std;


#define ll long long
#define p(i,j) pair<i,j>
#define v(i) vector<i>
#define pb push_back
#define pf push_front
#define x first
#define y second
#define all(x) begin(x), end(x)
#define FASTIO ios::sync_with_stdio(false);cin.tie(NULL);

const int N = 1e6;
const int K = int(log2(N))+5;
const int MOD = 1e9+7;
int sT[N][K];


int logArray[N+1];
void preCompLog()
{
    logArray[1] = 0;
    for( int i = 2; i <= N; i++) logArray[i] = logArray[i/2]+1;
}

//Minimum sparse tree
void createTable(int *a, int n)
{
    for(int i = 0; i < n; ++i)
        sT[i][0] = a[i];
    
    for( int j = 1; j <= int(log2(n)); j++)
        for( int i = 0; i + (1<<j) <= n; i++ )
            sT[i][j] = min(sT[i][j-1], sT[i+(1<<(j-1))][j-1]);
}


int main()
{
    int arr[] = {
        5,34,2,12,45,32,56,234,45,-12,4
            };
    createTable(arr, 11);
    int k = log2(3-0+1);
    
    cout << min(sT[0][k], sT[3 - (1<<k)+1][k]);
    
}
