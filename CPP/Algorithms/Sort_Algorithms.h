#include <stack>
#include <cstring>
#include <vector>

namespace Sort
{
	/**
	 * Takes two elements of same type and swaps their values
	 * Returns null
	 * 
	 * Time Complexity = O(1)
	 * Space Complexity = O(1)
	 */
	template <typename T>
	void swap(T &a, T &b)
	{
		T hold = a;
		a = b;
		b = hold;
	}

	/**
	 * Implements Bubble Sort
	 * Takes a vector array of comparable elements as a reference input and sorts them using Bubble sort
	 * 
	 * Time complexity = O(n^2)
	 * Space Complexity = O(1)
	 */
	template <typename T>
	void bubble_sort(std::vector<T> &array)
	{
		int size = array.size();
		for (int i = size - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (array[j] > array[j + 1])
				{
					swap<T>(array[j], array[j + 1]);
				}
			}
		}
	}

	/**
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 * 
	 * Time complexity = O(n^2)
	 * Space Complexity = O(1)
	 */
	template <typename T>
	void insertion_sort(std::vector<T> &array)
	{
		int size = array.size();
		for (int i = 1; i < size; i++)
		{
			T current = array[i];
			int j = i - 1;
			for (; j >= 0 && array[j] > current; j--)
			{
				array[j + 1] = array[j];
			}
			array[j + 1] = current;
		}
	}

	/**
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 * 
	 * Time complexity = O(n^2)
	 * Space complexity = O(1)
	 */
	template <typename T>
	void selection_sort(std::vector<T> &array)
	{
		int size = array.size();
		for (int i = 0; i < size - 1; i++)
		{
			int index_of_min = i;
			for (int j = i + 1; j < size; j++)
			{
				if (array[index_of_min] > array[j])
				{
					index_of_min = j;
				}
			}
			swap(array[index_of_min], array[i]);
		}
	}

	/**
	 * Takes array and its size as input
	 * Uses quick sort to sort the array
	 * Returns null
	 * 
	 * Time complexity = O( n log(n) )
	 * Space Complexity = O( log(n) )
	 */
	template <typename T>
	void quick_sort(std::vector<T> &array)
	{
		int size = array.size();
		std::stack<std::pair<int, int>> stack;
		stack.push(std::pair<int, int>(0, size - 1));

		while (!stack.empty())
		{
			std::pair<int, int> range = stack.top();
			stack.pop();

			T pivot = array[range.second];

			// Partition procedure begin

			// Index before which elements are less than	pivot (inclusive)
			int i = range.first - 1;

			for (int j = range.first; j < range.second; ++j)
			{

				if (array[j] < pivot)
				{
					i += 1;
					swap(array[i], array[j]);
				}
			}
			int partition_index = i + 1;
			swap(array[partition_index], array[range.second]);
			// Partition procedure end

			if (range.first < partition_index - 1)
			{
				stack.push(std::pair<int, int>(range.first, partition_index - 1));
			}
			if (partition_index + 1 < range.second)
			{
				stack.push(std::pair<int, int>(partition_index + 1, range.second));
			}
		}
	}

	/**
	 * Takes a vector array, size and maximum value in array as input
	 * Sorts the array using count sort
	 * Only used on non-negaitve integers
	 * 
	 * Time complexity = O(n)
	 * Space Complexity = O(n)
	 */
	template <typename T = unsigned long long>
	void count_sort(std::vector<T> &array, int max_value_of_element, bool be_stable = true)
	{
		int size = array.size();
		std::vector<int> count_of_element(max_value_of_element + 1, 0);

		for (int i = 0; i < size; i++)
		{
			count_of_element[array[i]] += 1;
		}

		for (int i = 1; i <= max_value_of_element; i++)
		{
			count_of_element[i] += count_of_element[i - 1];
		}

		std::vector<T> sorted_array(size);
		if (be_stable)
		{
			for (int i = size - 1; i >= 0; --i)
			{
				sorted_array[--count_of_element[array[i]]] = array[i];
			}
		}
		else
		{
			for (int i = 0; i < size; ++i)
			{
				sorted_array[--count_of_element[array[i]]] = array[i];
			}
		}
		array = sorted_array;
	}

	/**
	 * Takes an non-negative integer array, size, maximum allowed digits in a number as input
	 * Sorts the array using radix sort
	 * Returns null
	 * 
	 * Time Complexity = O(n * max_digits)
	 * Space Complexity = O(n)
	 */
	void radix_sort(std::vector<unsigned long long> &array, int max_digits = 20)
	{
		int size = array.size();
		const unsigned long long DIVISOR = 10;
		
		// Helper datatype to make radix sorting easier to implement
		struct number
		{
			int digit;
			unsigned long long value, actual_value;

			operator int() const 
			{
				return digit;
			}

		};

		std::vector<number> number_array(size);
		for (int i = 0; i < size; i++)
		{
			number_array[i].value = array[i];
			number_array[i].actual_value = array[i];
		}

		while (max_digits--)
		{
			for (int i = 0; i < size; i++)
			{
				number_array[i].digit = number_array[i].value % DIVISOR;
				number_array[i].value /= DIVISOR;
			}
			
			// A stable sort
			count_sort(number_array, 10);
		}
		for (int i = 0; i < size; i++)
		{
			array[i] = number_array[i].actual_value;
		}
	}

	/**
	 * Used as a sub procdure in merge sort
	 * 
	 * Time Complexity = O(n)
	 * Space Complexity = O(n)
	 */
	template <typename T>
	void merge(std::vector<T> &array, int left, int right)
	{

		int mid = (left + right) / 2;
		int left_array_size = mid - left + 1;
		int right_array_size = right - mid;

		T *left_array = new T[left_array_size];
		T *right_array = new T[right_array_size];

		for (int i = left, j = 0; i <= mid; i++, j++)
		{
			left_array[j] = array[i];
		}

		for (int i = mid + 1, j = 0; i <= right; j++, i++)
		{
			right_array[j] = array[i];
		}

		int left_index = 0, right_index = 0, current_index = left;

		while (left_index < left_array_size && right_index < right_array_size)
		{
			if (left_array[left_index] < right_array[right_index])
			{
				array[current_index++] = left_array[left_index++];
			}
			else
			{
				array[current_index++] = right_array[right_index++];
			}
		}

		while (left_index < left_array_size)
		{
			array[current_index++] = left_array[left_index++];
		}

		while (right_index < right_array_size)
		{
			array[current_index++] = right_array[right_index++];
		}
	}

	/**
	 * Takes array, starting index and ending index of the sub array to sort
	 * Uses merge sort to sort the array
	 * 
	 * Time Complexity = O(n log(n) )
	 * Space Complexity = O( n log(n) )
	 */
	template <typename T>
	void merge_sort(std::vector<T> &array, int left, int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2;
			merge_sort(array, left, mid);
			merge_sort(array, mid + 1, right);
			merge(array, left, right);
		}
	}

	/**
	 * Takes array and its size as input
	 * Uses Merge sort to sort the array
	 * 
	 * Same complexitites as above
	 */
	template <typename T>
	void merge_sort(std::vector<T> &array)
	{
		int size = array.size();
		merge_sort(array, 0, size - 1);
	}

}