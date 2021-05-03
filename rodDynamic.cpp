#include<bits/stdc++.h>
using namespace std;

int rodcut(int *p, int n){
	int r[n+1], cut[n+1];
	r[0] = 0;
	cut[0] = 0;
	int q = -1;
	for(int i=1;i<=n;i++)
	{
		q = -1;
		for(int j=0;j<i;j++){
			if(q<p[j]+r[i-1-j]){
				q = p[j] + r[i-j-1];
				cut[i] = j+1; 
			}
		}
		r[i] = q;
	}
	for(auto i:cut)
		cout<<i<<' ';
	cout<<'\n';
	return r[n];
}

int main(){
	int a[]{1,20,33,36};
	cout<<rodcut(a,4);
}