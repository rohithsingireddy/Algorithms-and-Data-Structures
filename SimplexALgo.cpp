#include<bits/stdc++.h>
typedef std::vector<double> typ_db;
typedef std::vector<int> typ_int;
const double inf = 10e9;
//N - nonbasic variables
//B - basic variables
//A - negatives of coefficient's matrix
//b - constraint values on RHS of slack form
//c - coefficients of variables in objective function
//v - some constant in objective function
//e - entering variable
//l - exiting variable
//Next time

int main(){
	int m,n;
	std::cin>>m>>n;
	std::vector<typ_db> mat(m);
	std::vector<double> c(n), b(n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			double a;
			std::cin>>a;
			mat[i].push_back(a);
		}
	for(int i=0;i<n;i++)
	{
		double a;
		std::cin>>a;
		b[i] = a;
	}
	for(int i=0;i<n;i++)
	{
		double a;
		std::cin>>a;
		c[i] = a;
	}
	auto temp = simplex(mat,b,c);
	for(auto i:temp)
		std::cout<<i<<' ';
}