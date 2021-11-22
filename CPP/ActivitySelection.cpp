#include<bits/stdc++.h>
//Dynamic Approach
int dp[100][100], am[100][100];

int activity_selection(int *s, int *f, int i, int j, int size){
	
	if(i==j||j==i+1)
		return 0;
	
	if(dp[i][j]>-1)
		return dp[i][j];

	//if((s[i]>=f[j] || s[j]>=f[i]))
		dp[i][j] = 0;
	//else 
	//	return 0;
	for(int k=0;k<size;k++){
		auto temp = activity_selection(s,f,i,k, size)+activity_selection(s,f,k,j,size)+1;
		if(f[i]<=s[k] && f[k]<=s[j]){
			if(dp[i][j] < temp){
				dp[i][j] = temp;
				am[i][j] = k;
			}
		}
	}

	return dp[i][j];
}

void print(int i, int j){
	if(dp[i][j]>0){
		auto temp = am[i][j];
		std::cout<<temp<<' ';
		print(i,temp);
		print(temp,j);
	}
}


int main(){
	int s[]{-2, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 20};		//Adding two sentinel jobs at begining and end
	int f[]{-1, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 21};
	for(int i=0;i<100;i++)
		std::fill(dp[i], dp[i]+100,-1);
	std::cout<<activity_selection(s,f,0,12, 13)<<'\n';
	print(0,12);
	/*int m = -1;
	for(int i=0;i<11;i++)
		for(int j=0;j<11;j++){
			m = std::max(m , activity_selection(s,f,i,j));
		}
	std::cout<<m;
*/
}