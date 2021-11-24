#include <stack>
#include <cstring>
#include <iostream>

namespace Sort {
	/*
	* Takes two elements of same type and swaps their values
	* Returns null
	*/
	template<typename T>
	void swap(T& a, T& b) {
		T hold = a; 
		a = b;
		b = hold;
	}

	/*
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 */
	template<typename T>
	void insertion_sort(T* array, int size) {
		for(int i = 1; i < size; i++) {
			T current = array[i];
			int j = i - 1;
			for( j; j >= 0 && array[j] > current; j--) {
				array[j+1] = array[j];
			}
			array[j+1] = current; 
		}
	}

	/*
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 */
	template<typename T>
	void selection_sort(T* array, int size) {

		for( int i = 0; i < size-1; i++ ) {
			int index_of_min = i;
			for( int j = i+1; j < size; j++ ) {
				if( array[index_of_min] > array[j] ) {
					index_of_min = j;
				}
			}
			swap(array[index_of_min], array[i]);
		}
	}

	/*
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 */
	template<typename T>
	void quick_sort(T* array, int size) {
		std::stack< std::pair<int,int> > stack;
		stack.push( std::pair<int,int>(0, size - 1) );
		
		while(!stack.empty()) {
			std::pair<int,int> range = stack.top();
			stack.pop();

			T pivot = array[range.second];
			
			
			//Partition procedure begin			

			//Index before which elements are less than	pivot (inclusive)
			int i = range.first - 1;

			for( int j = range.first; j < range.second; ++j ) {
				
				if( array[j] < pivot ) {
					i += 1;
					swap(array[i], array[j]);
				}
			}
			int partition_index = i + 1;
			swap(array[partition_index], array[range.second]);
			//Partition procedure end

			if(range.first < partition_index-1) {
				stack.push(std::pair< int, int >(range.first, partition_index - 1));
			}
			if(partition_index+1 < range.second) {
				stack.push(std::pair< int, int >(partition_index + 1, range.second));
			}
		}
	}

	/*
	 * Takes array, size and maximum value in array as input
	 * Sorts the array using count sort
	 * Only used on non-negaitve integers
	 */
	template<typename T = unsigned long long>
	void count_sort(T* array, int size, T max_value_of_element) {
		int* count_of_element;
		count_of_element = new int[max_value_of_element+1];

		memset(count_of_element, 0, sizeof count_of_element);

		for( int i = 0; i < size; i++ ) {
			count_of_element[array[i]] += 1;
		}

		for( int i = 1; i <= max_value_of_element; i++ ) {
			count_of_element[i] += count_of_element[i-1];
		}

		T* sorted_array = new T[size];
		for( int i = size-1; i >= 0; --i ) {
			sorted_array[--count_of_element[array[i]]] = array[i];
		}

		for( int i = 0; i < size; i++ ) {
			array[i] = sorted_array[i];
		}
	}

	/*
	 * Takes an non-negative integer array, size, maximum allowed digits in a number as input
	 * Sorts the array using radix sort
	 * Returns null
	 */
	void radix_sort( unsigned long long* array, unsigned int size, int max_digits = 20) {

		const unsigned long long DIVISOR = 10;
		struct number {
			int digit;
			unsigned long long value, actual_value;
			
			number():value(0), actual_value(0) {}
			
		};
		number* number_array = new number[size];
		for( int i = 0; i < size; i++ ) {
			number_array[i].value = array[i];
			number_array[i].actual_value = array[i];
		}

		while( max_digits-- ) {
			for( int i = 0; i < size; i++ ) {
				number_array[i].digit = number_array[i].value / DIVISOR;
				number_array[i].value /= DIVISOR;
			}
			unsigned long long count_array[10];
			for( int i = 0; i < 10; i++ ) {
				count_array[i] = 0;
			}
			for( int i = 0; i < size; i++ ) {
				count_array[number_array[i].digit]++;
			}
			for( int i = 1; i < 10; i++ ) {
				count_array[i] += count_array[i-1];
			}
			number* partially_sorted_array = new number[size];
			for( int i = size-1; i >= 0; i-- ) {
				partially_sorted_array[--count_array[number_array[i].digit]] = number_array[i];
			}
			for( int i = 0; i < size; i++ ) {
				number_array[i] = partially_sorted_array[i];
			}
		}
		for( int i = 0; i < size; i++ ) {
			array[i] = number_array[i].actual_value;
		}
	}

}