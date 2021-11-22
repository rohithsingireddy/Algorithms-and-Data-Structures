#include<bits/stdc++.h>
typedef std::vector<std::vector<int>> vec;
const int max = 10000000;
template<typename T>
struct vertex{
	T label;
	int height = 0;
	int excess_flow = 0;
	std::vector<vertex<T>*> neighbours;
	std::unordered_map<vertex<T>*, int> adj;
	vertex(T i){label = i;}
};

template<typename T>
void push(vertex<T> *ul, vertex<T>* vl, std::vector<vertex<T>*> g, std::vector<vertex<T>*> res_g, vec& flow)
{
			auto u = ul->label;
			auto v = vl->label;
			auto min_cap = std::min(ul->excess_flow, res_g[u]->adj[res_g[v]]);

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
			

	ul->excess_flow -= min_cap;

	vl->excess_flow += min_cap;
}


template<typename T>
void relabel(vertex<T>* u)
{
	int h = max;
	for(auto v:u->adj)
	{
		h = std::min(h, 1+v.first->height);
	}
	if(h!=max)
		u->height = h;
}

template<typename T>
void discharge(vertex<int>* u, std::vector<vertex<T>*> g, std::vector<vertex<T>*> rg, vec& flow)
{
	auto i = 0;
	while(u->excess_flow > 0)
	{
		//std::cout<<u->excess_flow<<' ';
		if(i==u->neighbours.size()){
			i = 0;	
			relabel(u);
		}
		else if(u->adj.find(u->neighbours[i])!=u->adj.end() && u->height == u->neighbours[i]->height+1)
		{
			push(u, u->neighbours[i], g, rg, flow);
		}
		else
			i++;
		//std::cout<<i;
	}
}

template<typename T>
vec relabelTofront(std::vector<vertex<T>*> g, std::vector<vertex<T>*> rg)
{
	int s = 0;
	int n = g.size();
	int t = g.size()-1;
	std::vector<std::vector<int>> flow(n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			flow[i].push_back(0);
	rg[s]->height = n;
	std::vector<vertex<T>*> st;
	for(auto v:rg[s]->adj)
	{
		rg[s]->excess_flow -= rg[s]->adj[v.first];
		flow[rg[s]->label][v.first->label] = rg[s]->adj[v.first];
		v.first->excess_flow = rg[s]->adj[v.first];
		v.first->adj.insert({rg[s], rg[s]->adj[v.first]});
		//rg[s]->adj.erase(v.first);
		st.push_back(v.first);
	}
	for(auto i:st){
		rg[s]->adj.erase(i);
	}


	std::deque<vertex<T>*> list;
	for(int i=1;i<n-1;i++){

		list.push_back(rg[i]);
		//std::cout<<list[i]->label;
	}
	
	int i = 0;

	while(i < list.size())
	{
		int old_height = list[i]->height;

		discharge(list[i], g, rg, flow);
		if(list[i]->height > old_height)
		{
			auto temp = list[i];
			list.erase(list.begin()+i);
			list.push_front(temp);
			i = 0;
		}
		i++;
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
		g[a]->neighbours.push_back(g[b]);
		g[b]->neighbours.push_back(g[a]);
		res_g[a]->adj.insert({res_g[b], c});
		//res_g[b]->adj.insert({res_g[a], 0});
		res_g[a]->neighbours.push_back(res_g[b]);
		res_g[b]->neighbours.push_back(res_g[a]);
	}
	auto temp = relabelTofront(g,res_g);
	for(auto i:temp){
		for(auto j:i)
			std::cout<<j<<' ';
		std::cout<<'\n';
	}
}

