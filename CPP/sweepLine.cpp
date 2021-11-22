#include<bits/stdc++.h>

template<typename T=int>
struct rbNode{
	rbNode<T> *left=nullptr, *right=nullptr, *parent=nullptr;
	T val=T();
	char color = 'R';
	//rbNode(){}
	rbNode(rbNode<T>* p, rbNode<T> *l, rbNode<T> *r, T v, char c){
		parent = p;
		val = v;
		right = r;
		left = l;
		color = c;
	}
};


template<typename T=int>
struct red_Black_Tree{
	
	rbNode<T> *NIL = new rbNode<T>(nullptr,nullptr,nullptr,T(),'B');
	rbNode<T> *root = NIL;
	void left_rotate(rbNode<T> *cur){
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
	}

	void rb_insert(T val){
		auto temp=root, trail_temp=NIL;
		while(temp!=NIL){
			trail_temp = temp;
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


	rbNode<T>* maxOfTree(rbNode<T>* temp){
		while(temp->right!=NIL)
			temp = temp->right;
		return temp;
	}

	rbNode<T>* successor(T t){
		auto temp = search(t);
		if(temp->right!=NIL)
			return minOfTree(temp->right);
		auto parent = temp->parent;
		while(parent!=NIL && parent->right==temp){
			temp = parent;
			parent = parent->parent;
		}
		return parent;
	}

	rbNode<T>* successor(rbNode<T> *temp){
		//auto temp = search(t);
		if(temp->right!=NIL)
			return minOfTree(temp->right);
		auto parent = temp->parent;
		while(parent!=NIL && parent->right==temp){
			temp = parent;
			parent = parent->parent;
		}
		return parent;
	}

	rbNode<T>* predecessor(T t){
		auto temp = search(t);
		if(temp->right!=NIL)
			return maxOfTree(temp->left);
		auto parent = temp->parent;
		while(parent!=NIL && parent->left==temp){
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
			std::cout<<n->val<<' ';
			inorder(n->right);
		}
	}

};





struct point{
	int x=0,y=0;
	int segment_label = 0;
	point(){x=0;y=0;}
	bool e = 0;//Left or right endpoint
	bool operator<(const point &b) const{
		if(x!=b.x)
			return x < b.x;
		else
			return y < b.y;
	}
	void operator=(point b){
		x = b.x;
		y = b.y;
		e = b.e;
		segment_label = b.segment_label;

	}
};


struct segment
{
	point p1, p2;
	segment(){p1 = point();p2 = point();}	
	segment(point a, point b, int l){
		p1.x = a.x;
		p1.y = a.y;
		p2.x = b.x;
		p2.y = b.y;
		p1.e = 0;
		p2.e = 1;
		p1.segment_label = l;
		p2.segment_label = l;
	}

	bool operator<(const segment& b) const{
		return p1.y < b.p1.y;
	}

	bool operator==(const segment& b) const{
		return (p1.x==b.p1.x) && (p2.x==b.p2.x) && (p1.y==b.p1.y) && (p2.y==b.p2.y);
	}
};

inline int direction(point i, point j, point k)
{
	return (k.x-i.x)*(j.y-i.y) - (k.y-i.y)*(j.x-i.x);
}

bool on_segment(point i, point j, point k){
	int xmin, xmax, ymin, ymax;
	if(i.x <= j.x)
	{
		xmin = i.x;
		xmax = j.x;
	}
	else
	{
		xmin = j.x;
		xmax = i.x;
	}
	if(i.y <= j.y)
	{
		ymin = i.y;
		ymax = j.y;
	}
	else
	{
		ymin = j.y;
		ymax = i.y;
	}
	if(xmin<=k.x && k.x<=xmax && ymin<=k.y && k.y<=ymax)
		return true;
	else
		return false;
} 

bool seg_intersect(segment s1, segment s2){
	//s'i' 'j' - orientation of jth point of other segment wrt. si segment
	int s11 = direction(s1.p1, s1.p2, s2.p1);
	int s12 = direction(s1.p1, s1.p2, s2.p2);
	int s21 = direction(s2.p1, s2.p2, s1.p1);
	int s22 = direction(s2.p1, s2.p2, s1.p2);
	if(s11*s12<0 && s21*s22<0)
		return true;
	else if(s11 == 0 && on_segment(s1.p1,s1.p2,s2.p1))
		return true;
	else if(s12 == 0 && on_segment(s1.p1,s1.p2,s2.p2))
		return true;
	else if(s21 == 0 && on_segment(s2.p1,s2.p2,s1.p2))
		return true;
	else if(s22 == 0 && on_segment(s2.p1,s2.p2,s1.p2))
		return true;
	else
		return false;
}

bool any_seg_instersect(std::vector<segment> s){
	red_Black_Tree<segment> T;
	std::vector<point> s_endp;
	for(auto i:s)
	{
		s_endp.push_back(i.p1);
		s_endp.push_back(i.p2);
	}
	std::sort(s_endp.begin(), s_endp.end());
	//for(auto p:s_endp)
	//	std::cout<<p.e<<' ';
	
	for(auto p:s_endp)
	{
		
		auto temp = s[p.segment_label];
		if(p.e==0)
		{

			T.rb_insert(temp);
			if(T.successor(temp)!=T.NIL && seg_intersect(T.successor(temp)->val,s[p.segment_label]))
				return true;
			if(T.predecessor(temp)!=T.NIL && seg_intersect(T.predecessor(temp)->val,s[p.segment_label]))
				return true;
			
		}
		else
		{
			if(T.successor(temp)!=T.NIL && T.predecessor(temp)!=T.NIL && seg_intersect(T.successor(temp)->val, T.predecessor(temp)->val))
				return true;
			T.rb_delNode(s[p.segment_label]);
		}
		//std::cout<<p.segment_label<<' ';

	}
	return false;

}


int main(){
	int n;
	std::cin>>n;
	std::vector<segment> s(n);
	for(int i=0;i<n;i++){
		int a,b,c,d;
		std::cin>>a>>b>>c>>d;
		point a1,a2;
		a1.x = a;
		a1.y = b;
		a2.x = c;
		a2.y = d;
		a1.segment_label = i;
		a2.segment_label = i;
		a1.e = 0;
		a2.e = 1;
		s[i].p1 = a1;
		s[i].p2 = a2;
	}
	std::cout<<any_seg_instersect(s);
}