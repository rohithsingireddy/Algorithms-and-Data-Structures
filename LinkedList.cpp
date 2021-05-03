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


int main(){
	LinkedList<int> *ll, *l2;
	ll = new LinkedList<int>();
	l2 = new LinkedList<int>();
	for(int i=0;i<10;i++){
		ll->insert(i);
		l2->insert(i+10);
	}
	LinkedList<int>* temp = ll->merge(l2);
	//if(temp!=nullptr)ll.remove(temp);
	ll->print();
}
