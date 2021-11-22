#include<bits/stdc++.h>

long hashing(char s){
	return ((int)(s)*10>>1) * ((int)(s)*10<<1);
}

int main(){
	std::string s;
	std::cin>>s;
	std::string p;
	std::cin>>p;
	long p_hash=0, t_hash = 0;
	for(auto i:p)
		p_hash += hashing(i);
	//std::cout<<p_hash;
	for(int i=0;i<p.size();i++)
		t_hash += hashing(s[i]);
	int k = 0;
	int t = p.size();
	while(1)
	{
		if(t_hash == p_hash)
		{
			std::cout<<"Pattern Found\n";
			return 0;
		}
		if(t>=s.size()) break;
		t_hash -= hashing(s[k++]);
		t_hash += hashing(s[t++]); 
	}
	std::cout<<"Pattern Not Found\n";
}