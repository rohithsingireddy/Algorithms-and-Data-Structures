#include<bits/stdc++.h>
using namespace std;
const int m {10000};
const int a {12};
const int b {23};
int hashArray[m];

//prime generator


const int p = 19394489;

int hashfunc(int k){

	int temp = (a*k+b)%p;
	return temp % m;
}

int insert(int val){
	int temp = hashfunc(val);
	hashArray[temp] = val;
}

int search(int val)
{
	int k = hashfunc(val);
	if(hashArray[k]!=val)
		return -1;
	return k;
}

int deleteVal(int val)
{
	int k = hashfunc(val);
	hashArray[k] = -1;
}

int main()
{
	for(int i=0;i<10;i++)
		insert(i);
	for(int i=0;i<10;i++)
		cout<<search(i)<<' ';

}