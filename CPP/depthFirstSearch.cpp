#include<bits/stdc++.h>

int t = 1;
int con_comp=0;//connected components
template<typename T>
struct vertex
{
	T label;
	int start;
	char color;
	int finish;
	vertex *parent;
	int cc;//for undirected graphs
	int inDegree, outDegree;
	std::vector<vertex<T>*> adj;
	vertex(T i){
		cc = 0;
		label = i;
		start = 0;
		finish = 0;
		color = 'W';
		parent = nullptr;
		inDegree = 0;
		outDegree = 0;
	}
};


template<typename T=int>
std::vector<vertex<T>*> graph_transpose(std::vector<vertex<T>*> graph)
{
	std::vector<vertex<T>*> temp(graph.size());
	for(int i=0;i<graph.size();i++)
		temp[i] = new vertex<T>(i);
	for(auto i:graph)
		for(auto j:i->adj){
			temp[j->label]->adj.push_back(temp[i->label]);;
			temp[j->label]->outDegree++;
			temp[i->label]->inDegree++;
		}
	return temp;
}

template<typename T>
void dfs(std::vector<vertex<T>*> g, int no_vertices){
	t = 1;
	con_comp = 0;
	for(int i=0;i<no_vertices;i++)
		if(g[i]->color=='W')
		{
			g[i]->cc = ++con_comp;
			dfs_vertex(g[i]);
		}
	t = 1;
	con_comp = 0;
}

template<typename T>
void dfs_vertex(vertex<T> *u){
	u->color = 'G';
	u->start = t++;
	for(auto v:u->adj){
		if(v->color == 'W')
		{
			//v->color = 'G';
			v->cc = con_comp;
			v->parent = u;
			dfs_vertex(v);
		}
	}
	u->color = 'B';
	u->finish = t++;
}

template<typename T=int>
struct comparator{
	bool operator()(vertex<T>* a, vertex<T>* b){
		return a->finish > b->finish;
	}
};

template<typename T>
void dfs_transpose(std::vector<vertex<T>*> g_t, std::vector<vertex<T>*> g){

	sort(g.begin(), g.end(), comparator<T>());
	t = 1;
	con_comp = 0;
	for(auto i:g){
		if(g_t[i->label]->color=='W')
		{
			g_t[i->label]->cc = ++con_comp;
			dfs_vertex(g_t[i->label]);			 
		}
	}
	con_comp = 0;
	t = 1;
}

int main(){
	int n;
	std::cin>>n;
	std::vector<vertex<int>*> v(n);
	for(int i=0;i<n;i++)
		v[i] = new vertex<int>(i);
	int e;
	std::cin>>e;
	while(e--){
		int a,b;
		std::cin>>a>>b;
		v[a]->adj.push_back(v[b]);
		v[b]->inDegree++;
		v[a]->outDegree++;
	}
	//dfs(v,n);
	//std::cout<<v[n-1]->finish;
	//print_path(v[0], v[n-1]);
	dfs(v,n);
	auto tran = graph_transpose(v);
	dfs_transpose(tran, v);
	for(auto i:tran){
		std::cout<<i->label<<' '<<i->cc;
		std::cout<<'\n';
	}
	
}