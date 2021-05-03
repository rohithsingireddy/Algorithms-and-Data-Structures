#include<bits/stdc++.h>
using namespace std;
//Did not check. Was feeling sleepy.
struct queueArray{
	int f_head = -1,f_tail = 0, b_tail = 1, b_head=-1;
	int a[100];
	void enqueueFront(int front){
		if(f_tail+1==b_head || b_head+1==f_head)
			return;
		if(f_head==-1)
			f_head = f_tail;
		a[f_tail--] = front;
		if(f_tail<0)
			f_tail = 99;
	}


	void enqueueLast(int back){
		if(f_tail+1==b_head || b_tail+1==f_head)
			return;

		if(b_head==-1)
			b_head = b_tail;
		a[b_tail++] = back;
		if(b_tail>99)
			b_tail = 0;
	}

	int popFirst(){
		if(f_tail+1==b_head || b_tail+1==f_head)
			return -1;
		int temp = a[f_head];
		f_head--;
		if(f_head<0)
			f_head = 99;
		return temp;
	}

	int popLast(){
		if(f_tail+1==b_head || b_head+1==f_head)
			return -1;
		int temp = a[b_head];
		b_head++;
		if(b_head>99)
			b_head = 0;
		return temp;
	}
};

int main(){
	queueArray qa;
	qa.enqueueFront(1);
	qa.enqueueLast(100);
	cout<<qa.popLast()<<' '<<qa.popFirst();
}