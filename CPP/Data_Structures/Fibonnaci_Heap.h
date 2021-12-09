#include <list>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include "LinkedList.h"

/*
 * Some more tests should be done
 * Not an exact implementation. Some liberties were taken
 * Has a large memory footprint
 */

// template <typename T1, typename T2>
// class Fibonnaci_Heap
// {
// private:
// 	struct node
// 	{
// 		node *parent = nullptr;
// 		node *left = nullptr;
// 		node *right = nullptr;
// 		std::list<node *> children;
// 		int degree = 0;
// 		bool mark = false;

// 		T1 key = T1();
// 		T2 data = T2();

// 		void insert_data(T1 key, T2 data)
// 		{
// 			this->key = key;
// 			this->data = data;
// 		}
// 	};
// 	node *min;
// 	int no_of_nodes;
// 	// LinkedList<node *> *root_list;
// 	node *head_node;
// 	node *tail_node;

// 	int index;
// 	std::unordered_map<int, node *> node_dict;

// 	void add_to_root_list(node *created_node)
// 	{
// 	}

// 	/*
// 	 * Helper function to connect two nodes of same degree
// 	 * and create a parent child relationship between them
// 	 * based on their keys.
// 	 */
// 	void link(node *child, node *parent)
// 	{
// 		this->root_list->remove(child);
// 		parent->children.push_back(child);
// 		child->parent = parent;
// 		parent->degree++;
// 		child->mark = false;
// 	}

// 	/*
// 	 * Helper function to take a child of node in heap and
// 	 * add it to root list in case it has lower key than
// 	 * the parent
// 	 */
// 	void cut(node *child, node *parent)
// 	{
// 		if (parent != nullptr && child != nullptr)
// 		{
// 			auto it = std::find(parent->children.begin(), parent->children.end(), child);
// 			if (it != parent->children.end())
// 			{
// 				parent->children.erase(it);
// 			}
// 			parent->degree--;
// 			this->root_list->insert(child);
// 			child->parent = nullptr;
// 			child->mark = false;
// 		}
// 	}

// 	/*
// 	 * Helper function to recursively implement the cut
// 	 * until the min heap property is maintained
// 	 */
// 	void cascading_cut(node *parent)
// 	{
// 		if (parent != nullptr)
// 		{
// 			node *grand_parent = parent->parent;
// 			if (grand_parent != nullptr)
// 			{
// 				if (!parent->mark)
// 				{
// 					parent->mark = true;
// 				}
// 				else
// 				{
// 					this->cut(parent, grand_parent);
// 					this->cascading_cut(grand_parent);
// 				}
// 			}
// 		}
// 	}

// 	/*
// 	 * Helper function to maintain the heap rule
// 	 * in the tree after extracting min node
// 	 */
// 	void consolidate()
// 	{
// 		int n = std::ceil(std::log2(this->no_of_nodes) + 1);
// 		std::vector<node *> array(n, nullptr);

// 		this->root_list->begin_iteration();
// 		while (!this->root_list->has_reached_end())
// 		{
// 			node *current = this->root_list->next();
// 			int current_degree = current->degree;

// 			while (array[current_degree] != nullptr)
// 			{
// 				node *another_node = array[current_degree];
// 				if (current->key > another_node->key)
// 				{
// 					node *temp = current;
// 					current = another_node;
// 					another_node = temp;
// 				}
// 				this->link(another_node, current);
// 				array[current_degree] = nullptr;
// 				current_degree++;
// 			}
// 			array[current_degree] = current;
// 		}

// 		this->min = nullptr;
// 		for (auto current : array)
// 		{
// 			if (current != nullptr)
// 			{
// 				if (this->min == nullptr)
// 				{
// 					this->root_list = new LinkedList<node *>();
// 					this->root_list->insert(current);
// 					this->min = current;
// 				}
// 				else
// 				{
// 					this->root_list->insert(current);
// 					if (current->key < this->min->key)
// 					{
// 						this->min = current;
// 					}
// 				}
// 			}
// 		}
// 	}

// 	/*
// 	 * For pseudo bound checking
// 	 */
// 	inline void check_index(int index)
// 	{
// 		if (this->node_dict.find(index) == this->node_dict.end())
// 		{

// 			throw std::invalid_argument("Node with index is not in the heap\n");
// 		}
// 	}

// public:
// 	Fibonnaci_Heap()
// 	{
// 		this->min = nullptr;
// 		this->no_of_nodes = 0;
// 		this->root_list = new LinkedList<node *>();
// 		this->head_node = nullptr;
// 		this->tail_node = nullptr;
// 		this->index = 0;
// 	}

// 	/*
// 	 * Takes data as input
// 	 * Stores it into the fibonacci heap
// 	 * Returns a number that serves as a representative
// 	 * of the node for access and remove purposes
// 	 */
// 	int insert(T1 key, T2 data)
// 	{
// 		node *created_node = new node();
// 		created_node->insert_data(key, data);

// 		if (this->tail_node == nullptr)
// 		{
// 			this->tail_node = created_node;
// 			this->head_node = this->tail_node;
// 		}
// 		this->tail_node->right = created_node;

// 		created_node->left = this->tail_node;
// 		created_node->right = this->head_node;

// 		this->tail_node = created_node;

// 		if (this->min == nullptr ||
// 			(this->min != nullptr && this->min->key > key))
// 		{
// 			this->min = created_node;
// 		}

// 		// root_list->insert(created_node);
// 		this->no_of_nodes++;
// 		node_dict.insert({this->index++, created_node});
// 		return this->index - 1;
// 	}

// 	/*
// 	 * Connects the argument heap with the calling heap
// 	 * It would not be possible to decrease or delete nodes of
// 	 * argument heap after calling this funciton for now.
// 	 */
// 	void heap_union(Fibonnaci_Heap h1)
// 	{
// 		// this->root_list->merge(h1.root_list);
// 		this->tail_node->right = h1.head_node;
// 		if (this->min == nullptr ||
// 			(h1.min != nullptr && h1.min->key < this->min->key))
// 		{
// 			this->min = h1.min;
// 		}
// 		this->no_of_nodes += h1.no_of_nodes;
// 	}

// 	/*
// 	 * Returns the key and data of the node with the
// 	 * minimum key in the heap and removes it from the heap
// 	 */
// 	std::pair<T1, T2> extract_min()
// 	{
// 		if (this->is_empty())
// 		{
// 			throw std::runtime_error("Accessing an empty heap\n");
// 		}
// 		node *top = this->min;
// 		std::pair<T1, T2> data = std::make_pair(T1(), T2());
// 		if (top != nullptr)
// 		{
// 			for (node *child : top->children)
// 			{
// 			}
// 			this->root_list->remove(top);

// 			// this->min = nullptr;
// 			this->consolidate();

// 			data = std::make_pair(top->key, top->data);
// 		}
// 		this->no_of_nodes--;
// 		return data;
// 	}

// 	/*
// 	 * Takes the index of the node to decrease and the
// 	 * new value to decrease the key.
// 	 * Throws an exception if the new key is greater than current key
// 	 */
// 	void decrease_key(int index_of_key, T1 new_value)
// 	{
// 		this->check_index(index_of_key);
// 		node *node_pointer = this->node_dict[index_of_key];
// 		if (new_value > node_pointer->key)
// 		{
// 			throw std::runtime_error("Cannot overwrite key with a higher value\n");
// 		}

// 		if (node_pointer != nullptr)
// 		{
// 			node_pointer->key = new_value;
// 			node *parent = node_pointer->parent;

// 			if (parent != nullptr && node_pointer->key < parent->key)
// 			{
// 				this->cut(node_pointer, parent);
// 				this->cascading_cut(parent);
// 			}

// 			if (this->min == nullptr)
// 			{
// 				this->min = node_pointer;
// 			}
// 			if (node_pointer->key < this->min->key)
// 			{
// 				this->min = node_pointer;
// 			}
// 		}
// 	}

// 	/*
// 	 * Deletes a given index'th node from the tree
// 	 * Takes a index of node to be deleted and lowest possible
// 	 * value for the key type
// 	 */
// 	void delete_node(int node_index, T1 lowest_key_possible)
// 	{
// 		this->check_index(node_index);
// 		this->decrease_key(node_index, lowest_key_possible);
// 		this->extract_min();
// 		this->node_dict.erase(this->node_dict.find(node_index));
// 	}

// 	/*
// 	 * Returns true if the heap is empty
// 	 */
// 	bool is_empty()
// 	{
// 		return this->no_of_nodes == 0;
// 	}
// };

template <typename T1, typename T2>
class Fibonnaci_Heap
{
private:
	struct Fib_node
	{
		Fib_node *parent = nullptr;
		Fib_node *left = nullptr;
		Fib_node *right = nullptr;
		std::list<Fib_node *> children;
		Fib_node *child_head = nullptr;
		Fib_node *child_tail = nullptr;

		int degree = 0;
		bool mark = false;

		T1 key = T1();
		T2 data = T2();

		Fib_node(T1 key, T2 data)
		{
			this->key = key;
			this->data = data;
		}

		void add_child(Fib_node* child)
		{
			this->children.push_back(child);
			// if( this->child_head == nullptr )
			// {
			// 	this->child_head = child;
			// 	this->child_tail = this->child_head;

			// 	child->left = child;
			// 	child->right = child;
			// }
			// else
			// {
			// 	this->child_tail->right = child;
			// 	this->child_head->left = child;
				
			// 	child->left = this->child_tail;
			// 	child->right = this->child_head;

			// 	this->child_tail = child;

			// }
			child->parent = this;
			this->degree++;
			child->mark = false;
		}

		void remove_child(Fib_node* child)
		{
			if( this->child_head != nullptr )
			{
				child->left->right = child->right;
				child->right->left = child->left;

				if( child == this->child_head )
				{
					child_head = child->right;
				}

				if( child == this->child_tail )
				{
					child_tail = child->left;
				}
			}
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
	}

	/*
	 * Helper function to remove a node from list
	 */
	void remove_from_root_list(Fib_node *node)
	{
		node->left->right = node->right;
		node->right->left = node->left;

		if( node == this->head_node )
		{
			this->head_node = node->right;
		}

		if( node == this->tail_node )
		{
			this->tail_node = node->left;
		}

		// node->right = node;
		// node->left = node;
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
	void link( Fib_node *child, Fib_node *parent)
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
	 * Helper function to maintain the heap rule
	 * in the tree after extracting min node
	 */ 
	void consolidate()
	{
		int n = std::ceil(std::log2(this->no_of_nodes) + 1);
		Fib_node **temp_array = new Fib_node*[n];

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

				if (node_1->key > node_2->key)
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
			if( temp_array[i] != nullptr )
			{
				if( this->min == nullptr )
				{
					this->reset_root_list();
					this->add_to_root_list(temp_array[i]);
					this->min = temp_array[i];
				}
				else
				{
					this->add_to_root_list(temp_array[i]);
					if( this->min->key > temp_array[i]->key )
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
	 * TODO: Implement union
	 */
	void fib_union(Fibonnaci_Heap heap) {}

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
			for (Fib_node *child : top->children)
			{
				this->add_next_to_node(current, child);
				current = child;
			}
			//Fib_node* child = top->child_head;
			//std::vector<Fib_node*> children;

			// while( top->child_head != top->child_tail )
			// {
			// 	top->remove_child(child);
			// 	// this->add_next_to_node(current, child);
			// 	// current = child;
			// 	// child = top->child_head;
			// }

			// if( child != nullptr )
			// {
			// 	this->add_next_to_node(current, child);
			// }

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
		}
		else{
			printf("null\n");
		}

		this->no_of_nodes--;

		return data;
	}

	bool is_empty()
	{
		return this->no_of_nodes == 0;
	}
};