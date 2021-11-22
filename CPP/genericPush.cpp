#include<bits/stdc++.h>
const int MAX = 1000000;
//Does Not terminate
template<typename T>
struct vertex{
	T label;
	int height = 0;
	int excess_flow = 0;
	//int cap = 0;
	std::unordered_map<vertex<T>*, int> adj; //stores capacities
	vertex(T i){
		label = i;
	}
};



template<typename T>
void push(vertex<T> *a, vertex<T> *b, std::stack<T> &st, std::vector<std::vector<T>> &flow, std::vector<vertex<T>*> gv, std::vector<vertex<T>*> rg)
{
	auto r_u = a;
	auto r_v = b;
	auto u = gv[a->label];
	auto v = gv[b->label];
	auto temp = std::min(u->excess_flow, u->adj[v] - flow[r_u->label][r_v->label]);
	std::cout<<temp<<'\n';
	if(u->adj.find(v)!=u->adj.end()){
		flow[u->label][v->label] += temp;
		r_u->adj[r_v] = u->adj[v] - flow[u->label][v->label];
		r_v->adj.erase(r_u);
		r_v->adj.insert({r_u, flow[u->label][v->label]});
	}
	else if(v->adj.find(u)!=v->adj.end()){
		flow[v->label][u->label] -= temp;
		r_v->adj[r_u] = v->adj[u] - flow[v->label][u->label];
		r_u->adj.erase(r_v);
		r_u->adj.insert({r_v, flow[v->label][u->label]});	
	}
	else{
		
		r_u->adj.erase(r_v);
		r_u->adj.insert({r_v,0});
		r_v->adj.erase(r_u);
		r_v->adj.insert({r_u,0});
	}
	if(r_v->adj[r_u] == 0){
		r_v->adj.erase(r_u); //disappears
		//st.push(v);
	}
	if(r_u->adj[r_v] == 0){
		r_u->adj.erase(r_v);//disappears
		//st.push(u);
	}
	u->excess_flow -= temp;
	//if(u->excess_flow > 0)
	//	st.push(u);
	v->excess_flow += temp;
	if(v->excess_flow > 0)
		st.push(v);
}

template<typename T>
void relabel(vertex<T>* u, std::stack<vertex<T>*> &st, std::vector<vertex<int>*> rg){
	int m = MAX;
	for(auto i:rg[u->label]->adj)
		m = std::min(m, i.first->height);
	if(m>=MAX)
		return;
	u->height = m+1;
	rg[u->label]->height = m+1;
	st.push(u);
}

int main(){
	int n;
	std::cin>>n;
	std::vector<vertex<int>*> gv(n),rg(n);
	for(int i=0;i<n;i++)
	{
		gv[i] = new vertex<int>(i);
		rg[i] = new vertex<int>(i);
	}
	//gv[0]->height = n;
	int e;
	std::cin>>e;
	while(e--)
	{
		int a , b,c;
		std::cin>>a>>b>>c;
		//gv[b].cap += c;
		//rg[b].cap += c
		gv[a]->adj.insert({gv[b], c});
		rg[a]->adj.insert({rg[b], c});
	}
	std::stack<vertex<int>*> st;
	std::vector<std::vector<int>> flow(gv.size());
	for(int i=0;i<gv.size();i++)
		for(int j=0;j<gv.size();j++)
			flow[i].push_back(0);
	int s = 0;
	int t = gv.size()-1;
	for(auto i:rg[s]->adj)
	{
		flow[s][i.first->label] = rg[s]->adj[i.first];
		i.first->excess_flow = rg[s]->adj[i.first];
		//std::cout<<i.first->excess_flow<<'\n';
		st.push(rg[i.first->label]);
		rg[s]->excess_flow -= rg[s]->adj[i.first];
		i.first->adj.insert(rg[s], rg[s]->adj[i.first]);
	}
	//std::stack<vertex<int>*> st;
	//st.push(gv[0]);
	rg[s]->height = n;
	while(!st.empty())
	{
		auto u = st.top();
		st.pop();
		//if(u==rg[5])
		//	continue;
		bool flag = 0;
		for(auto v:u->adj)
		{
			//if(v.first==rg[5])
			//	continue;
			flag = 1;
			if(u->height == v.first->height+1 && rg[u->label]->adj.find(rg[v.first->label]) != rg[u->label]->adj.end()){
				//std::cout<<u->excess_flow<<'\n';
				if(u->excess_flow > 0)
					push(u, v.first, st, flow, gv, rg);
				flag = 0;
				//break;
			}
		}
		if(flag==1)
			relabel(u, st, rg);	
	}
	//std::cout<<'\n';
	for(auto i:flow){
		for(auto j:i)
			std::cout<<j<<' ';
		std::cout<<'\n';
	}
}