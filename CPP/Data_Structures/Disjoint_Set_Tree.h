#include "LinkedList.h"
#include <vector>

/*
 * TODO: Input bound checks and more unit tests
 */
template <typename T>
class Disjoint_Set_Tree
{
	// Helper struct for storing individual nodes
	struct Set_node
	{
		int rank;
		LinkedList<Set_node *> *child_pointers;
		T data;
		Set_node *parent;
		Set_node() : rank{0}, parent{this}
		{
			parent->child_pointers = new LinkedList<Set_node *>();
		}

		void insert(T data)
		{
			this->data = data;
			parent->child_pointers->insert(this);
		}
	};

	std::vector<Set_node *> nodes;
	int size = 0;
	/* 
	 * Finds the parent node( representative of set it belongs to) 
	 * of the given node
	 */
	Set_node *find_set(Set_node *x)
	{
		if (x != x->parent)
			x->parent = find_set(x->parent);
		return x->parent;
	}

public:

	/*
	 * Returns the data of parent (or representative ) of index'th node
	 */
	T find_parent(int index)
	{
		return this->find_set(nodes[index])->data;
	}


	/*
	 * Takes the indices of the sets( indices based on insertion order ) as input
	 * Connects sets of i and j if they are disjoint. Otherwise does nothing
	 * Connects j set to i set if both ranks are equal
	 */
	void union_set(int i, int j)
	{
		Set_node *x = nodes[i];
		Set_node *y = nodes[j];
		Set_node *x_parent = find_set(x);
		Set_node *y_parent = find_set(y);

		// printf("%d %d\n", x_parent->data, y_parent->data);
		if (x_parent == y_parent)
		{
			return;
		}

		if (x_parent->rank > y_parent->rank)
		{
			y_parent->parent = x_parent;
			x_parent->child_pointers->merge(y_parent->child_pointers);
		}
		else
		{
			x_parent->parent = y_parent;
			y_parent->child_pointers->merge(x_parent->child_pointers);
			if (x_parent->rank == y_parent->rank)
				y_parent->rank++;
		}
	}


	/*
	 * Takes an object as input
	 * Inserts the object into a seperate disjoint set and 
	 * returns its set number
	 */
	int insert(T data)
	{
		Set_node *node = new Set_node;
		node->insert(data);
		nodes.push_back(node);
		return ++size;
	}

	/*
	 * Takes set number as input
	 * Returns the set elements if the given set number is a parent( or representative) of the set
	 * Otherwise returns an empty vector
	 */
	std::vector<T> get_set_data(int set_number)
	{
		Set_node *s = nodes[set_number];
		Set_node *parent = find_set(s);
		std::vector<T> result;

		if( parent != s )
		{
			return result;
		}

		parent->child_pointers->begin_iteration();
		while (!parent->child_pointers->has_reached_end())
		{
			result.push_back(parent->child_pointers->next()->data);
		}

		return result;
	}

};