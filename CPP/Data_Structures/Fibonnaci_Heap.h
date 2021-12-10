#ifndef FIBONNACI_HEAP_GUARD
#define FIBONNACI_HEAP_GUARD

#include <list>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "LinkedList.h"

/*
 * Segmentation fault when used in some programs with pointers as data
 * Not an exact implementation. Some liberties were taken
 * Has a large memory footprint
 * Can be made more robust
 */


template <typename T1, typename T2>
class Fibonnaci_Heap
{
private:
	struct Fib_node
	{
		Fib_node *parent = nullptr;
		Fib_node *left = nullptr;
		Fib_node *right = nullptr;
		// std::list<Fib_node *> children;
		std::unordered_set<Fib_node *> children;

		int degree = 0;
		bool mark = false;

		T1 key = T1();
		T2 data = T2();

		Fib_node(T1 key, T2 data)
		{
			this->key = key;
			this->data = data;
		}

		void add_child(Fib_node *child)
		{
			this->children.insert(child);
			child->parent = this;
			this->degree++;
			child->mark = false;
		}

		void remove_child(Fib_node *child)
		{
			this->children.erase(child);
			child->parent = nullptr;
			this->degree--;
			child->mark = false;
		}
	};

	Fib_node *min, *head_node, *tail_node;
	int no_of_nodes;

	int index;
	std::unordered_map<int, Fib_node *> node_dict;

	/*
	 * Helper function to add a node to root list
	 */
	void add_to_root_list(Fib_node *node)
	{
		if (this->tail_node == nullptr)
		{
			this->tail_node = node;
			this->head_node = node;

			node->left = node;
			node->right = node;

			return;
		}

		this->tail_node->right = node;
		this->head_node->left = node;

		node->left = this->tail_node;
		node->right = this->head_node;

		this->tail_node = node;
	}

	/*
	 * Helper function to add a node to next to another node
	 */
	void add_next_to_node(Fib_node *current, Fib_node *child)
	{
		child->right = current->right;
		child->left = current;

		current->right->left = child;
		current->right = child;

		if( current == this->tail_node )
		{
			this->tail_node = child;
		}
	}

	/*
	 * Helper function to remove a node from list
	 */
	void remove_from_root_list(Fib_node *node)
	{
		node->left->right = node->right;
		node->right->left = node->left;

		if (node == this->head_node)
		{
			this->head_node = node->right;
		}

		if (node == this->tail_node)
		{
			this->tail_node = node->left;
		}
	}

	/*
	 * Helper function to reset the root list
	 */
	void reset_root_list()
	{
		this->head_node = nullptr;
		this->tail_node = nullptr;
	}

	/*
	 * Helper function to connect two nodes of same degree
	 * and create a parent child relationship between them
	 * based on their keys.
	 */
	void link(Fib_node *child, Fib_node *parent)
	{
		this->remove_from_root_list(child);
		parent->add_child(child);
	}

	/*
	 * Inline function checking for existance of index in node_dict
	 */
	inline void check_index(int index)
	{
		if (this->node_dict.find(index) == this->node_dict.end())
		{
			throw std::invalid_argument("Node with index is not in heap\n");
		}
	}

	/*
	 * Helper function to cut the child from parent node and 
	 * add it to root list
	 */
	void cut(Fib_node *child, Fib_node *parent)
	{
		if( parent != nullptr && child != nullptr )
		{
			parent->remove_child(child);
			this->add_to_root_list(child);
		}
	}

	/*
	 * Helper function to recursively call the cut function until
	 * the heap rule is maintained
	 */
	void cascading_cut(Fib_node *child)
	{
		if( child != nullptr && child->parent != nullptr )
		{
			if( child-> mark )
			{
				this->cut( child, child->parent);
				this->cascading_cut(child->parent);
			}
			else
			{
				child->mark = true;
			}
		}
	} 

	/*
	 * Helper function to maintain the heap rule
	 * in the tree after extracting min node
	 */
	void consolidate()
	{
		int n = std::ceil(std::log2(this->no_of_nodes) + 1);
		Fib_node **temp_array = new Fib_node *[n];

		for (int i = 0; i < n; i++)
		{
			temp_array[i] = nullptr;
		}

		Fib_node *current = this->head_node;
		do
		{
			Fib_node *node_1 = current;
			int degree = node_1->degree;

			while (temp_array[degree] != nullptr)
			{
				Fib_node *node_2 = temp_array[degree];

				if (node_1->key > node_2->key) // Segmentation fault occurs here
				{
					Fib_node *temp = node_1;
					node_1 = node_2;
					node_2 = temp;
				}
				this->link(node_2, node_1);

				temp_array[degree] = nullptr;
				degree++;
			}
			temp_array[degree] = node_1;

			current = current->right;

		} while (current != this->head_node);

		this->min = nullptr;
		for (int i = 0; i < n; i++)
		{
			if (temp_array[i] != nullptr)
			{
				if (this->min == nullptr)
				{
					this->reset_root_list();
					this->add_to_root_list(temp_array[i]);
					this->min = temp_array[i];
				}
				else
				{
					this->add_to_root_list(temp_array[i]);
					if (this->min->key > temp_array[i]->key)
					{
						this->min = temp_array[i];
					}
				}
			}
		}
	}

public:
	Fibonnaci_Heap()
	{
		this->min = nullptr;
		this->tail_node = nullptr;
		this->head_node = nullptr;
		this->index = 0;
		this->no_of_nodes = 0;
	}

	/*
	 * Takes a key and data as input
	 * Stores in Fibonacci Heap
	 * Returns a number that serves as a representative
	 */
	int insert(T1 key, T2 data)
	{
		Fib_node *created_node = new Fib_node(key, data);
		this->add_to_root_list(created_node);

		if (this->min == nullptr || this->min->key > key)
		{
			this->min = created_node;
		}

		this->no_of_nodes++;
		node_dict.insert({this->index++, created_node});

		return this->index - 1;
	}

	/*
	 * TODO: Elements of node_dict can be added albeit with updated indices 
	 * and linear complexity.
	 * 
	 * Connects the given heap to heap object that called this function
	 * Because of the way decrease_key and delete accept input, they cannot
	 * be used on the members of argument heap after calling this function
	 * 
	 */
	void fib_union(Fibonnaci_Heap& heap) 
	{
		heap.tail_node->right = this->head_node;

		this->tail_node->right = heap.head_node;
		heap.head_node->left = this->tail_node;

		this->head_node->left = heap.tail_node;
		this->tail_node = heap.tail_node;

		if( this->min == nullptr || this->min->key > heap.min->key )
		{
			this->min = heap.min;
		}
		this->no_of_nodes += heap.no_of_nodes;
	}

	/*
	 * Returns the key and value of the node with minimu
	 * key in the heap.
	 */
	std::pair<T1, T2> extract_min()
	{
		if (this->is_empty())
		{
			throw std::runtime_error("Heap is empty\n");
		}

		Fib_node *top = this->min;
		std::pair<T1, T2> data = std::make_pair(T1(), T2());

		if (top != nullptr)
		{
			data = std::make_pair(top->key, top->data);
			Fib_node *current = top;
			for (auto child : top->children)
			{
				this->add_next_to_node(current, child);
				current = child;
			}

			this->remove_from_root_list(top);

			if (top == top->right)
			{
				this->min = nullptr;
			}
			else
			{
				this->min = top->right;
				this->consolidate();
			}
			delete top;
			this->no_of_nodes--;
		}
		else
		{
			throw std::runtime_error("Heap is empty\n");
		}

		return data;
	}

	/*
	 * Takes the index of the node to decrease and new key
	 * and decreases the key of index'th inserted element
	 * Throws an exception if new key is greater than current key
	 */
	void decrease_key(int index, T1 new_key)
	{
		this->check_index(index);
		Fib_node *node = this->node_dict[index];

		if (node != nullptr)
		{
			if (new_key > node->key)
			{
				throw std::runtime_error("Cannot overwrite key with a higher value\n");
			}

			node->key = new_key;
			
			if( node->parent != nullptr && node->parent->key > node->key )
			{
				this->cut( node, node->parent);
				this->cascading_cut(node->parent);
			}

			if( this->min == nullptr || this->min->key > node->key )
			{
				this->min = node;
			}

		}
	}


	/*
	 * Deletes a node from the heap
	 * Takes index of node and min possible value for a key as input
	 */
	void delete_node(int index, T1 min_possible_key)
	{
		this->check_index(index);
		this->decrease_key(index, min_possible_key);
		this->extract_min();
	}

	/*
	 * Returns true if heap is empty
	 */
	bool is_empty()
	{
		return this->no_of_nodes == 0;
	}
};

#endif