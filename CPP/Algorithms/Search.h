#include <stack>

namespace search {
	
	/* 
	 * Takes a sorted array, its size and element to search as input and returns an integer as output
	 * Returns lowest index in case of more than one occurrence of the searched element
	 * If element is not in array, index of the first upper bound of element is returned
	 * Return array size if no element and upper bound exist
	 */
	template<typename T>
	int upper_bound( T* a, int size, T value_to_search) {
		int low = 0, high = size, current = 0;
		while( low != high ) {
			current = ( low + high - 1)/2;
			
			if( a[current] < value_to_search ) {
				low = current+1;
			}

			else {
				high = current;
			}

		}
		return low;
	}


	/* 
	 * Takes a sorted array, its size and element to search as input and returns an integer as output
	 * Returns highest index in case of more than one occurences of the searched element
	 * If element is not in array, index of the last lower_bound of element is returned
	 * Returns -1 if no element and its lower bound exist in the array
	 */ 
	template<typename T>
	int lower_bound( T* a, int size, T value_to_search) {
		int low = 0, high = size, current = 0;
		while( low !=  high ) {
			current = (low + high + 1)/2;

			if( value_to_search < a[current] ) {
				high = current - 1;
			}
			else {
				low = current;
			}
		}
		if( low == 0 && a[low] > value_to_search ) {
			return -1;
		}
		return low;
	}


	/*
	 * Takes a unsorted array with comparable elements, its size and nth element in a sorted list to find.
	 * Returns the nth element 
	 * If input array is 101,102,103 and 2nd element was to be found, 102 is returned.
	 * Uses the partition procedure of quick sort to divide the elements
	 * Modifies the position of array elements
	 * Should be tested
	 */
	template<typename T>
	int get_less_elements( T* array, int size, T nth_element_to_find ) {
		std::stack< std::pair<int, int> > stack;
		stack.push(std::make_pair(0, size-1));

		while( !stack.empty() ) {

			auto range = stack.top();
			stack.pop();

			T pivot = array[range.second];
			
			
			//Partition procedure begin			

			//Index before which elements are less than	pivot (inclusive)
			int i = range.first - 1;

			for( int j = range.first; j < range.second; ++j ) {
				
				if( array[j] < pivot ) {
					i += 1;
					std::swap(array[i], array[j]);
				}
			}
			int partition_index = i + 1;
			std::swap(array[partition_index], array[range.second]);
			//Partition procedure end

			if( partition_index + 1 < nth_element_to_find && range.first < partition_index - 1) {
				stack.push(std::make_pair(range.first, partition_index - 1));
			}
			else if(range.second > partition_index + 1){
				stack.push(std::make_pair(partition_index + 1, range.second));
				nth_element_to_find -= (partition_index - range.first + 1);
			}
			else {
				return array[partition_index];
			}

		}
		return -1;
	} 

}