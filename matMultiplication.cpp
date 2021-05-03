#include<bits/stdc++.h>
using namespace std;
int dp[100][100], s[100][100];

double matMultiply(int *a, int i, int j){ // Top-Down Memoization Approach
	if(i==j) return 0;
	if(dp[i][j]>0) return dp[i][j];

	double m = 10e9;
	for(int k = i; k<j; k++){
		auto temp = matMultiply(a, i, k) + matMultiply(a, k+1, j) + a[i-1]*a[k]*a[j];
		if(m>temp)
		{
			m = temp;
			s[i][j] = k;
		}
	}
	dp[i][j] = m;
	return dp[i][j];
}

void print(int i,int j){
	if(i==j)
		cout<<' '<<i<<' ';
	else{
		cout<<"( ";
		print(i,s[i][j]);
		print(s[i][j]+1, j);
		cout<<") ";
	}
}

int main(){
	int a[]{5,10,3,12,5,50,6};
	for(int i=0;i<100;i++){
		fill(dp[i], dp[i]+100,0);
		fill(s[i], s[i]+100,0);
	}
	cout<<matMultiply(a, 1, 6)<<'\n';
	print(1,6);
	//cout<<s[1][6];
}