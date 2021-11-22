#include<bits/stdc++.h>
using namespace std;

struct heapTree{
	int *a;
	int heapSize;
	heapTree(int *t, int s){
		heapSize = s;
		a = new int[s+1];
		a[0] = s;
		for(int i=1;i<=s;i++)
			a[i] = t[i-1];
	}
	~heapTree(){
		delete[] a;
	}
	inline int parent(int i)
	{
		return i/2;
	}
	inline int left(int i)
	{
		return 2*i;
	}
	inline int right(int i)
	{
		return 2*i+1;
	}
	void rec_maxHeapify(int i)
	{
		int l = 2*i;
		int r = 2*i+1;
		int largest = i;
		if(l<=heapSize && a[largest]<a[l])
			largest = l;
		if(r<=heapSize && a[largest]<a[r])
			largest = r;
		if(largest!=i)
		{
			swap(a[largest], a[i]);
			rec_maxHeapify(largest);
		}
	}

	void iter_maxHeapify(int i)
	{
		while(i<=heapSize/2)
		{
			int l = 2*i;
			int r = 2*i+1;
			int largest = i;
			if(l<=heapSize && a[l]>a[largest])
				largest = l;
			if(r<=heapSize && a[r]>a[largest])
				largest = r;
			if(largest!=i)
			{
				swap(a[largest], a[i]);
				i = largest;
			}
			else
				break;
		}
	}

	void build_max_heap(){
		//heapSize = size;
		//copy
		for(int i=heapSize/2;i>0;i--)
			iter_maxHeapify(i);
	}

	void heapSort()
	{
		//After bulilding max_heap;
		for(int i=heapSize;i>1;i--)
		{
			swap(a[i],a[1]);
			heapSize--;
			iter_maxHeapify(1);
		}
	}
};

int main()
{
	int a[]{1,2,3,4,5,6,7,8,9};
	heapTree ht(a,9);
	ht.build_max_heap();
	ht.heapSort();
	for(int i=1;i<=9;i++)
		cout<<ht.a[i]<<' ';
}