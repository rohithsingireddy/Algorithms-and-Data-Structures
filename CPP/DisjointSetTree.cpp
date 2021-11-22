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
	 		//return this;
	 	}
	 }
};

template<typename T=int>
struct Set_node{
	int rank = 0;
	T data;
	LinkedList<T> *l=new LinkedList<T>();
	Set_node* parent;
	Set_node(T d):rank{0},data{d},parent{this}{
		parent->l = new LinkedList<T>();
		parent->l->insert(d);
	}


};




template<typename T=int>
Set_node<T>* find_set(Set_node<T>* x){
	if(x != x->parent)
		x->parent = find_set(x->parent);
	return x->parent;
}

template<typename T=int>
void union_set(Set_node<T> *x, Set_node<T> *y){
	auto x_p = find_set(x);
	auto y_p = find_set(y);
	
	if(x_p->rank > y_p->rank){
		x_p->parent = y_p;
		y_p->l->merge(x_p->l);
	}
	else{
		y_p->parent = x_p;
		x_p->l->merge(y_p->l);
		if(x_p->rank == y_p->rank)
			x_p->rank++;
	}
}

template<typename T=int>
void print(Set_node<T>* s){
	auto temp = find_set(s);
	temp->l->print();
}

int main(){
	Set_node<int>* s[17];
	for(int i=1;i<17;i++)
		s[i] = new Set_node<int>(i);
	for(int i=1;i<17;i += 2)
		union_set(s[i],s[i+1]);
	for(int i=1;i<17;i += 4)
		union_set(s[i], s[i+2]);
	union_set(s[1],s[5]);
	union_set(s[11],s[13]);
	union_set(s[1],s[10]);
	std::cout<<find_set(s[2])->data<<' '<<find_set(s[9])->data<<'\n';
	print(s[2]);
}