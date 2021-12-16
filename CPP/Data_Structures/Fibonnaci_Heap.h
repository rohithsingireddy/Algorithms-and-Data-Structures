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

/**
 * Not an exact implementation. Some liberties were taken
 * Has a large memory footprint
 * Can be made more robust.
 * Some more tests should be done
 * Had to abandon double linked list implementation
 */

template <typename T1, typename T2>
class Fibonnaci_Heap
{
private:
	struct node
	{
		node *parent = nullptr;
		std::unordered_set<node *> children;
		int degree = 0;
		bool mark = false;

		T1 key = T1();
		T2 data = T2();

		void insert_data(T1 key, T2 data)
		{
			this->key = key;
			this->data = data;
		}
	};
	node *min;
	int no_of_nodes;
	LinkedList<node *> *root_list;

	int index;
	std::unordered_map<int, node *> node_dict;

	void set_min_node(node *min_node)
	{
		this->min = min_node;
	}

	node *get_min_node()
	{
		return this->min;
	}

	LinkedList<node *> *get_root_list()
	{
		return this->root_list;
	}

	/**
	 * Helper function to connect two nodes of same degree
	 * and create a parent child relationship between them
	 * based on their keys.
	 */
	void link(node *child, node *parent)
	{
		this->root_list->remove(child);
		parent->children.insert(child);
		child->parent = parent;
		parent->degree++;
		child->mark = false;
	}

	/**
	 * Helper function to take a child of node in heap and
	 * add it to root list in case it has lower key than
	 * the parent
	 */
	void cut(node *child, node *parent)
	{
		parent->children.erase(child);
		parent->degree--;
		this->root_list->insert(child);
		child->parent = nullptr;
		child->mark = false;
	}

	/**
	 * Helper function to recursively implement the cut
	 * until the min heap property is maintained
	 */
	void cascading_cut(node *parent)
	{
		node *grand_parent = parent->parent;
		if (grand_parent != nullptr)
		{
			if (!parent->mark)
			{
				parent->mark = true;
			}
			else
			{
				this->cut(parent, grand_parent);
				this->cascading_cut(grand_parent);
			}
		}
	}

	/**
	 * Helper function to maintain the heap rule
	 * in the tree after extracting min node
	 */
	void consolidate()
	{
		std::unordered_map<int, node *> degree_dict;
		this->root_list->begin_iteration();
		while (!this->root_list->has_reached_end())
		{
			node *current = this->root_list->next();
			int current_degree = current->degree;

			if (degree_dict.find(current_degree) != degree_dict.end())
			{
				degree_dict.insert({current_degree, nullptr});
			}

			while (degree_dict[current_degree] != nullptr)
			{
				node *another_node = degree_dict[current_degree];
				if (current->key > another_node->key)
				{
					std::swap(current, another_node);
				}
				this->link(another_node, current);
				degree_dict[current_degree] = nullptr;
				current_degree++;

				if (degree_dict.find(current_degree) != degree_dict.end())
				{
					degree_dict.insert({current_degree, nullptr});
				}
			}
			degree_dict[current_degree] = current;
		}

		this->min = nullptr;
		for (auto current : degree_dict)
		{
			if (current.second != nullptr)
			{
				if (this->min == nullptr)
				{
					this->root_list = new LinkedList<node *>();
					this->root_list->insert(current.second);
					this->min = current.second;
				}
				else
				{
					this->root_list->insert(current.second);
					if (current.second->key < this->min->key)
					{
						this->min = current.second;
					}
				}
			}
		}
	}

	/**
	 * For pseudo bound checking
	 */
	inline void check_index(int index)
	{
		if (index >= this->index)
		{

			throw std::invalid_argument("Node with index is not in the heap\n");
		}
	}

public:
	Fibonnaci_Heap()
	{
		this->min = nullptr;
		this->no_of_nodes = 0;
		this->root_list = new LinkedList<node *>();
		this->index = 0;
	}

	~Fibonnaci_Heap()
	{
		for (auto i : this->node_dict)
		{
			delete i.second;
		}
	}

	/**
	 * Takes data as input
	 * Stores it into the fibonacci heap
	 * Returns a number that serves as a representative
	 * of the node for access and remove purposes
	 */
	int insert(T1 key, T2 data)
	{
		node *created_node = new node();
		created_node->insert_data(key, data);
		if (this->min == nullptr ||
			(this->min != nullptr && this->min->key > key))
		{
			this->min = created_node;
		}

		root_list->insert(created_node);
		this->no_of_nodes++;
		this->node_dict.insert({this->index++, created_node});
		return this->index - 1;
	}

	/**
	 * Connects the argument heap with the calling heap
	 * It would not be possible to decrease or delete nodes of
	 * argument heap after calling this funciton for now.
	 */
	void heap_union(Fibonnaci_Heap h1)
	{
		this->root_list->merge(h1.root_list);
		if (this->min == nullptr ||
			(h1.min != nullptr && h1.min->key < this->min->key))
		{
			this->min = h1.min;
		}
		this->no_of_nodes += h1.no_of_nodes;
	}

	/**
	 * Returns the key and data of the node with the
	 * minimum key in the heap and removes it from the heap
	 */
	std::pair<T1, T2> extract_min()
	{
		if (this->is_empty())
		{
			throw std::runtime_error("Accessing an empty heap\n");
		}
		node *top = this->min;
		std::pair<T1, T2> data = std::make_pair(T1(), T2());
		if (top != nullptr)
		{
			for (node *child : top->children)
			{
				this->root_list->insert(child);
			}
			this->root_list->remove(top);

			this->consolidate();

			data = std::make_pair(top->key, top->data);
			// delete top // Segementation fault because of this
		}
		this->no_of_nodes--;
		return data;
	}

	/**
	 * Takes the index of the node to decrease and the
	 * new value to decrease the key.
	 * Throws an exception if the new key is greater than current key
	 */
	void decrease_key(int index_of_key, T1 new_value)
	{
		this->check_index(index_of_key);
		node *node_pointer = this->node_dict[index_of_key];
		if (new_value > node_pointer->key)
		{
			throw std::runtime_error("Cannot overwrite key with a higher value\n");
		}

		node_pointer->key = new_value;
		node *parent = node_pointer->parent;

		if (parent != nullptr && node_pointer->key < parent->key)
		{
			this->cut(node_pointer, parent);
			this->cascading_cut(parent);
		}

		if (node_pointer->key < this->min->key)
		{
			this->min = node_pointer;
		}
	}

	/**
	 * Deletes a given index'th node from the tree
	 * Takes a index of node to be deleted and lowest possible
	 * value for the key type
	 */
	void delete_node(int node_index, T1 lowest_key_possible)
	{
		this->decrease_key(node_index, lowest_key_possible);
		this->extract_min();
	}

	/**
	 * Returns true if the heap is empty
	 */
	bool is_empty()
	{
		return this->no_of_nodes == 0;
	}
};

#endif