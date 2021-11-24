#include <iostream>
#include <stack>

template<typename T = int>
struct binNode{
	binNode* parent;
	binNode* left;
	binNode* right;
	T val;
	binNode(binNode* p=nullptr, binNode* l=nullptr, binNode* r=nullptr, T v=0){
		parent = p;
		left = l;
		right = r;
		val = v;
	}
};


template<typename T = int>
struct BinTree{
	binNode<T>* root=nullptr;

	/*
	 * Takes a value and inserts into the binary tree
	 * Returns null
	 */
	void insert(T val){
		auto temp = root, trail_temp = root;
		while(temp){
			trail_temp = temp;
			if(val < temp->val)
				temp = temp->left;
			else
				temp = temp->right;
		}
		binNode<T>* node = new binNode<T>(trail_temp, nullptr, nullptr, val);
		if(trail_temp==nullptr)
			root = node;
		else if(val <= trail_temp->val)
			trail_temp->left = node;
		else
			trail_temp->right = node;
	}

	/*
	 * Takes two subtrees and replaces one with other sub tree
	 * Returns null
	 */ 
	void transplant(binNode<T>* replaced, binNode<T>* replacement){
		auto parent = replaced->parent;
		if(parent==nullptr){
			root = replacement; 
		}
		else if(parent->left==replaced)
			parent->left = replacement;
		else
			parent->right = replacement;
		if(replacement!=nullptr)
			replacement->parent = parent;
	}


	/* 
	 * Removes the given node from the sub-tree and readjusts the tree
	 * Returns null
	 */ 
	void delNode(T val){
		binNode<T>* nodePtr = search(val);
		if(nodePtr==nullptr)
			return;
		if(nodePtr->left==nullptr)
			transplant(nodePtr, nodePtr->right);
		else if(nodePtr->right==nullptr)
			transplant(nodePtr, nodePtr->left);
		else{
			auto suc = successor(nodePtr);
			if(suc->parent!=nodePtr){
				transplant(suc, suc->right);
				suc->right = nodePtr->right;
				suc->right->parent = suc;
			}
			transplant(nodePtr, suc);
			suc->left = nodePtr->left;
			suc->left->parent = suc;
		}
	}

	/*
	 * Takes a given node and gives the smallest node which is greater than it
	 * Returns a binNode<T> if it exists else null
	 */ 
	binNode<T>* successor(binNode<T>* temp){
		if(temp->right!=nullptr)
			return minOfTree(temp->right);
		auto parent = temp->parent;
		while(parent!=nullptr && parent->right==temp){
			temp = parent;
			parent = temp->parent;
		}
		return parent;
		
	}

	/* 
	 * Finds the leftmost ( also know as lowest in value ) node of the subtree
	 * Returns a binNode<T>
	 */ 
	binNode<T>* minOfTree(binNode<T>* temp){
		while(temp->left)
			temp = temp->left;
		return temp;
	}


	/*
	 * Searches for a node with the given value
	 * Returns a binNode<T> if node exists else null
	 */
	binNode<T>* search(T val){
		auto temp = root;
		while(temp){
			if(temp->val==val)
				return temp;
			else if(val < temp->val)
				temp = temp->left;
			else temp = temp->right; 
		}
		return temp;
	}

	/* 
	 * Traverses the tree in order
	 * Returns null
	 */
	void inorderTraversal(binNode<T>* r){
		std::stack<binNode<T>*> st;
		auto temp = r;
		bool done =1;
		while(done){
			if(temp!=nullptr){
				st.push(temp);
				temp=temp->left;
			}
			else{
				if(st.empty())
					done=0;
				else{
					temp = st.top();
					st.pop();
					std::cout<<temp->val<<' ';
					temp = temp->right;
				}
			}
		}
	}

};
