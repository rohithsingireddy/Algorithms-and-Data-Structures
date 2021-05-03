#include<bits/stdc++.h>

int greedy_finishFirst(int *s, int *f, int size){
	int last_finished = f[0];
	std::vector<int> act{1};
	int no_of_activities = 1;
	for(int i=1;i<size;i++)
	{
		if(s[i]>=last_finished)
		{
			last_finished = f[i];
			act.push_back(i+1);
			no_of_activities++;
		}
	}
	for(auto i:act)
		std::cout<<i<<' ';
	std::cout<<'\n';
	return no_of_activities;
}



int main(){
	int s[]{1,3,0,5,3,5,6,8,8,2,12};
	int f[]{4,5,6,7,9,9,10,11,12,14,16};
	//std::cout<<'\n';
	std::cout<<greedy_finishFirst(s,f,12);

}