#include<bits/stdc++.h>
typedef long long u_64;
int order = 64;

struct vEB_n{
	std::unordered_map<u_64, vEB_n*> cluster;
	u_64 u;
	vEB_n *summary;
	u_64 sqrt_u_floor, sqrt_u_ceil;
	u_64 min, max;
	vEB_n(int n){
		u = n;
		double temp = std::log2(n)/2;
		sqrt_u_floor = std::pow(2, std::floor(temp));
		sqrt_u_ceil = std::pow(2, std::ceil(temp));
		max = -1;
		min = -1;
		summary = nullptr;
	}
	inline u_64 high(u_64 x){return x/sqrt_u_floor;}
	inline u_64 low(u_64 x){return x%sqrt_u_floor;}
	inline u_64 index(u_64 h, u_64 l){return h*sqrt_u_floor + l;} 
};

struct vEB_tree{
	vEB_n *root=new vEB_n(order);

	inline vEB_n* create_new_node(u_64 u){
		return new vEB_n(u);
	}

	inline void empty_tree_insert(vEB_n* cur, u_64 x){
		cur->min = x;
		cur->max = x;
	}
	void insert(vEB_n *cur, u_64 x){
		if(cur->min == -1){
			empty_tree_insert(cur,x);
		}
		else{
			if(x < cur->min)
				std::swap(x, cur->min);
			if(cur->u > 2){
				if(cur->cluster.find(cur->high(x))==cur->cluster.end()){
					cur->summary = create_new_node(cur->sqrt_u_ceil);
					insert(cur->summary, cur->high(x));
					cur->cluster[cur->high(x)] = create_new_node(cur->sqrt_u_floor);
					empty_tree_insert(cur->cluster[cur->high(x)], x);
				}
				else{
					insert(cur->cluster[cur->high(x)], cur->low(x));
				}
			}
			if(x > cur->max)
				cur->max = x;
		}
	}


	bool isMember(vEB_n *cur, u_64 x){
		if(x==cur->min || x==cur->max)
			return true;
		else if(cur->u==2)
			return false;
		else{
			if(cur->cluster.find(cur->high(x)) == cur->cluster.end())
				return false;
			return isMember(cur->cluster[cur->high(x)], cur->low(x));
		}
	}



	inline u_64 minimum(vEB_n* cur){return cur->min;}
	inline u_64 maximum(vEB_n* cur){return cur->max;}




};

int main(){
	vEB_tree veb;
	//veb.build();
	std::vector<u_64> v{2,3,5,9,12,11,1,24,30};
	for(auto i:v)
		veb.insert(veb.root, i);
	//veb.remove(veb.root, 30);
	//std::cout<<veb.successor(veb.root, 24);
	return 0;

}