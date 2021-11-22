#include<bits/stdc++.h>
using namespace std;


int rand_partition(int *a, int p, int r){
	int i=p-1;
	int temp = a[r];
	for(int j=p;j<r;j++)
		if(a[j]<=temp)
			swap(a[j],a[++i]);
	swap(a[++i],a[r]);
	return i;
}


int quick_search(int *a, int p, int r, int order){
	if(p==r)
		return a[p];
	int q = rand_partition(a, p, r);
	int count = q-p+1;
	if(order<count)
		return quick_search(a, p ,q-1, order);
	else if(order>count)
		return quick_search(a, q+1, r, order-count);
	else
		return a[q];
}

int iter_quickSearch(int *a, int p, int r, int order){
	int q;
	while(1)
	{
		q = rand_partition(a, p, r);
		int count = q-p+1;
		if(order<count)
			r = q-1;
		else if(order>count){
			p = q+1;
			order -= count;
		}
		else
			break;
	}
	return a[q];
}

int main(){
	int a[]{4,2,5,7,8,9,1,3,6,0};
	cout<<iter_quickSearch(a,0,9,1);
}