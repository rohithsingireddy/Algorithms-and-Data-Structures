#include<bits/stdc++.h>
const int MAX = 100000000;

template<typename T>
struct vertex{
	T label;
	//int capacity;
	vertex<T>* parent=nullptr;
	std::unordered_map<vertex<T>*, int> adj;
	bool color = 0;
	vertex(T i){label = i;}
};

template<typename T>
std::vector<std::vector<int>> foldFulkerson(std::vector<vertex<T>*> g, std::vector<vertex<T>*> res_g){

	int s=0;
	int t = g.size()-1;
	std::vector<std::vector<int>> flow(g.size());
	for(int i=0;i<g.size();i++)
		for(int j=0;j<g.size();j++)
			flow[i].push_back(0);
	while(1)
	{
		for(int i=0;i<g.size();i++)
		{
			res_g[i]->color = 1;
			res_g[i]->parent = nullptr;
		}
		std::deque<vertex<T>*> dq;
		dq.push_back(res_g[s]);
		res_g[s]->color = 0;
		while(!dq.empty())
		{
			vertex<T> *u = dq.front();
			dq.pop_front();
			for(auto v:u->adj)
			{
				if(v.first->color)
				{
					v.first->color = 0;
					v.first->parent = u;
					dq.push_back(v.first);
				}
			}
		}
		//std::cout<<res_g[t]->parent->label;
		auto temp = res_g[t];
		int min_cap = MAX;
		if(temp->parent==nullptr)
			break;
		while(temp->parent!=nullptr)
		{
			min_cap = std::min(min_cap, temp->parent->adj[temp]);
			temp = temp->parent;
		}
		//std::cout<<min_cap;
		temp = res_g[t];
		while(temp->parent!=nullptr)
		{
			auto u = temp->parent->label;
			auto v = temp->label;
			temp = temp->parent;
			if(g[u]->adj.find(g[v])!=g[u]->adj.end())
			{
				flow[u][v] += min_cap;
				res_g[u]->adj[res_g[v]] = g[u]->adj[g[v]] - flow[u][v];
				res_g[v]->adj.erase(res_g[u]);
				res_g[v]->adj.insert({res_g[u],flow[u][v]});

			}
			else if(g[v]->adj.find(g[u])!=g[v]->adj.end())
			{
				flow[v][u] -= min_cap;
				res_g[v]->adj[res_g[u]] = g[v]->adj[g[u]] - flow[v][u];
				res_g[u]->adj.erase(res_g[v]);
				res_g[u]->adj.insert({res_g[v], flow[v][u]});

			}
			else{
				res_g[v]->adj.erase(res_g[u]);
				res_g[u]->adj.erase(res_g[v]);
				res_g[v]->adj.insert({res_g[u],0});
				res_g[u]->adj.insert({res_g[v], 0});
			}
			if(res_g[u]->adj[res_g[v]] == 0)
				res_g[u]->adj.erase(res_g[v]);
			if(res_g[v]->adj[res_g[u]] == 0)
				res_g[v]->adj.erase(res_g[u]);
		}
		//break;
	}
	return flow;
}


int main(){
	int n;
	std::cin>>n;
	std::vector<vertex<int>*> g(n),res_g(n);
	for(int i=0;i<n;i++)
	{
		g[i] = new vertex<int>(i);
		res_g[i] = new vertex<int>(i);
	}
	int e;
	std::cin>>e;
	while(e--){
		int a, b, c;
		std::cin>>a>>b>>c;
		g[a]->adj.insert({g[b], c});
		res_g[a]->adj.insert({res_g[b], c});
	}
	auto temp = foldFulkerson(g,res_g);
	for(auto i:temp){
		for(auto j:i)
			std::cout<<j<<' ';
		std::cout<<'\n';
	}
}