#include <iostream>

/*
 * Array uses one-based indexing to access elements
 * Implements min-heap tree
 * Can be used for min priority queue
 */ 
template <typename T>
class HeapTree
{
	T *array;
	int max_size;
	int heap_size;

	/*
	 * Takes two elements by references 
	 * Swaps the values of given elements using call by reference
	 */
	void swap(T &a, T &b)
	{
		T hold = a;
		a = b;
		b = hold;
	}

	/*
	 * Takes index as input and returns the possible index of its left child
	 */
	inline int left_child(int index)
	{
		return index * 2;
	}

	/*
	 * Takes index as input and returns the possible index of its right child.
	 */
	inline int right_child(int index)
	{
		return 2 * index + 1;
	}

	/* 
	 * Takes index as input and returns its parents
	 * Returns zero if the given index is of root
	 */
	inline int parent(int index)
	{
		return index / 2;
	}

	/*
	 * Takes index as input and 'heapifies' the input index and its children recursively
	 * Recursion stops when a parent is not swapped with one of its children
	 */
	void min_heapify(int index)
	{
		int l_child = left_child(index);
		int r_child = right_child(index);
		int smallest = index;

		if (l_child <= heap_size && array[l_child] < array[smallest])
		{
			smallest = l_child;
		}

		if (r_child <= heap_size && array[r_child] < array[smallest])
		{
			smallest = r_child;
		}

		if (smallest != index)
		{
			swap(array[smallest], array[index]);
			min_heapify(smallest);
		}
	}

	/*
	 * Converts the entire array into a min-heap
	 */
	void build_min_heap()
	{
		heap_size = max_size;
		for (int i = heap_size / 2; i > 0; i--)
		{
			min_heapify(i);
		}
	}

public:
	/*
	 * Constructors for the class
	 */
	HeapTree(int size) : max_size(size), array(new T[size + 1]), heap_size(0) {}
	HeapTree(int size, T *a) : max_size(size), array(a), heap_size(0) {}

	/* 
	 * Takes a value and index as inputI
	 * Inserts the value in the array at given index
	 * Also used for overwriting a value with a less value at a given index which acts as a substitute for value deletion
	 */
	void insert(T value, int index = -1)
	{
		if( index == -1 ) {
			index = heap_size + 1;
		}
		if( index == heap_size+1 && index > max_size ) {
			throw std::invalid_argument("Heap array is full.\n");
		}
		if( index <= heap_size && array[index] < value ) {
			throw std::invalid_argument("Cannot insert a greater value in place of lesser value.\n");
		}
		array[index] = value;
		if( index == heap_size + 1 ) {
			heap_size++;
		}
		while( parent(index) != 0 && array[index] < array[parent(index)] ) {
			swap( array[parent(index)], array[index] );
			index = parent(index);
		}
	}

	/*
	 * Sorts the heap array 
	 * Sorts the array in descending array
	 * Array stops being a min tree after this operation
	 */
	void heap_sort()
	{
		build_min_heap();
		for (int i = max_size; i > 1; i--)
		{
			swap(array[1], array[i]);
			heap_size--;
			min_heapify(1);
		}
	}

	/*
	 * Remove a value from given index
	 */
	T remove(int index = 1) {
		if( index < 0 || index > heap_size ) {
			throw std::runtime_error("Index out of bounds");
		}
		T temp = array[index];
		swap(array[index], array[heap_size--]);
		min_heapify(index);
		return temp;
	}

	/*
	 * Returns the root (or minimimum) of the tree
	 */
	T root_of_tree()
	{
		return array[1];
	}

	/*
	 * Returns true if the heap is empty
	 */
	bool is_empty()
	{
		return this->heap_size == 0;
	}
};