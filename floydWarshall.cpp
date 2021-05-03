#include<bits/stdc++.h>
typedef std::vector<std::vector<int>> t;
const int MAX = 1000000;

t flyodWarshall(t wm, t &pred){
	int n = wm.size();
	//t temp(n);
	//for(int i=0;i<n;i++)
	//	temp[i].resize(n);
	//temp = wm;
	for(int k=0;k<n;k++){
		//temp[i][j] = MAX;

		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				
				if(wm[i][j] >= wm[i][k] + wm[k][j]){
					wm[i][j] = wm[i][k] + wm[k][j];
					pred[i][j] = pred[k][j];
				}
			}
	}
	return wm;
}

int main(){
	
	int n;
	std::cin>>n;
	t v(n), p(n);
	for(int i=0;i<n;i++)
		v[i].resize(n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(i==j)
				v[i][j] = 0;
			else
				v[i][j] = MAX;
			p[i][j] = -1;
		}
	int e;

	std::cin>>e;
	
	while(e--){
		int a, b, w;
		std::cin>>a>>b>>w;
		v[a][b] = w;
		p[a][b] = a;
	}
	auto temp = flyodWarshall(v, p);
	std::cout<<'\n';
	for(auto i:p){
		for(auto j:i)
			std::cout<<j<<' ';
		std::cout<<'\n';
	}
}