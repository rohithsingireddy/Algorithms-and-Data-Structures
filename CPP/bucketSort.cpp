#include<bits/stdc++.h>
using namespace std;

void bucket_sort(double *a,int size)
{
	vector<double> v[10];
	for(int i=0;i<size;i++)
	{
		int temp = (int)a[i]*10;
		v[temp].push_back(a[i]);
	}

	for(int i=0;i<10;i++){
		sort(v[i].begin(), v[i].end());
	}
	int k=0;
	for(int i=0;i<10;i++)
		for(auto j:v[i])
			a[k++] = j;

}


int main(){
	double a[]{0.89,0.23,0.45,0.19,0.60,0.23};
	bucket_sort(a,6);
	for(auto i:a)
		cout<<i<<' ';
}