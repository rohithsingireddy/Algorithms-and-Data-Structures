#include<bits/stdc++.h>
using namespace std;
int dp[100];
int s[100];

int subsequence(int *a, int j){
	if(j==0)
		return 1;
	if(dp[j]>1)
		return dp[j];
	for(int i=j-1;i>=0;i--){
		auto temp = subsequence(a,i);
		if(a[i]<=a[j]){
			dp[j] = max(dp[j],temp+1);
		}
	}
	return dp[j];
}

void print(int *a, int n){
	if(n!=0){
		
		print(a, s[n]);
		cout<<a[s[n]]<<' ';
	}
}

int main(){
	int a[]{1,3,2,5,4,6,5,7,10,11,8};
	fill(dp, dp+100, INT_MAX);
	//fill(s, s+100, -1);
	/*dp[0] = 1;
	for(int i=1;i<11;i++)
		for(int j=i-1;j>=0;j--)
			if(a[j]<=a[i]){
				dp[i] = max(dp[i], dp[j]+1);
				break;
			}
	for(int i=0;i<11;i++)
		cout<<dp[i]<<' ';
	cout<<'\n';
		fill(dp, dp+100, 1);
	subsequence(a,10);
		for(int i=0;i<11;i++)
		cout<<dp[i]<<' ';*/
		dp[0] = -mod;
	for( int i = 1; i <= n; ++i )
	{
		int j = upper_bound(dp, dp+n+1, a[i]) - dp;
		if(dp[j-1] < a[i-1] && a[i-1] < dp[j] ) dp[j] = a[i-1];
	}
	for( int i = 1; i <= n; ++i ) cout << dp[i] << '\n';

}