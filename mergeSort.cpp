#include<bits/stdc++.h>
using namespace std;
const int sentinel=10e3;
int inversions=0;

void merge(int *a, int p, int q, int r)
{

	//if(r-p+1<=k)
	//{
	//	insertionSort(a,p,r);
	//	return;
	//}
	int n1 = q-p+1;
	int n2 = r-q;
	int left[n1],right[n2];
	for(int i=0;i<n1;i++)
		left[i] = a[p+i];
	for(int i=0;i<n2;i++)
		right[i] = a[q+i+1];
	left[n1] = sentinel;
	right[n2] = sentinel;
	int i=0,j=0,k;
	for(k=p;k<=r;k++)
	{
		if(left[i]<right[j])
			a[k] = left[i++];
		else{
			inversions += n1-i;
			a[k] = right[j++];
		}
		//if(i==n1||j==n2)
		//	break;
	}
	/*k++;
	while(i<n1)
		a[k++] = left[i++];
	while(j<n2)
		a[k++] = right[j++];
	*/
}

void merge_sort(int *a, int p, int q)
{
	if(p<q)
	{
		int mid = (p+q)/2;
		merge_sort(a,p,mid);
		merge_sort(a,mid+1,q);
		merge(a,p,mid,q);

	}
}


int main()
{
	int n{8};
	int a[]{2,3,4,5,6,7,8,1};
	merge_sort(a,0,n-1);
	for(auto i:a)
		cout<<i<<' ';
	cout<<'\n'<<inversions;
}