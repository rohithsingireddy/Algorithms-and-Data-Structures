#include<bits/stdc++.h>
using namespace std;

int main(){
	int n{4};
	int bit_num1[n]{1,0,1,1};
	int bit_num2[n]{1,1,0,1};
	int carry=0;
	int result[n+1];
	for(int i=n-1;i>=0;i--){
		int temp = carry+bit_num1[i] + bit_num2[i];
		if(temp==2){
			carry=1;
			temp=0;
		}
		if(temp==3){
			carry = 1;
			temp = 1;  
		}
		result[i+1] = temp;
	}
	result[0] = carry;
	for(auto i:result)
		cout<<i;
}