#include<bits/stdc++.h>
int order = 16;

struct proto_eVB_n{
	int u, k;
	proto_eVB_n *summary;
	std::vector<proto_eVB_n*> cluster;
	bool a[2];
	int n = 0;
	proto_eVB_n(int s){
		u = s;
		k = (int)std::sqrt(s);
		cluster.resize(k);

	}


	inline int index(int h, int l){return h*k+l;}
	inline int high(int x){return (x/k);}
	inline int low(int x){return (x%k);} 
};

struct proto_eVB{
	proto_eVB_n *root = nullptr;
	
	void build(proto_eVB_n *cur=nullptr, int u=order){
		
		int k = (int)std::sqrt(u);
		if(root==nullptr){
			proto_eVB_n *temp = new proto_eVB_n(u);
			root = temp;
			cur = root;
		}
		if(cur->u==2){
			cur->summary = nullptr;
			cur->a[0]  = 0;
			cur->a[1] = 0;
			return;
		}
		proto_eVB_n *temp = new proto_eVB_n(cur->k);
		cur->summary = temp;
		build(cur->summary, cur->k);
		for(int i=0;i<cur->k;i++){
			cur->cluster[i] = new proto_eVB_n(cur->k);
			build(cur->cluster[i], cur->k);
		}

	}

	void insert(proto_eVB_n *cur, int x){
		if(cur->u==2){
			cur->a[x] = 1;
			cur->n++;
		}
		else{
			insert(cur->cluster[cur->high(x)], cur->low(x));
			insert(cur->summary, cur->high(x));
			cur->n++;
		}
	}

	void remove(proto_eVB_n *cur, int x){
		if(cur->u==2){
			cur->a[x] = 0;
			cur->n--;
			if(cur->n-1 > 0)
				cur->a[x] = 1;
		}
		else{
			remove(cur->cluster[cur->high(x)], cur->low(x));
			remove(cur->summary, cur->high(x));
			cur->n--;
		}
	}

	bool isMember(proto_eVB_n *cur, int v){
		if(cur->u==2)
			return cur->a[v];
		else{
			isMember(cur->cluster[cur->high(v)], cur->low(v));
		}
	} 

	int minimum(proto_eVB_n *cur){
		if(cur->u==2){
			if(cur->a[0]==1)
				return 0;
			else if(cur->a[1]==1)
				return 1;
			else
				return -1;
		}
		else{
			int min_cluster = minimum(cur->summary);
			if(min_cluster==-1)
				return -1;
			else{
				int offset = minimum(cur->cluster[min_cluster]);
				return cur->index(min_cluster, offset);
			}
		}
	}

	int maximum(proto_eVB_n *cur){
		if(cur->u==2){
			if(cur->a[1]==1)
				return 1;
			else if(cur->a[0]==1)
				return 0;
			else
				return -1;
		}
		else{
			int max_cluster = maximum(cur->summary);
			if(max_cluster==-1)
				return -1;
			else{
				int offset = maximum(cur->cluster[max_cluster]);
				return cur->index(max_cluster, offset);
			}
		}
	}

	int successor(proto_eVB_n *cur, int x){
		if(cur->u == 2){
			if(x==0 && cur->a[1]==1)
				return 1;
			else
				return -1;
		}
		else{
			int offset = successor(cur->cluster[cur->high(x)], cur->low(x));
			if(offset!=-1)
				return cur->index(cur->high(x), offset);
			else{
				int succ_cluster = successor(cur->summary, cur->high(x));
				if(succ_cluster==-1)
					return -1;
				else{
					int offset = minimum(cur->cluster[succ_cluster]);
					return cur->index(succ_cluster, offset);
				}
			}
		}
	}

	int predecessor(proto_eVB_n *cur, int x){
		if(cur->u == 2){
			if(x==1 && cur->a[0]==1)
				return 0;
			else
				return -1;
		}
		else{
			int offset = predecessor(cur->cluster[cur->high(x)], cur->low(x));
			if(offset!=-1)
				return cur->index(cur->high(x), offset);
			else{
				int pred_cluster = predecessor(cur->summary, cur->high(x));
				if(pred_cluster==-1)
					return -1;
				else{
					int offset = maximum(cur->cluster[pred_cluster]);
					return cur->index(pred_cluster, offset);
				}
			}
		}
	}

};

int main(){
	proto_eVB eVB;
	std::vector<int> v{2,4,5,14,15,3,7};
	eVB.build();
	for(auto i:v)
		eVB.insert(eVB.root, i);
	std::cout<<eVB.isMember(eVB.root,5)<<'\n';
	eVB.remove(eVB.root, 15);
	std::cout<<eVB.isMember(eVB.root,15)<<'\n';

}