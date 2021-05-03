#include<bits/stdc++.h>
const int MAX = 100000;

template<typename T>
struct vertex{
	int d = MAX;
	vertex *p;
	T label;
	vertex(T l){
		label = l;
		p = nullptr;
	}

};



template<typename T>
struct edge
{
	vertex<T> *u, *v;
	double weight;
	edge(vertex<T>* a, vertex<T> *b, double w){
		u = a;
		v = b;
		weight = w;
	}
	bool operator==(const edge<T>& b) const{
		return (u->label==b.u->label) && (v->label==b.v->label);
	}
	bool operator<(const edge<T> *b) const{
		return weight < b->weight;
	}
};


template<typename T>
struct myHash
{
	std::size_t operator()(const edge<T>& e) const{
		std::size_t h1 = std::hash<int>()(e.u->label);
		std::size_t h2 = std::hash<int>()(e.v->label);
		return h1^(h2<<1);
	}
};

template<typename T>
void relax(vertex<T>* u, vertex<T>* v, int w)
{
	if(v->d > u->d + w){
		v->d = u->d + w;
		v->p = u;
	}
}

int main(){
	int n;
	std::cin>>n;
	vertex<int> *gv[n];
	for(int i=0;i<n;i++)
		gv[i] = new vertex<int>(i);
	int e;
	std::cin>>e;
	std::unordered_map<edge<int>, int, myHash<int>> ew;
	while(e--){
		int a,b,w;
		std::cin>>a>>b>>w;
		ew[edge<int>(gv[a],gv[b], 0)] = w;
	}
	gv[0]->d = 0;
	for(int i=0;i<n-1;i++){
		for(auto i:ew){
			//std::cout<<i.first.u->label<<' '<<i.first.v->label<<' '<<i.second<<'\n';
			relax(i.first.u, i.first.v, i.second);
		}
	}
	for(auto i:gv)
		std::cout<<i->label<<' '<<i->d<<'\n';
}