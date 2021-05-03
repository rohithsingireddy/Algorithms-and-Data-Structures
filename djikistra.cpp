#include<bits/stdc++.h>
const int MAX = 100000;


template<typename T>
struct vertex{
	vertex<T> *parent;
	T label;
	int d = MAX;
	std::unordered_map<vertex<T>*, int> adj;
	vertex(int i){label = i;}	
};



template<typename T=vertex<int>>
struct LinkedNode{
	LinkedNode<T> *prev=nullptr, *next=nullptr;
	T val = T();
	LinkedNode(T v):val{v}{}
};

template<typename T=vertex<int>>
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

	 void remove(T t){
	 	auto temp = search(t);
	 	if(temp==head){
	 		head = head->next;
	 		if(head!=nullptr)
	 			head->prev = nullptr;
	 	}
	 	else if(temp==tail){
	 		tail = tail->prev;
	 		if(tail!=nullptr)
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

	 LinkedList<T>* merge(LinkedList<T>* b){
	 	if(b->head==nullptr)
	 		return this;
	 	else if(head==nullptr)
	 		return b;
	 	else
	 	{
	 		this->tail->next = b->head;
	 		b->head->prev = this->tail;
	 		this->tail = b->tail;
	 		return this;
	 	}
	 }
};







template<typename T=vertex<int>>
struct node{
	node<T> *parent, *left, *right;
	std::vector<node<T>*> child;
	int degree;
	bool mark;
	T data;
	node(T d = T()){
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		degree = 0;
		mark = 0;
		data = d;
	}
	/*~node(){
		delete parent;
		delete child;
		delete left;
		delete right;
	}*/
};

template<typename T=vertex<int>>
struct FibonacciHeap{
	node<T> *min = nullptr;
	int no_of_nodes = 0;
	LinkedList<node<T>*> *root_list=new LinkedList<node<T>*>();
	//int root_index = -1;

	node<T>* fib_insert(T val){
		node<T> *temp = new node<T>(val);
		if(min == nullptr){
			//root_index++;
			//root_list.push_back(temp);
			root_list->head =  new LinkedNode<node<T>*>(temp);
			root_list->tail = root_list->head;
			min = temp;
		}
		else{
			root_list->insert(temp);
			if(val->d < min->data->d){
				min = temp;
			}
		}
		no_of_nodes++;
		return temp;
	}

	bool isEmpty(){return no_of_nodes==0;}

	node<T>* extractMin(){
		auto z = min;
		if(z!=nullptr){
			for(auto t:z->child){
				root_list->insert(t);
				t->parent = nullptr;
			}
			root_list->remove(z);
			if(z==z->right)
				min == nullptr;
			else{
				min = z->right;
				consolidate();
			}
			no_of_nodes--;

		}
		return z;
	}

	void consolidate(){
		int n = std::ceil(std::log2(no_of_nodes))+1;
		std::vector<node<T>*> a(n);
		for(int i=0;i<n;i++)
			a[i] = nullptr;
		auto w  = root_list->head;
		while(w!=nullptr){
			auto x = w->val;
			int d = x->degree;
			while(a[d]!=nullptr)
			{
				auto y = a[d];
				if(x->data->d > y->data->d)
					std::swap(x,y);
				fib_heap_link(y,x);
				a[d] = nullptr;
				d++; 
			}
			a[d] = x;
			w = w->next;
		}
		min = nullptr;
		for(int i=0;i<n;i++){
			if(a[i]!=nullptr){
				if(min==nullptr){
					root_list->head = new LinkedNode<node<T>*>(a[i]);
					root_list->tail = root_list->head;
					min = a[i];
				}
				else{
					root_list->insert(a[i]);
					if(a[i]->data->d < min->data->d)
						min = a[i];
				}
			}
		}

	}

	void fib_heap_link(node<T> *y, node<T>* x){
		root_list->remove(y);
		x->child.push_back(y);
		y->parent = x;
		x->degree++;
		y->mark = 0;
	}

	void decrease_Key(node<T> *x, int k){
		if(k > x->data->d)
			throw "ERROR\n";
		x->data->d = k;
		auto y = x->parent;
		if(y!=nullptr && x->data->d < y->data->d){
			cut(x,y);
			cascading_cut(y);
		}
		if(x->data->d < min->data->d)
		{
			min = x;
		}
	}

	void cut(node<T>* x, node<T>* y)
	{
		auto it = std::find(y->child.begin(), y->child.end(), x);
		y->child.erase(it);
		root_list->insert(x);
		x->parent = nullptr;
		x->mark = 0;
	}

	void cascading_cut(node<T>* y){
		auto z = y->parent;
		if(z!=nullptr)
		{
			if(y->mark==0)
				y->mark=1;
			else{
				cut(y,z);
				cascading_cut(z);
			}
		}
	}
};


int main(){
	int n;
	std::cin>>n;
	int e;
	std::cin>>e;
	std::vector<vertex<int>*> gv(n);
	for(int i=0;i<n;i++)
		gv[i] = new vertex<int>(i);
	while(e--){
		int a,b,w;
		std::cin>>a>>b>>w;
		gv[a]->adj[gv[b]] = w;
	}
	FibonacciHeap<vertex<int>*> fh;
	std::vector<node<vertex<int>*>*> nv(n);
	gv[0]->d = 0;
	for(int i=0;i<n;i++)
		nv[i] = fh.fib_insert(gv[i]);
	//for(auto i:nv)
	//	std::cout<<i->data->label<<' ';
	std::vector<vertex<int>*> temp;

	while(!fh.isEmpty())
	{
		node<vertex<int>*> *u = fh.extractMin();
		//std::cout<<u->data->label<<' ';
		temp.push_back(u->data);
		for(auto v:u->data->adj){
			if(v.first->d > u->data->d + v.second)
			{
				fh.decrease_Key(nv[v.first->label], u->data->d + v.second);
				v.first->parent = u->data; 
			}
		}
	}
	for(auto i:gv)
		std::cout<<i->label<<' '<<i->d<<'\n';

}

/*
 *priority_queue<int> pq;//min priority queue
 *insert all nodes into the priority queue // a written heap will do
 *dist = inf for all nodes
 *dist of src from src will be zero
 *push src onto pq
 *while pq is not empty or all nodes are not processed:
 *  get the top of the pq -- consider it u
 *  pop the top
 *  for all vertices adjacent to u -- consider it v:
 *    if current distance from src to v is greater than distance of u
 *    plus weight of u and v edge, update it.
 *    remove v from pq and insert v with the updated min distance
 */
