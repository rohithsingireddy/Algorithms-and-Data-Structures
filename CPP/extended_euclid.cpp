#include<bits/stdc++.h>

std::vector<int> extended_euclid(int a, int b)
{
	//if(a<b)
	//	std::swap(a,b);
	if(b==0)
		return std::vector<int>{a,1,0};
	else{
		std::vector<int>temp2(3), temp = extended_euclid(b, a%b);
		temp2[0] = temp[0];
		temp2[1] = temp[2];
		temp2[2] = temp[1] - (a/b)*temp[2];
		return temp2;
	}
}

void mod_solv(int a, int b, int n){
	std::vector<int> temp = extended_euclid(a,n);
	if(b% temp[0]==0)
	{
		auto x = temp[1]*((b/temp[0])%(n));
		for(int i=0;i<temp[0];i++)
			std::cout<<(x+i*(n/temp[0]))%n<<' ';
	}
}

int main(){
	int a,b,n;
	std::cin>>a>>b>>n;
	for(auto i:extended_euclid(a,n))
		std::cout<<i<<' ';
	std::cout<<'\n';
	mod_solv(a,b,n);
}