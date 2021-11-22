#include<bits/stdc++.h>
using namespace std;

struct interval{
	int low=-1;
	int high=-1;
	interval(){low=-1;high=-1;}
	interval(int a, int b){low=a;high=b;}
};

template<typename T=int>
struct rbNode{
	rbNode *left=nullptr, *right=nullptr, *parent=nullptr;
	//int val = 0;
	char color = 'R';
	T inter;
	int max_end=0;
	rbNode(rbNode* p, rbNode *l, rbNode *r, T v, char c){
		parent = p;
		inter = v;
		right = r;
		left = l;
		color = c;
		//val = v.low;
		max_end = v.high;
	}

};


template<typename T=int>
struct red_Black_Tree{
	
	rbNode<T>* NIL = new rbNode<T>(nullptr,nullptr,nullptr,T(),'B');
	rbNode<T> *root = NIL;
	
	void left_rotate(rbNode<T>*cur){
		auto r = cur->right;
		if(r==NIL) return;
		cur->right = r->left;
		if(r->left!=NIL)
			cur->right->parent = cur;
		r->parent = cur->parent;
		if(cur->parent==NIL)
			root = r;
		else if(cur->parent->left == cur)
			cur->parent->left = r;
		else
			cur->parent->right = r;
		r->left = cur;
		cur->parent = r;
		r->max_end = cur->max_end;
		cur->max_end = max_high(cur);
	}

	void right_rotate(rbNode<T>* cur){
		auto l = cur->left;
		if(l==NIL) return;
		cur->left = l->right;
		if(l->right!=NIL)
			cur->left->parent = l;
		l->parent = cur->parent;
		if(cur->parent==NIL)
			root = l;
		else if(cur->parent->left == cur)
			cur->parent->left = l;
		else
			cur->parent->right = l;
		l->right = cur;
		cur->parent = l;
		l->max_end = cur->max_end;
		cur->max_end = max_high(cur);
	}

	int max_high(rbNode<T>* temp){
		int m;
		m = temp->max_end;
		if(temp->right!=NIL)
			m = max(m, temp->right->max_end);
		if(temp->left!=NIL)
			m = max(m, temp->left->max_end);
		return m;
	}

	void rb_insert(T val){
		auto temp=root, trail_temp=NIL;
		while(temp!=NIL){
			trail_temp = temp;
			//temp->size += 1;
			//temp->max_end = max_high(temp);
			if(val.low < temp->inter.low)
				temp = temp->left;
			else
				temp = temp->right;
		}
		rbNode<T>* node = new rbNode<T>(trail_temp, NIL, NIL, val, 'R');
		if(trail_temp==NIL)
			root = node;
		else if(val.low < trail_temp->inter.low)
			trail_temp->left = node;
		else
			trail_temp->right = node;
		if(trail_temp!=NIL)
			trail_temp->max_end = max_high(trail_temp);
		rb_insert_fixup(node);
	}

	void rb_insert_fixup(rbNode<T>* cur){
		while(cur->parent->color=='R')
		{
			if(cur->parent==cur->parent->parent->right)
			{
				auto uncle = cur->parent->parent->left;
				if(uncle->color=='R')
				{
					uncle->color = 'B';
					cur->parent->color = 'B';
					cur->parent->parent->color = 'R';
					cur = cur->parent->parent;
				}
				else
				{
					if(cur==cur->parent->left)
					{
						cur = cur->parent;
						right_rotate(cur);
					}
					cur->parent->color = 'B';
					cur->parent->parent->color = 'R';
					left_rotate(cur->parent->parent);
				}
			}
			else
			{
				auto uncle = cur->parent->parent->right;
				if(uncle->color=='R')
				{
					uncle->color = 'B';
					cur->parent->color = 'B';
					cur->parent->parent->color = 'R';
					cur = cur->parent->parent;
				}
				else
				{
					if(cur==cur->parent->right)
					{
						cur = cur->parent;
						left_rotate(cur);
					}
					cur->parent->color = 'B';
					cur->parent->parent->color = 'R';
					right_rotate(cur->parent->parent);
				}	
			}
		}
		root->color = 'B';
	}

	bool not_overlap(T a, T b){
		if(a.high<=b.low || b.high<a.low)
			return true;
		return false;
	}
	rbNode<T>* search(T inter){
		auto temp = root;
		while(temp!=NIL && not_overlap(temp->inter, inter)){
			if(temp->left!=NIL && temp->left->max_end>=inter.low)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return temp;
	}

	void inorder(rbNode<T>* n){
		if(n!=NIL){
			inorder(n->left);
			//if(n->val!=0)
			cout<<'('<<n->inter.low<<' '<<n->inter.high<<')'<<' '<<n->max_end<<'\n';
			inorder(n->right);
		}
	}

};

int main(){
	//cout<<int();
	//interval a(0,3);
//	a.low = 0;
//  a.high = 3;
	red_Black_Tree<interval> rb;
	for(int i=0;i<10;i++){
		int a,b;
		cin>>a>>b;
		rb.rb_insert(interval(a,b));
	}
	rb.inorder(rb.root);
	cout<<rb.search(interval(11,14))->inter.high;
}
