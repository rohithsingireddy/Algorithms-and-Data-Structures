#include<bits/stdc++.h>
using namespace std;
const int MAX {100};

void selectionSort(int *a, int size){
	int i=0;
	int n =size;
	while(i<n)
	{
		int j=i;
		int m=MAX;
		int min_index=i;
		while(j<n)
		{
			if(m>a[j])
			{
				m = a[j];
				min_index = j;
			}
			j++;
		}
		swap(a[i],a[min_index]);
		i++;
	}
}

int main(){
	int n{6};
	int a[]{6,5,4,3,2,1};
	selectionSort(a,6);
	for(auto i:a)
		cout<<i<<' ';
}