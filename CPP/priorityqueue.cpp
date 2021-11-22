#include<bits/stdc++.h>
using namespace std;
const int SENTINEL = -1;
const int MAX = 1000000;

struct minpriorityQueue{
	deque<int> dq{SENTINEL};
	int queueSize{0};
	//minpriorityQueue(){dq.push_back(SENTINEL); queueSize = 0;}

	inline int heapMin(){return dq[1];}

	int extract_heapMin(){
		if(queueSize<0)
			throw "Heap Underflow\n";
		int max = dq[1];
		dq[1] = dq[queueSize--];
		minHeapify(1);
		return max;
	}

	void minHeapify(int i)
	{
		while(i<=queueSize/2)
		{
			int l = 2*i;
			int r = 2*i+1;
			int smallest = i;
			if(l<=queueSize && dq[smallest]>dq[l])
				smallest = l;
			if(r<=queueSize && dq[smallest]>dq[r])
				smallest = r;
			if(smallest != i)
			{
				swap(dq[smallest], dq[i]);
				i = smallest;
			}
			else
				break;
		}
	}

	void decrease_key(int i,int key){
		if(key>dq[i])
			throw "Key is greater than current.\n";
		//dq[i] = key;
		while(i>1 && dq[i/2]>dq[i]){
			dq[i] = dq[i/2];
			i /= 2;
		}
		dq[i] = key;
	}

	void insertKey(int val)
	{
		queueSize += 1;
		dq.push_back(MAX);
		decrease_key(queueSize, val);
	}

	void deleteKey(int i){
		if(queueSize<=0)
			return;
		decrease_key(i, -MAX);
		swap(dq[1],dq[queueSize--]);
		minHeapify(1);
	}

};

int main(){

	vector<int> a{1,2,3,4,5,6,7,8,9};
	minpriorityQueue pq;
	for(auto i:a)
		pq.insertKey(i);
	//pq.deleteKey(3);
	while(pq.queueSize>0)
		cout<<pq.extract_heapMin()<<' ';
}	