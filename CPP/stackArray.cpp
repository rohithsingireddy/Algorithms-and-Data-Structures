#include<bits/stdc++.h>
using namespace std;

struct stackArray{
	int top = -1;
	int a[100];
	void push(int val){
		if(top>=100){
			throw "Overflow\n";
			return;
		}
		a[++top] = val;
	}
	int pop(){
		if(top==-1){
			throw "Underflow\n";
			return -1;
		}
		return a[top--];
	}
	bool isEmpty(){
		if(top==-1)
			return true;
		return false;
	}
};

int main(){
	stackArray st;
	st.push(4);
	cout<<st.pop()<<' ';
	cout<<st.isEmpty()<<' ';
}