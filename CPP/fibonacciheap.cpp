#include<bits/stdc++.h>
const int MAX = 1000000;

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







template<typename T=int>
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

template<typename T=int>
struct FibHeap{
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
			if(val < min->data){
				min = temp;
			}
		}
		no_of_nodes++;
		return temp;
	}

	FibHeap<T>* fib_heap_union(FibHeap<T> *h1, FibHeap<T> *h2){
		FibHeap<T> *temp = new FibHeap<T>();
		temp->min = h1->min;
		temp->root_list = temp->root_list->merge(h2->root_list);  
		if(h1->min==nullptr || (h2->min!=nullptr && h2->min->data < h1->min->data))
			temp->min = h2->min;
		temp->no_of_nodes = h1->no_of_nodes + h2->no_of_nodes;
		return temp;
	}

	node<T>* fib_heap_extract_min(){
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
			
		}
		no_of_nodes--;
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
				if(x->data > y->data)
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
					if(a[i]->data < min->data)
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

	void fib_heap_decrease_data(node<T> *x, int k){
		if(k>x->data)
			throw "ERROR\n";
		x->data = k;
		auto y = x->parent;
		if(y!=nullptr && x->data < y->data){
			cut(x,y);
			cascading_cut(y);
		}
		if(x->data < min->data)
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

	void fib_delete_node(node<T>* x){
		fib_heap_decrease_data(x, -MAX);
		fib_heap_extract_min();
	}


};



int main(){
	try{
	FibHeap<int> fh;
	node<int>* a[11];
	for(int i=0;i<=10;i++)
		a[i] = fh.fib_insert(i);
	//fh.root_list->print();
	//fh.fib_insert(2);
	//std::cout<<'d';
	//std::cout<<fh.fib_heap_extract_min()->data;
	
	//fh.fib_heap_decrease_data(a[2], -1);
	//fh.fib_heap_decrease_data(a[3], -6);
	//fh.fib_delete_node(a[3]);
	for(auto i:a)
		std::cout<<'\n'<<fh.fib_heap_extract_min()->data<<'\n';
	}
	catch(std::exception &e){std::cout<<"Error";}
	
	return 0;

}