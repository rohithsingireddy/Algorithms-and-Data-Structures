#include<bits/stdc++.h>
using namespace std;

int dp(vector<string> grid, int r, int c){
	if(r<=0 || c<=0 || r>grid.size() || c>grid[0].size())
		return 0;
	if(r==grid.size()-1 && c==grid[0].size()-1)
		return 0;
	if(grid[r][c]=='.')
		return min(dp(grid,r+1,c),dp(grid,r,c+1));
	else if(grid[r][c]=='#')
		return 1 + min(dp(grid,r+1,c), min(grid,r,c+1));
}


int main(){
	int r,c;
	cin>>r>>c;
	vector<string> grid(r);
	for(int i=0;i<r;i++)
		cin>>grid[i];
	cout<<dp(grid,0,0);
}