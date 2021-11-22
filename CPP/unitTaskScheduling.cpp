#include<bits/stdc++.h>

bool independent(std::vector<int> v, int size){
	int c[size+1];
	for(int i=0;i<size+1;i++)
		c[i] = 0;
	for(int i=0;i<v.size();i++)
		c[v[i]] += 1;
	for(int i=1;i<size+1;i++)
		c[i] += c[i-1];
	for(int i=1;i<size+1;i++){
		std::cout<<c[i]<<' ';
		if(c[i]>i){
			std::cout<<'\n';
			return false;
		}
	}
	std::cout<<'\n';
	return true;
	
}

std::vector<int> scheduling(int *deadlines, int *penalties, int size)
{
	std::vector<int> result, temp1;
	int pen = 0;
	for(int i=0;i<size;i++){
		result.push_back(deadlines[i]);
		temp1.push_back(i+1);
		if(!independent(result, size)){
			result.pop_back();
			temp1.pop_back();
			pen += penalties[i];
		}
	}
	for(auto i:temp1)
		std::cout<<i<<' ';
	std::cout<<'\n'<<pen;
	return result;
}

int main(){
	int d[]{1,1,1};
	int p[]{2,1,5};
	auto temp = scheduling(d,p,3);
}