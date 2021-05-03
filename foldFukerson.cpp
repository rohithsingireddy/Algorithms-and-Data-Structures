

#include<bits/stdc++.h>
using namespace std;
const int inf = 99999;

int main(){
	int n;
	cin>>n;
	int e;
	cin>>e;
	string s;
	stringstream ss;
	int edges[n][n], flow[n][n], res[n][n];
	set<int> adj[n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			edges[i][j] = 0;
			flow[i][j] = 0;
			res[i][j] = 0;
		}
	//for(int i=0;i<n;i++)
	for(int i=0;i<e;i++){
		cin>>ws;
		getline(cin,s);
		ss.clear();
		ss.str(s);
		int a,b,c;
		ss>>a>>b>>c;
		edges[a][b] = c;
		res[a][b] = c;
		adj[a].insert(b);
	}
	int src=0,tar=n-1;
	while(1){
		int parent[n];
		queue<int> q;
		bool color[n];
		fill(parent,parent+n,-1);
		fill(color,color+n,1);
		color[src] = 0;
		q.push(src);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(auto v:adj[u]){
				if(color[v]){
					color[v] = 0;
					parent[v] = u;
					q.push(v);
				}
			}
		}
		int temp = tar;
		int min_cap=99999;
		if(parent[temp]==-1)
			break;
		while(parent[temp]!=-1){
			auto temp1 = min_cap;
			auto temp2 = res[parent[temp]][temp];
			min_cap = min(temp1,temp2);
			temp = parent[temp];
		}
		temp = tar;
		while(parent[temp]!=-1){
			auto a = parent[temp];
			auto b = temp;
			if(edges[a][b]>0){
				flow[a][b] += min_cap; 
			}
			else{
				flow[a][b] -= min_cap;
			}
			temp = parent[temp];
		}
		temp = tar;
		while(parent[temp]!=-1){
			auto a = parent[temp];
			auto b = temp;
			if(edges[a][b]){
				res[a][b] = edges[a][b] - flow[a][b];
				res[b][a] = flow[b][a];
				adj[b].insert(a);
			}
			else if(edges[b][a]){
				res[b][a] = edges[b][a] - flow[b][a];
				res[a][b] = flow[a][b];
				adj[a].insert(b);
			}
			else{
				res[a][b]=0;
				res[b][a] = 0;
			}
			if(res[a][b]==0)
				adj[a].erase(b);
			if(res[b][a]==0)
				adj[b].erase(a);
			temp = parent[temp];
		}
	}
	std::cout<<'\n';
	for(auto i=0;i<n;i++){
		for(auto j=0;j<n;j++)
			cout<<flow[i][j]<<' ';
		cout<<'\n';
	}
}