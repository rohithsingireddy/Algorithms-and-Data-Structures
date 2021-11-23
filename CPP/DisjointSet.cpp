#include<vector>
//Linked Set Representation
/*
template<typename T=int>
struct set_node
{
	set_node *parent = nullptr;
	set_node *next = nullptr;
	set_node *tail = nullptr;
	//set_node *head = nullptr
	T data = T();
	int no_of_elements;
	set_node(T d){
		parent = this;
		next = nullptr;
		tail = this;
		//head = this;
		data = d;
		no_of_elements = 1;

	}
};

template<typename T=int>
void union_sets(set_node<T> *temp1, set_node<T>* temp2){
	auto a=temp1, b=temp2;
	if(a->parent->no_of_elements < b->parent->no_of_elements)
		std::swap(a,b);
	a->parent->tail->next = b->parent;
	auto temp = b->parent;
	a->parent->tail = b->parent->tail;
	a->parent->no_of_elements += b->parent->no_of_elements;
	while(temp){
		temp->parent = a->parent;
		temp = temp->next;
	}
	
}

template<typename T=int>
set_node<T>* find_set(set_node<T> *a){
	return a->parent;
}
*/
const int maxn = 5e5 + 500;
std::vector<int> Parent(maxn), Rank(maxn), Size(maxn);

// intialize user groups with just 1 element i.e itself
void init(){
	for(int i = 0; i < maxn; i++){
		Parent[i] = i;
		Rank[i] = 0;
		Size[i] = 1;
	}
}

// This is used for finding the head or representative of a group which
// has user v
int find_root(int v){
	if(v == Parent[v])return v;
	return Parent[v] = find_root(Parent[v]);
}

// unite two groups which has user u and user v 
bool unite(int u, int v){
	u = find_root(u);
	v = find_root(v);
	if(u != v){
		if(Rank[u] < Rank[v])
			std::swap(u, v);
		Parent[v] = u;
		if(Rank[u] == Rank[v])Rank[u]++;
		Size[u] += Size[v];
		return true;
	}
	return false;
}
/*
int main(){
	set_node<int> *s[17];
	for(int i=1;i<=16;i++){
		s[i] = new set_node<int>(i);
		//std::cout<<s[i]->data<<' ';
	}
	for(int i=1;i<16; i += 2){
		union_sets(s[i],s[i+1]);
	}
	for(int i=1;i<14; i += 4){
		union_sets(s[i],s[i+2]);
	}
	union_sets(s[1],s[5]);
	union_sets(s[11],s[13]);
	union_sets(s[1],s[10]);

	std::cout<<find_set(s[2])->data<<' '<<find_set(s[9])->data;
}
*/
