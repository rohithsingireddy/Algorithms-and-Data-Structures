#include<bits/stdc++.h>
typedef std::vector<std::vector<double>> typ;

void LU_decomp(typ &mat){
	int n = mat.size();
	for(int k=0;k<n;k++){
		auto temp = mat[k][k];
		for(int i = k+1; i<n;i++)
		{
			mat[i][k] /= temp; 
		}
		for(int i = k+1;i<n;i++)
			for(int j=k+1;j<n;j++)
				mat[i][j] -= mat[i][k]*mat[k][j];
	}
}

bool LUP_decomp(typ &mat, std::vector<int> &p){
	int n = mat.size();
	//int p[n];
	for(int i=0;i<n;i++)
		p[i] = i;
	for(int k=0;k<n;k++)
	{
		double temp = 0;
		int index = 0;
		for(int i = k;i<n;i++)
		{
			if(std::abs(mat[i][k])>temp)
			{
				temp = std::abs(mat[i][k]);
				index = i;
			}
		}
		if(temp==0)
			return false;
		std::swap(p[k],p[index]);
		for(int i=0;i<n;i++)
			std::swap(mat[k][i], mat[index][i]);
		for(int i=k+1;i<n;i++)
		{
			mat[i][k] /= mat[k][k];
			for(int j = k+1;j<n;j++)
				mat[i][j] -= mat[i][k]*mat[k][j];
		}
	}
}

std::vector<double> solv(typ mat, std::vector<int> con)
{
	int n = mat.size();
	std::vector<int> P(n);
	LUP_decomp(mat, P);
	typ L(n),U(n);
	for(int i=0;i<n;i++){
		L[i].resize(n);
		U[i].resize(n);
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			L[i][j] = 0;
			U[i][j] = 0;
			if(i==j)
				L[i][j] = 1;
		}
	for(int k=0;k<n;k++)
	{
		U[k][k] = mat[k][k];
		for(int i=k+1;i<n;i++){
			L[i][k] = mat[i][k];
			U[k][i] = mat[k][i];
		}
	}

	/*for(auto i:L){
		for(auto j:i)
			std::cout<<std::setw(6)<<std::left<<std::setprecision(2)<<j<<' ';
		std::cout<<'\n';
	}*/

	std::vector<double> x(n), y(n);
	for(int i=0;i<n;i++){
		y[i] = con[P[i]];
		for(int j=0;j<i;j++)
		{
			y[i] -= L[i][j]*y[j];
		} 
	}
	for(int i=n-1;i>=0;i--){
		x[i] = y[i];
		for(int j=i+1;j<n;j++)
		{
			x[i] -= U[i][j]*x[j];
		}
		x[i] /= U[i][i]; 
	}
	return x;


}

int main(){
	int r,c;
	std::cin>>r>>c;
	typ mat(r);
	std::vector<int> con(r);
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++){
			double a;
			std::cin>>a;
			mat[i].push_back(a);
		}
	for(int i=0;i<r;i++)
	{
		double a;
		std::cin>>a;
		con[i] = a;
	}
	//solv(mat,con);
/*	LUP_decomp(mat);
	std::cout<<'\n';
	for(auto i:mat){
		for(auto j:i)
			std::cout<<std::setw(6)<<std::left<<std::setprecision(2)<<j<<' ';
		std::cout<<'\n';
	}
*/
	for(auto i:solv(mat, con))
		std::cout<<std::setprecision(2)<<std::setw(8)<<i;
}
