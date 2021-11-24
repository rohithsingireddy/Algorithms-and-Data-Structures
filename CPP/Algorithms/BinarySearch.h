namespace bin_search {
	
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

}