#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct segment_node{
	int left_index,right_index;
	T sum;
	segment_node<T>* left_child, *right_child;
	segment_node():left_child{nullptr}, right_child{nullptr}, sum{0}{}
};

template<typename T>
void build(vector<T> a, segment_node* cur, int left, int right)
{
	if(left==right)
		cur->sum = a[left];
	else
	{
		int mid = (left+right)/2;
		cur->left_child = new segment_node();
		cur->right_child = new segment_node();
		build(a, cur->left_child, left, mid);
		build(a, cur->right_child, mid+1, right);
		cur->sum = max(cur->left_child->sum , cur->right_child->sum);
	}
	cur->left_index = left;
	cur->right_index = right;
}

template<typename T>
T sum(segment_node<T>* cur, int left, int right)
{
	if(left>right)
		return 0;
	if(cur->left_index==left && cur->right_index==right)
		return cur->sum;
	if(cur->left_child==nullptr && cur->right_child==nullptr)
		return 0;
	int l = cur->left_index;
	int r = cur->right_index;
	int mid = (l+r)/2;
	return max(sum(cur->left_child, left, min(right,mid)) , sum(cur->right_child, max(left, mid+1), right));

}

void update(segment_node* cur, int pos, int val)
{
	if(cur->left_index == cur->right_index && cur->left_index==pos)
		cur->sum = val;
	else{
		int l  = cur->left_index;
		int r = cur->right_index;
		int mid = (l+r)/2;
		if(pos<=mid)
			update(cur->left_child, pos, val);
		else
			update(cur->right_child, pos, val);
		cur->sum = cur->left_child->sum + cur->right_child->sum;
	}
}

int main()
{
	vector<int> a{1,2,3,4,5,6};
	segment_node* root = new segment_node();
	build(a,root,0,a.size()-1);
	//update(root, 3, 3);
	cout<<sum(root,0,5);
}