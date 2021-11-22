#include<bits/stdc++.h>
using namespace std;
std::vector<int> compute_prefix(std::string p)
{
	int m = p.size();
	std::vector<int> pre_arr(m);
	pre_arr[0] = -1;
	int k=-1;
	for(int q=1;q<m;q++)
	{
		while(k>-1 && p[k+1]!=p[q])
			k = pre_arr[k];
		if(p[k+1]==p[q])
			k++;
		pre_arr[q] = k;
	}
	//for(auto i:pre_arr)
	//	std::cout<<i<<' ';
	//std::cout<<'\n';
	return pre_arr;
}
/*
void KMP_matcher(std::string s, std::string p)
{
	int n = s.size();
	int m = p.size();
	std::vector<int> pre_arr = compute_prefix(p);
	int q = -1, flag=0;
	for(int i=0;i<n;i++)
	{
		while(q>-1 && p[q+1]!=s[i])
			q = pre_arr[q];
		if(p[q+1]==s[i])
			q++;
		if(q==m-1){
			std::cout<<"Pattern Matched at "<<i-m+1<<'\n';
			flag = 1;
			q = pre_arr[q];
		}
	}
	if(flag==0)
		std::cout<<"Pattern Not Found\n";
	return;
}	
*/
int main(){
	std::string s;
	std::cin>>s;
	auto f = compute_prefix(s);
	int n = s.size() - 1;
	bool mark[n];
	memset(mark, 0, sizeof mark);
	mark[0]=true;
	int k = f[n-1];
	while ( k != -1 && !mark[k] )	  k=f[k-1];
	if (k) cout<<s.substr(0,k);
	else cout<<"Just a legend";
}