#include <stdexcept>

template<typename T>
class Stack_Array{
private:
	int top, max_size;
	T* stack;

public:
	/**
	 * Default constructor
	 */ 
	explicit Stack_Array(int n)
	{
		this->top = -1;
		this->max_size = n;
		stack = new int[max_size];
	}

	/**
	 * Copy Constructor
	 */ 
	Stack_Array(const Stack_Array &other)
	{
		this->top = -1;
		this->max_size = other->max_size;
		stack = new int[max_size];
		while( !other.isEmpty() )
		{
			this->push(other.pop());
		}
	}

	/**
	 * Destructor
	 */
	~Stack_Array()
	{
		delete[] this->stack;
	} 

	/*
	 * Takes a value and pushes to the end of the array
	 * Returns null
	 */
	void push(T val){
		if(top >= max_size) {
			throw std::runtime_error("Overflow\n");
		}
		stack[++top] = val;
	}
	
	/*
	 * Returns and removes the last element at the array
	 */
	T pop(){
		if(top < 0){
			throw std::runtime_error("Underflow\n");
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

	/**
	 * Overloading = operator
	 */
	void operator=(const Stack_Array &other)
	{
		this->top = other.top;
		this->max_size = other.max_size;
		this->stack = other.stack;

	} 

};
