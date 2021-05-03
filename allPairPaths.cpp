#include<bits/stdc++.h>
const int MAX = 10000000;
typedef std::vector<std::vector<int>> t;


t allPair(t weight_matrix1, t weight_matrix2, t& pred_mat){
	int size = weight_matrix1.size();
	t temp(size),temp2(size);
	for(int i=0;i<size;i++){
		temp[i].resize(size);
		temp2[i].resize(size);
	}
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			temp[i][j]  = MAX;
			temp2[i][j] = -1;
			if(i==j)
				continue;
			for(int k=0;k<size;k++)
				if(temp[i][j] > weight_matrix1[i][k] + weight_matrix2[k][j]){
					temp[i][j] =  weight_matrix1[i][k] + weight_matrix2[k][j];
					if(k!=j)
						temp2[i][j] = k;
					else
						temp2[i][j] = pred_mat[i][j];
				}
			//if(i==j || temp[i][j]==MAX)
			//	pred_mat[i][j] = -1;
		}
	pred_mat = temp2;
	return temp;
}


t slow_allPair(t weight_matrix){
	t temp = weight_matrix;// pred_mat(weight_matrix.size());
	int n = weight_matrix.size();
	t pred_mat(n);
	for(int i=0;i<n;i++)
		pred_mat[i].resize(n);

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			if(temp[i][j] == MAX || temp[i][j] == 0)
				pred_mat[i][j] = -1;
			else
				pred_mat[i][j] = i;
		}
	int i = 1;
	while(i<n-1){
		//std::cout<<i<<' ';
		temp = allPair(temp,weight_matrix, pred_mat);
		i++;
	}
	return pred_mat;
}


t allPair(t weight_matrix){
	int size = weight_matrix.size();
	std::vector<std::vector<int>> temp = weight_matrix;
	//for(int i=0;i<size;i++)
	//	temp[i].resize(size);
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			temp[i][j]  = MAX;
			for(int k=0;k<size;k++)
				temp[i][j] = std::min(temp[i][j], weight_matrix[i][k] + weight_matrix[k][j]);
		}
	return temp;
}


t repeated_allPair(t weight_matrix){
	t temp = weight_matrix;
	int n = weight_matrix.size();
	int i = 1;
	while(i<n-1){
		//cout<<i<<' ';
		temp = allPair(temp);
		i *= 2;
	}
	return temp;
}

int main(){
	
	int n;
	std::cin>>n;
	t v(n);
	for(int i=0;i<n;i++)
		v[i].resize(n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i==j)
				v[i][j] = 0;
			else
				v[i][j] = MAX;
	int e;

	std::cin>>e;
	
	while(e--){
		int a, b, w;
		std::cin>>a>>b>>w;
		v[a][b] = w;
	}
	auto temp = slow_allPair(v);
	std::cout<<'\n';
	for(auto i:temp){
		for(auto j:i)
			std::cout<<j<<' ';
		std::cout<<'\n';
	}
}