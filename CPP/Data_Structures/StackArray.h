
const int STACK_SIZE = 1000;

template<typename T = int>
struct StackArray{
	int top = -1;
	T stack[STACK_SIZE];

	void push(T val){
		if(top >= STACK_SIZE) {
			throw "Overflow\n";
			return;
		}
		stack[++top] = val;
	}
	T pop(){
		if(top < 0){
			throw "Underflow\n";
			return T();
		}
		return stack[top--];
	}
	bool isEmpty(){
		if(top < 0)
			return true;
		return false;
	}

};
