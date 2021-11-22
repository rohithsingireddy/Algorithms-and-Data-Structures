#include<bits/stdc++.h>

template<typename T=int>
struct LinkedNode{
	LinkedNode<T> *prev=nullptr, *next=nullptr;
	T val = T();
	LinkedNode(T v):val{v}{}
};

template<typename T=int>
struct LinkedList{
	LinkedNode<T> *head=nullptr, *tail=nullptr;
	LinkedList(){}
	 void insert(T v){
	 	if(head == nullptr){
	 		head = new LinkedNode<T>(v);
	 		tail = head;
	 	}
	 	else{
	 		LinkedNode<T> *temp = new LinkedNode<T>(v);
	 		tail->next = temp;
	 		temp->prev = tail;
	 		tail = temp;
	 	}
	 }

	 LinkedNode<T>* search(T val){
	 	auto temp = head;
	 	while(temp!=nullptr){
	 		if(temp->val == val)
	 			return temp;
	 		temp = temp->next;
	 	}
	 	return nullptr;
	 }

	 void remove(LinkedNode<T>* temp){
	 	if(temp==head){
	 		head = head->next;
	 		head->prev = nullptr;
	 	}
	 	else if(temp==tail){
	 		tail = tail->prev;
	 		tail->next = nullptr;
	 	}
	 	else
	 	{ 
	 		temp->next->prev = temp->prev;
	 		temp->prev->next = temp->next;
	 	}
	 }

	 void print(){
	 	auto temp = head;
	 	while(temp){
	 		std::cout<<temp->val<<' ';
	 		temp = temp->next;
	 	}
	 }


	 void merge(LinkedList<T>* b){
	 	if(b->head==nullptr)
	 		return;
	 	else if(head==nullptr)
	 		return;
	 	else
	 	{
	 		this->tail->next = b->head;
	 		b->head->prev = this->tail;
	 		this->tail = b->tail;
	 		return;
	 	}
	 }
};




template<typename T>
struct set_node{
	set_node<T> *parent;
	LinkedList<T> *l;
	int rank;
	T label;
	set_node(T d){
		label  = d;
		l = new LinkedList<T>();
		l->insert(d);
		parent = this;
		rank = 0;
	}
};

template<typename T>
set_node<T>* find_set(set_node<T>* s){
	if(s->parent!=s)
		s->parent = find_set(s->parent);
	return s->parent;
}

template<typename T>
void union_set(set_node<T> *a, set_node<T>* b){
	auto a_parent = find_set(a);
	auto b_parent = find_set(b);
	if(a_parent->rank > b_parent->rank)
	{
		b_parent->parent = a_parent;
		a_parent->l->merge(b_parent->l);
	}
	else{
		a_parent->parent = b_parent;
		b_parent->l->merge(a_parent->l);
		if(a_parent->rank==b_parent->rank)
			b_parent->rank++;
	}
}

template<typename T>
struct vertex{
	T label;
	vertex(T l):label{l}{}
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
	bool operator==(edge<T> *b) const{
		return (u==b->u) && (v==b->v);
	}
	bool operator<(const edge<T> *b){
		return weight < b->weight;
	}
};


template<typename T>
struct myHash
{
	std::size_t operator()(edge<T> *e) const{
		std::size_t h1 = std::hash<int>{}(e->u->label);
		std::size_t h2 = std::hash<int>{}(e->v->label);
		return (h1>>1)^(h2<<1);
	}
};

template<typename T>
struct myComparator{
	bool operator()(edge<T>  *a, edge<T> *b) const{
		return a->weight < b->weight;
	}
};

int main(){
	int n;
	std::cin>>n;
	vertex<int> *graph_vertex[n];
	for(int i=0;i<n;i++)
		graph_vertex[i] = new vertex<int>(i);
	int e;
	std::cin>>e;
	//std::unordered_map<edge<int>, int> edge_weights;
	std::vector<edge<int>*> edge_weights;
	while(e--)
	{
		int a, b, w;
		std::cin>>a>>b>>w;
		edge<int> *temp = new edge<int>(graph_vertex[a], graph_vertex[b], w);
		edge_weights.push_back(temp);
	}
	std::sort(edge_weights.begin(), edge_weights.end(), myComparator<int>());
	//for(auto i:edge_weights)
	//	std::cout<<i->weight<<' ';
	set_node<vertex<int>*> *s[n];
	for(int i=0;i<n;i++)
		s[i] = new set_node<vertex<int>*>(graph_vertex[i]);
	std::vector<edge<int>*> k_set;
	for(auto i:edge_weights){
		set_node<vertex<int>*> *temp1 = find_set(s[i->u->label]);
		set_node<vertex<int>*> *temp2 = find_set(s[i->v->label]);
		if(temp1 != temp2){
			k_set.push_back(i);
			union_set(temp1, temp2);
		}
	}

	for(auto i:k_set)
		std::cout<<i->u->label<<' '<<i->v->label<<' '<<i->weight<<'\n';

}