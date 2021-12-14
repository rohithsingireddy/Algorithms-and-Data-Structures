#include <functional>
#include <stdexcept>

namespace Data_Structures
{
	/*
	 * It takes array of elements, a placeholder value and a function as input that compares 
	 * two objects of type T and returns appropriate value as constructor arguments
	 * The placeholder value is returned when no other value of array can be returned
	 */
	template <typename T>
	class Segment_Tree
	{
	private:
		struct Segment_Node
		{
			int left_index = 0, right_index = 0;
			T data = T();
			Segment_Node *left_child = nullptr, *right_child = nullptr;
		};
		Segment_Node *root;
		T placeholder; // Value to return when no value is possible
		std::function<T(T, T)> operation;
		int size;

		/*
		 * Builds the segement tree from the given array
		 */
		void build(const std::vector<T> &array)
		{

			this->root = new Segment_Node();

			std::function<void(Segment_Node *, int, int)> divide =
				[&array, &divide, this](Segment_Node *cur, int left, int right) -> void
			{
				if (left == right)
				{
					cur->data = array[left];
				}
				else
				{
					int mid = (left + right) / 2;
					cur->left_child = new Segment_Node();
					cur->right_child = new Segment_Node();

					divide(cur->left_child, left, mid);
					divide(cur->right_child, mid + 1, right);
					cur->data = this->operation(cur->left_child->data, cur->right_child->data);
				}
				cur->left_index = left;
				cur->right_index = right;
			};

			divide(this->root, 0, array.size() - 1);
		}

		/*
		 * Returns the data after performing given operation
		 * between the values in the given range
		 */
		T range(Segment_Node *cur, int left, int right)
		{

			if (left > right)
			{
				return this->placeholder;
			}

			if (cur == nullptr)
			{
				throw std::runtime_error("A null pointer is being accessed");
			}
			
			int left_index = cur->left_index;
			int right_index = cur->right_index;

			if (left == left_index && right == right_index)
			{
				return cur->data;
			}
			printf("%5d %5d\n", left_index, right_index);

			if (cur->left_child == nullptr && cur->right_child == nullptr)
			{
				return cur->data;
			}


			int mid = (left_index + right_index) / 2;
			int left_range_end = std::min(mid, right);
			int right_range_begin = std::max(mid + 1, left);

			T left_range = range(cur->left_child, left, left_range_end);
			T right_range = range(cur->right_child, right_range_begin, right);
			return this->operation(left_range, right_range);
		}

		/*
		 * Changes the value at given index to new data
		 */
		void change_value(Segment_Node *cur, int index, T new_data)
		{
			if (cur->left_index == index && cur->right_index == index)
			{
				cur->data = new_data;
			}
			else
			{
				int mid = (cur->left_index + cur->right_index) / 2;
				if (index <= mid)
				{
					this->change_value(cur->left_child, index, new_data);
				}
				else
				{
					this->change_value(cur->right_child, index, new_data);
				}
				cur->data = this->operation(cur->left_child->data, cur->right_child->data);
			}
		}

		/*
		 * Bound checking function
		 */
		inline void check_index(int index)
		{
			if (index >= this->size)
			{
				throw std::invalid_argument("Index is out of bounds");
			}
		}


	public:
		Segment_Tree(std::vector<T> a, T placeholder, std::function<T(T, T)> f)
		{
			this->root = nullptr;
			this->operation = f;
			this->placeholder = placeholder;
			this->size = a.size();
			this->build(a);
		}

		/*
		 * Returns the data obtained by performing given operation
		 * on elements in given range
		 */
		T range_operation(int left, int right)
		{
			if( left > right )
			{
				throw std::invalid_argument("Left should be less than right");
			}
			this->check_index(left);
			this->check_index(right);
			return this->range(this->root, left, right);
		}


		/*
		 * Updates the value at given index to new_data
		 */
		void update(int index, T new_data)
		{
			this->check_index(index);
			this->change_value(this->root, index, new_data);
		}
	};
}