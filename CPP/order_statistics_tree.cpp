#include<bits/stdc++.h>
using namespace std;

template<typename T=int>
struct rbNode{
	rbNode *left=nullptr, *right=nullptr, *parent=nullptr;
	T val;
	char color = 'R';
	int size = 0;
	rbNode(rbNode* p, rbNode *l, rbNode *r, T v, char c){
		parent = p;
		val = v;
		right = r;
		left = l;
		color = c;
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
		r->size = cur->size;
		cur->size = cur->left->size + cur->right->size + 1;
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
		l->size = cur->size;
		cur->size = l->left->size + l->right->size + 1;
	}

	void rb_insert(T val){
		auto temp=root, trail_temp=NIL;
		while(temp!=NIL){
			trail_temp = temp;
			temp->size += 1;
			if(val < temp->val)
				temp = temp->left;
			else
				temp = temp->right;
		}
		rbNode<T>* node = new rbNode<T>(trail_temp, NIL, NIL, val, 'R');
		if(trail_temp==NIL)
			root = node;
		else if(val < trail_temp->val)
			trail_temp->left = node;
		else
			trail_temp->right = node;
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

	rbNode<T>* search(T val){
		auto temp = root;
		while(temp!=NIL){
			if(val == temp->val)
				return temp;
			else if(val < temp->val)
				temp = temp->left;
			else
				temp = temp->right;
		}
		return NIL;
	}

	rbNode<T>* minOfTree(rbNode<T>* temp){
		while(temp->left!=NIL)
			temp = temp->left;
		return temp;
	}

	rbNode<T>* successor(rbNode<T>* temp){
		if(temp->right!=NIL)
			return minOfTree(temp->right);
		auto parent = temp->parent;
		while(parent!=NIL && parent->right==temp){
			temp = parent;
			parent = parent->parent;
		}
		return parent;
	}

	void transplant(rbNode<T>* replaced, rbNode<T>* replacement){
		if(replaced->parent==NIL)
			root = replacement;
		else if(replaced->parent->left==replaced)
			replaced->parent->left = replacement;
		else
			replaced->parent->right = replacement;
		replacement->parent = replaced->parent;	
	}

	void rb_delNode(T val){
		auto delNode = search(val);
		if(delNode==NIL)return;
		decrement(delNode->parent);
		auto y = delNode;
		rbNode<T> *x=NIL; //violating node
		char y_orgColor = delNode->color;
		if(delNode->left==NIL){
			x = delNode->right;
			transplant(delNode, delNode->right);
		}
		else if(delNode->right==NIL){
			x = delNode->left;
			transplant(delNode,delNode->left);
		}
		else{
			y = successor(delNode);
			y_orgColor = y->color;
			x = y->right;
			if(y->parent == delNode)
				x->parent = y;
			else{
				transplant(y,y->right);
				y->right = delNode->right;
				y->right->parent = y;
			}
			transplant(delNode, y);
			y->left = delNode->left;
			y->left->parent = y;
			y->color = delNode->color;
		}
		if(y_orgColor=='B')
			rb_delFixUp(x);
	}

	void rb_delFixUp(rbNode<T>* cur){
		while(cur!=root && cur->color=='B'){
			if(cur == cur->parent->left)
			{
				auto right_sibling = cur->parent->right;
				if(right_sibling->color=='R')
				{
					right_sibling->color = 'B';
					cur->parent->color = 'R';
					left_rotate(cur->parent);
					right_sibling = cur->parent->right;
				}

				if(right_sibling->left->color=='B' && right_sibling->right->color=='B')
				{
					right_sibling->color = 'R';
					cur = cur->parent;
				}
				else{
					if(right_sibling->right->color=='B')
					{
						right_sibling->color = 'R';
						right_sibling->left->color = 'B';
						right_rotate(right_sibling);
					}
					right_sibling->color = cur->parent->color;
					cur->parent->color = 'B';
					right_sibling->right->color = 'B';
					left_rotate(cur->parent);
					cur = root;
				}
			}
			else
			{
				auto left_sibling = cur->parent->left;
				if(left_sibling->color=='R')
				{
					left_sibling->color = 'B';
					cur->parent->color = 'R';
					right_rotate(cur->parent);
					left_sibling = cur->parent->left;
				}

				if(left_sibling->left->color=='B' && left_sibling->right->color=='B')
				{
					left_sibling->color = 'R';
					cur = cur->parent;
				}
				else{
					if(left_sibling->left->color=='B')
					{
						left_sibling->color = 'R';
						left_sibling->left->color = 'B';
						left_rotate(left_sibling);
					}
					left_sibling->color = cur->parent->color;
					cur->parent->color = 'B';
					left_sibling->left->color = 'B';
					right_rotate(cur->parent);
					cur = root;
				}	
			}
		}
		cur->color = 'B';
	}

	void inorder(rbNode<T>* n){
		if(n!=NIL){
			inorder(n->left);
			//if(n->val!=0)
			cout<<n->val<<' ';
			inorder(n->right);
		}
	}

	T OS_select(rbNode<T>* cur,int i){	//Ordered Statistics
		int r = cur->left->size + 1;
		if(r==i)
			return cur->val;
		else if(i < r)
			return OS_select(cur->left, i);
		else 
			return OS_select(cur->right, i-r);
	}

	int rank_of_element(T val){
		auto cur = search(val);
		int rank = cur->left->size+1;
		while(cur!=root){
			if(cur==cur->parent->right)
				rank += cur->parent->left->size + 1;
			cur = cur->parent;
		}
		return rank;
	}

	void decrement(rbNode<T>* cur){
		while(cur!=NIL){
			cur->size -= 1;
			cur = cur->parent;
		}
	}

};


int main(){
	red_Black_Tree<int> rb;
	for(int i=0;i<10;i++)
		rb.rb_insert(i);
	rb.inorder(rb.root);
	cout<<'\n'<<rb.rank_of_element(9);
	rb.rb_delNode(2);
	cout<<'\n'<<rb.rank_of_element(9);
}