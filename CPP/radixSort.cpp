#include<bits/stdc++.h>
using namespace std;
const int D = 3;
const int K=10;

void radixSort(int *a, int size){
	int d=3;
	int t=1;
	while(d--){
		int c[K], b[size+1], temp[size];
		for(int i=0;i<size;i++){
			int tp = a[i]/t;
			temp[i] = tp%10;
		}
		t *= 10;
		for(int i=0;i<K;i++)
			c[i] = 0;
		for(int i=0;i<size;i++)
			c[temp[i]]++;
		for(int i=1;i<K;i++)
			c[i] += c[i-1];

		for(int i=size-1;i>=0;i--)
			b[c[temp[i]]--] = a[i];

		for(int i=0;i<size;i++)
			a[i] = b[i+1];
	}
}

int main(){
	int a[]{234,123,453,123,676,789,454,121,783,333};
	radixSort(a,10);
	for(auto i:a)
		cout<<i<<' ';
}