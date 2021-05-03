#include<bits/stdc++.h>
using namespace std;

inline void insertionSort(int *a,int size){
	for(int i=0;i<size;i++)
	{
		int temp_holder = a[i];
		int j = i-1;
		while(j>=0 && a[j]<temp_holder)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp_holder;
		for(int i=0;i<size;i++)
            cout<<a[i]<<' ';
        cout<<'\n';
	}
}

void rec_insertionSort(int *a, int size){
	if(size>1)
		rec_insertionSort(a,size-1);
	int temp = a[size];
	int j  = size-1;
	while(j>=0 && a[j]>temp){
		a[j+1] = a[j];
		j--;
	}
	a[j+1] = temp;
}
	/*if(size>0)
		rec_insertionSort(a,size);
	int temp = a[size];
	int j  = size-1;
	while(j>=0 && a[j]>temp){
		a[j+1] = a[j];
		j--;
	}
	a[j+1] = temp;
	*/

int main(){
	int a[10]{22,44,23,12,989,45,23,45,687,23};
	//for(int i=0;i<1000000;i++){a[i] = 1000000-i;}
	rec_insertionSort(a,9);
	for(auto i:a)
		cout<<i<<' ';
}
