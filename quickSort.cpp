#include<bits/stdc++.h>
using namespace std;

int hoarse_partition(int *a, int p, int q)
{
	int i = p-1;
	int j = q+1;
	int temp = a[p];
	while(true){
		do{
			i++;
		}while(a[i]<temp);
		do{
			j--;
		}while(a[j]>temp);
		if(i<j)
			swap(a[i],a[j]);
		else 
			return j;
	}
}

int partition(int *a, int p, int q){
	int pivot = a[q];
	int i = p-1;
	for(int j=p;j<q;j++){
		if(a[j]<=pivot)
			swap(a[j], a[++i]);
	}
	swap(a[q],a[++i]);
	return i;
}

int randomized_partition(int *a, int p, int q)
{
	int r = p + (rand()%(q-p+1));
	swap(a[q],a[r]);
	return partition(a,p,q);
}

void quickSort(int *a, int p, int q){
	if(p<q){
		int m = hoarse_partition(a,p,q);
		quickSort(a,p,m-1);
		quickSort(a,m+1,q);
	}
}

int main(){

	int a[] {2,32,424,1235,46312,53251,12,213,34,67};
	quickSort(a,0,9);
	for(auto i:a)
		cout<<i<<' ';
}