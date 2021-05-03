#include<bits/stdc++.h>
using namespace std;
int dp[100][100];
char s[100][100];

int length(string s1, string s2, int i, int j){
	if(i < 0||j < 0)
		return 0;
	if(dp[i][j])
		return dp[i][j];
	if(s1[i]==s2[j]){
		s[i][j] = 'C';
		return 1 + length(s1,s2,i-1,j-1);
	}
	int tempi = length(s1,s2,i-1,j);
	int tempj = length(s1,s2,i,j-1);
	if(tempi>=tempj)
		s[i][j] = 'U';
	dp[i][j] =  max(tempi, tempj);
	return dp[i][j];
}

void print(string s1, int i, int j){
	if(i<0 || j<0)
		return;
	if(s[i][j]=='C'){
		//cout<<s1[i];
		print(s1, i-1, j-1);
		cout<<s1[i];
	}
	else if(s[i][j]=='U')
		print(s1, i-1, j);
	else
		print(s1, i, j-1);
}



int main(){
	string s1{"10010101"};
	string s2{"010110110"};
	for(int i=0;i<100;i++){
		fill(dp[i], dp[i]+100, 0);
		fill(s[i], s[i]+100, ' ');
	}
	cout<<length(s1,s2,s1.size()-1, s2.size()-1)<<'\n';
	print(s1, s1.size()-1, s2.size()-1);
}
