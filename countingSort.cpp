#include<bits/stdc++.h>
using namespace std;
const int K{10};

void countingSort(int *a, int size){
	int b[size+1],c[K];
	fill(c,c+K,0);
	for(int i=0;i<size;i++)
		c[a[i]]++;
	for(int i=1;i<K;i++)
		c[i] += c[i-1];
	for(int i=0;i<size;i++)
		b[c[a[i]]--] = a[i];
	for(int i=0;i<size;i++)
		a[i] = b[i+1];
}

int main(){
	int a[]{2,5,3,0,2,3,0,3};
	countingSort(a,8);
	for(auto i:a)
		cout<<i<<' ';
}