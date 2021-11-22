#include<bits/stdc++.h>
using namespace std;
typedef long long u_64;

template<typename T>
int binSearch(vector<T> a, int low , int high, T k){//returns index
	int mid = low + (high-low)/2;
	if(low>=high)
		return high;//Low for upper_bound, high for lower_bound, ironic
	if(a[mid]==k)
		return mid;
	else if(a[mid]>k)
		return binSearch(a,low, mid-1,k);
	else
		return binSearch(a,mid+1,high,k);
}

/*int iter_binSearch(int *a, int low, int high, int k)
{
	while(low<high)
	{
		int mid = low+(high-low)/2;
		if(a[mid]==k)
			return mid;
		else if(a[mid]>k)
			high = mid-1;
		else
			low = mid+1;
	}
	return -1;
}
*/

string sum_two(vector<int> a,  int sum)
/*
{
	sort(a,a+size);
	for(int i=0;i<size;i++)
	{
		int temp = sum - a[i];
		if(binSearch(a,0,size-1,temp)!=-1)
			return "YES\n";
	}
	return "NO\n";
}
*/
{	
	int size =  a.size();
	sort(a.begin(), a.end());
	int l = 0, r = size - 1;
	while(l < r)
	{
		if( a[l] + a[r] == sum ) return "YES\n";
		else if ( a[l] + a[r] > sum ) r--;
		else l++;
	}
	return "NO\n";
}

int main()
{
	int n{10};
	std::vector<int> a{20,1,2,3,4,5,6,7,8,11};
	//sort(a.begin(), a.end());
	cout<<sum_two(a, 100);
}