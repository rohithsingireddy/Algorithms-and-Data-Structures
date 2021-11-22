#include<bits/stdc++.h>
double exp_cost[100][100];
double wei_prob[100][100];
int root[100][100];
const double MAX{10e5};

double weights(double *p, double *q, int i, int j){
	if(wei_prob[i][j])
		return wei_prob[i][j];
	if(j == i-1)
		return q[j];
	wei_prob[i][j] = weights(p, q, i, j-1) + p[j] + q[j];
	return wei_prob[i][j];
}

double OST_cost(double *p, double *q, int i, int j){
	if(j == i-1)
		return q[j];
	if(exp_cost[i][j]!=MAX)
		return exp_cost[i][j];
	for(int r = i; r<=j; r++){
		auto temp = OST_cost(p, q, i, r-1) + OST_cost(p, q, r+1, j) + weights(p, q, i, j);
		if(temp<exp_cost[i][j]){
			exp_cost[i][j] = temp;
			root[i][j] = r;
		}
	}

	return exp_cost[i][j];

}

void print(int i, int j, int r){
	if(i-1 == j){
		if(j<r)
			std::cout<<std::to_string(j) + " is the dummy left child of key "+ std::to_string(r)<<'\n';
		//return;
		else if(i>r)
			std::cout<<std::to_string(j) + " is the dummy right child of key "+ std::to_string(r)<<'\n';
		return;
	}
	if(r==0)
		std::cout<<std::to_string(root[i][j]) + " is the root\n";
	else if(j<r)
		std::cout<<std::to_string(root[i][j]) + " is the key left child of "+ std::to_string(r)<<'\n';
	else if(i>r)
		std::cout<<std::to_string(root[i][j]) + " is the key right child of "+ std::to_string(r)<<'\n';
	print(i, root[i][j]-1, root[i][j]);
	print(root[i][j]+1, j, root[i][j]);

}


int main(){

	double p[]{0.00, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14};
	double q[]{0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
	for(int i=0;i<100;i++){
		std::fill(exp_cost[i], exp_cost[i]+100, MAX);
		std::fill(wei_prob[i], wei_prob[i]+100, 0);
	}
	std::cout<<OST_cost(p, q, 1, 7)<<'\n';
	print(1, 5, 0);
}