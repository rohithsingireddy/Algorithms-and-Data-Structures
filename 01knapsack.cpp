#include<bits/stdc++.h>
int d[100][100];
int knapSack(int *w, int *p, int i, int wi, int max_w){
	if(i<=0 || w<=0)
		return 0;
	if(wi>max_w)
		return d[i-1][max_w];
	if(d[i][wi]>0)
		return d[i][wi];
	auto temp1 = knapSack(w,p,i-1,max_w-wi, max_w) + p[i];
	auto temp2 = knapSack(w,p,i-1,wi, max_w);
	if(temp1<temp2)
		d[i][wi] = temp2;
	else
		d[i][wi] = temp1;
	return d[i][wi];
}

void print(int i, int w, int max_w){
	if(i<0 || w<0)
		return;
	if(d[i][w]==d[i-1][w])
		print(i-1,w, max_w);
	else{
		print(i-1, max_w-w, max_w);
		std::cout<<i<<' ';
	}
}
int main(){
	int w[]{10,20,30};
	int p[]{60,100,120};
	for(int i=0;i<100;i++)
		std::fill(d[i], d[i]+100, 0);
	std::cout<<knapSack(w,p,3, 50, 50)<<'\n';
	print(3,50,50);
}
