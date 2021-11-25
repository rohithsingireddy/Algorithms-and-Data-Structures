#include <iostream>
const int STACK_SIZE = 1000;

template<typename T = int>
struct StackArray{
	int top = -1;
	T stack[STACK_SIZE];


	
	/*
	 * Takes a value and pushes to the end of the array
	 * Returns null
	 */
	void push(T val){
		if(top >= STACK_SIZE) {
			throw std::runtime_error("Overflow\n");
			return;
		}
		stack[++top] = val;
	}

	
	/*
	 * Returns and removes the last element at the array
	 */
	T pop(){
		if(top < 0){
			throw std::runtime_error("Underflow\n");
			return T();
		}
		return stack[top--];
	}

	
	/*
	 * Returns true if the stack is empty
	 * Else false
	 */
	bool isEmpty(){
		if(top < 0)
			return true;
		return false;
	}

};
