#include<bits/stdc++.h>
using namespace std;


struct binNode{
	binNode* parent;
	binNode* left;
	binNode* right;
	int val;
	binNode(binNode* p=nullptr, binNode* l=nullptr, binNode* r=nullptr, int v=0){
		parent = p;
		left = l;
		right = r;
		val = v;
	}
};

struct binTree{
	binNode* root=nullptr;

	void insert(int val){
		auto temp = root, trail_temp = root;
		while(temp){
			trail_temp = temp;
			if(val < temp->val)
				temp = temp->left;
			else
				temp = temp->right;
		}
		binNode* node = new binNode(trail_temp, nullptr, nullptr, val);
		if(trail_temp==nullptr)
			root = node;
		else if(val <= trail_temp->val)
			trail_temp->left = node;
		else
			trail_temp->right = node;
	}


	void transplant(binNode* replaced, binNode* replacement){
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

	void delNode(int val){
		binNode* nodePtr = search(val);
		if(nodePtr==nullptr)
			return;
		if(nodePtr->left==nullptr)
			transplant(nodePtr, nodePtr->right);
		else if(nodePtr->right==nullptr)
			transplant(nodePtr, nodePtr->right);
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

	binNode* successor(binNode* temp){
		if(temp->right!=nullptr)
			return minOfTree(temp->right);
		auto parent = temp->parent;
		while(parent!=nullptr && parent->right==temp){
			temp = parent;
			parent = temp->parent;
		}
		return parent;
		
	}

	binNode* minOfTree(binNode* temp){
		while(temp->left)
			temp = temp->left;
		return temp;
	}

	binNode* search(int val){
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

	void inorderTraversal(binNode* r){
		stack<binNode*> st;
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
					cout<<temp->val<<' ';
					temp = temp->right;
				}
			}
		}
	}

};


int main(){
	vector<int> a{15,6,18,3,7,17,20,2,4,13,9};
	binTree bt;
	for(auto i:a)
		bt.insert(i);
	bt.delNode(6);
	//bt.delNode(3);
	bt.inorderTraversal(bt.root);
	cout<<'\n';
	//cout<<bt.predecessor(bt.search(6))->val;
	for(int i=0;i<10;i++)
		bt.delNode(i);
	bt.inorderTraversal(bt.root);
}