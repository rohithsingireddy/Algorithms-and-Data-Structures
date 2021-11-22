#include<bits/stdc++.h>

template<typename T>
struct vertex{
	T label;
	vertex* parent;
	std::vector<vertex*> adj;
	char color;
	int d;
	vertex(T i){
		label = i;
		parent = nullptr;
		color = 'W';
		d = 0;
	}
};

template<typename T>
void bfs(vertex<T> *s){
	std::deque<vertex<T>*> dq;
	dq.push_back(s);
	s->color = 'G';
	while(!dq.empty()){
		auto u = dq.front();
		dq.pop_front();
		for(auto v:u->adj){
			if(v->color == 'W'){
				v->color = 'G';
				v->parent = u;
				v->d = u->d+1;
				dq.push_back(v);
			}
		}
		u->color = 'B';
	}
}
template<typename T>
void print_path(vertex<T>* a, vertex<T>* b)
{
	if(b!=nullptr){
		print_path(a, b->parent);
		std::cout<<b->label<<' ';
	}
}

int main(){
	int n;
	std::cin>>n;
	vertex<int>* v[n];
	for(int i=0;i<n;i++)
		v[i] = new vertex<int>(i);
	int e;
	std::cin>>e;
	while(e--){
		int a,b;
		std::cin>>a>>b;
		v[a]->adj.push_back(v[b]);
	}
	bfs(v[0]);
	print_path(v[0], v[n-1]);
}