#include <stack>
#include <stdio.h>
#include <vector>

namespace Search
{

	/** 
	 * Takes a sorted array, its size and element to search as input and returns an integer as output
	 * Returns lowest index in case of more than one occurrence of the searched element
	 * If element is not in array, index of the first upper bound of element is returned
	 * Return -1 if no element and upper bound exist
	 * 
	 * Time complexity = O(log(n))
	 * Space Complexity = O(1)
	 */
	template <typename T>
	int upper_bound(const std::vector<T> &array, T value_to_search)
	{
		int size = array.size();
		int low = 0, high = size;

		while (low != high)
		{
			int current = (low + high - 1) / 2; // Floor w.r.t division by 2 since low(left) is being 'tightly bounded'
			if (array[current] <= value_to_search)
			{
				low = current + 1;
			}
			else
			{
				high = current;
			}
		}
		if (low == size)
		{
			return -1;
		}
		return low;
	}

	/** 
	 * Takes a sorted array, its size and element to search as input and returns an integer as output
	 * Returns highest index in case of more than one occurences of the searched element
	 * If element is not in array, index of the last lower_bound of element is returned
	 * Returns -1 if no element and its lower bound exist in the array
	 * 
	 * Time complexity = O( log(n))
	 * Space complexity = O(1)
	 */
	template <typename T>
	int lower_bound(const std::vector<T> &array, T value_to_search)
	{
		int size = array.size();
		int low = 0, high = size;
		while (low != high)
		{
			int current = (low + high + 1) / 2; // Ceil w.r.t division by 2 since high(right) is being 'tightly bounded'

			if (value_to_search < array[current])
			{
				high = current - 1;
			}
			else
			{
				low = current;
			}
		}
		if (low == 0 && array[low] > value_to_search)
		{
			return -1;
		}
		return low;
	}

	/**
	 * Takes a unsorted array with comparable elements, its size and nth element in a sorted list to find.
	 * Returns the nth element 
	 * If input array is 101,102,103 and 2nd element was to be found, 102 is returned.
	 * Uses the partition procedure of quick sort to divide the elements
	 * Modifies the position of array elements
	 * Should be tested
	 * 
	 * Time complexity = O(n)
	 * Space complexity = O(n)
	 */
	template <typename T>
	T nth_element_in(std::vector<T> array, T nth_element_to_find)
	{
		int size = array.size();
		if (nth_element_to_find <= 0 || nth_element_to_find > size)
		{
			return -1;
		}

		std::stack<std::pair<int, int>> stack;
		stack.push(std::make_pair(0, size - 1));

		while (!stack.empty())
		{

			auto range = stack.top();
			stack.pop();

			T pivot = array[range.second];

			if (range.first == range.second)
			{
				return pivot;
			}

			//Partition procedure begin

			//Index before which elements are less than	pivot (inclusive)
			int i = range.first - 1;

			for (int j = range.first; j < range.second; ++j)
			{

				if (array[j] < pivot)
				{
					i += 1;
					std::swap(array[i], array[j]);
				}
			}
			int partition_index = i + 1;
			std::swap(array[partition_index], array[range.second]);
			//Partition procedure end

			// Number of elements less than or equal to element in the given sub-array
			int elements_lt_or_eq_pivot = partition_index - range.first + 1;

			if (elements_lt_or_eq_pivot == nth_element_to_find)
			{
				return array[partition_index];
			}
			else if (nth_element_to_find < elements_lt_or_eq_pivot)
			{
				stack.push(std::make_pair(range.first, partition_index - 1));
			}
			else
			{
				stack.push(std::make_pair(partition_index + 1, range.second));
				nth_element_to_find -= elements_lt_or_eq_pivot;
			}
		}
		return -1;
	}

}