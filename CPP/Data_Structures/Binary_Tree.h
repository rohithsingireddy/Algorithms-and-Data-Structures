#ifndef BIN_TREE_INCLUDE_GUARD
#define BIN_TREE_INCLUDE_GUARD

#include <functional>
#include <stdexcept>
namespace Data_Structures
{
	// TODO: Implement inorder, preorder and postorder traversals iteratively
	template <typename T1, typename T2>
	class Binary_Tree
	{
		struct binary_node
		{
			binary_node *parent;
			binary_node *left;
			binary_node *right;
			T1 key;
			T2 data;

			binary_node(T1 key, T2 data)
			{
				this->parent = nullptr;
				this->left = nullptr;
				this->right = nullptr;
				this->key = key;
				this->data = data;
			}
		};

		binary_node *root;

		/*
		 * Takes two subtrees and replaces one with other sub tree
		 */
		void transplant(binary_node *replaced, binary_node *replacement)
		{
			auto parent = replaced->parent;
			if (parent == nullptr)
			{
				root = replacement;
			}
			else if (parent->left == replaced)
				parent->left = replacement;
			else
				parent->right = replacement;

			if (replacement != nullptr)
				replacement->parent = parent;
		}

		/* 
		 * Removes the given node from the sub-tree and readjusts the tree
	 	 */
		void remove(binary_node *node)
		{
			if (node == nullptr)
			{
				return;
			}
			if (node->left == nullptr)
			{
				transplant(node, node->right);
			}
			else if (node->right == nullptr)
			{
				transplant(node, node->left);
			}
			else
			{
				auto suc = successor(node);
				if (suc->parent != node)
				{
					transplant(suc, suc->right);
					suc->right = node->right;
					suc->right->parent = suc;
				}
				transplant(node, suc);
				suc->left = node->left;
				suc->left->parent = suc;
			}
			delete node;
		}

		/* 
		 * Finds the leftmost ( also know as lowest node) node of the subtree
	 	 * Returns a pointer to that node
	 	 */
		binary_node *min_of_tree(binary_node *temp)
		{
			if (temp != nullptr)
			{
				while (temp->left)
				{
					temp = temp->left;
				}
			}
			return temp;
		}

		/*
	 	 * Finds the rightmost( also known as greatest node )node of the subtree
	 	 * Returns a pointer to that node
	 	 */
		binary_node *max_of_tree(binary_node *temp)
		{
			if (temp != nullptr)
			{
				while (temp->right)
				{
					temp = temp->right;
				}
			}
			return temp;
		}

		/*
	 	 * Takes a given node and gives the smallest node which is greater than its
	 	 * Returns null if no node that satisifes the above exists
	 	 */
		binary_node *successor(binary_node *temp)
		{
			if (temp->right != nullptr)
			{
				return this->min_of_tree(temp->right);
			}
			binary_node *parent = temp->parent;
			while (parent != nullptr && parent->right == temp)
			{
				temp = parent;
				parent = temp->parent;
			}
			return parent;
		}

		/*
	 	 * Takes a given node and gives the largest node which is smaller than its key
	 	 * Returns null if no node that satisfies the above exists
	 	 */
		binary_node *predecessor(binary_node *temp)
		{
			if (temp->left != nullptr)
			{
				return this->max_of_tree(temp->left);
			}
			binary_node *parent = temp->parent;
			while (parent != nullptr && parent->left == temp)
			{
				temp = parent;
				parent = temp->parent;
			}
			return parent;
		}

		/*
	 	 * Searches for a node with the given value
		 * Returns a binary_node pointer if node exists else null
		 */
		binary_node *search_tree(T1 key)
		{
			auto temp = root;
			while (temp)
			{
				if (temp->key == key)
					return temp;
				else if (key < temp->key)
					temp = temp->left;
				else
					temp = temp->right;
			}
			return temp;
		}

	public:
		Binary_Tree()
		{
			root = nullptr;
		}

		~Binary_Tree()
		{
			std::function<void(binary_node*)> delete_node = 
			[&delete_node](binary_node* current) -> void
			{
				if( current != nullptr )
				{
					delete_node(current->left);
					delete_node(current->right);
					delete current;
				}
			};

			delete_node(this->root);
		}

		/*
		 * Takes a value and inserts into the binary tree
		 * Returns null
		 */
		void insert(T1 key, T2 data)
		{
			binary_node *temp = root, *trailing_temp = root;
			while (temp)
			{
				trailing_temp = temp;
				if (key < temp->key)
					temp = temp->left;
				else
					temp = temp->right;
			}

			binary_node *node = new binary_node(key, data);
			node->parent = trailing_temp;

			if (trailing_temp == nullptr)
				root = node;
			else if (key <= trailing_temp->key)
				trailing_temp->left = node;
			else
				trailing_temp->right = node;
		}

		/*
		 * Removes a node with a given value if it exists
		 * Ohterwise does nothing
		 */
		void remove(T1 key)
		{
			remove(this->search_tree(key));
		}

		/*
		 * Search for a key in the tree
		 * Returns key and data as a pair if key is present 
		 * Throws an exception if key is not in tree
		 */
		std::pair<T1, T2> search(T1 key)
		{
			binary_node *node = this->search_tree(key);
			if (node == nullptr)
			{
				throw std::runtime_error("Key is not present in tree");
			}
			else
			{
				return std::make_pair(node->key, node->data);
			}
		}

		/*
		 * Returns the data of the lower bound of the given key provided
		 * that the key is present in the tree.
		 * If lower bound does not exist, it returns itself
		 * If key is not present, an exception is thrown
		 */
		std::pair<int, int> lower_bound(T1 key)
		{
			binary_node *node = this->search_tree(key);
			binary_node *lb_node = this->predecessor(node);
			if (lb_node == nullptr)
			{
				lb_node = node;
			}
			return std::make_pair(lb_node->key, lb_node->data);
		}

		/*
		 * Returns the data of the upper bound of the given key provided
		 * that the key is present in the tree
		 * If lower bound does not exist, it returns itself
		 * If key is not present, an exception is thrown
		 */
		std::pair<int, int> upper_bound(T1 key)
		{
			binary_node *node = this->search_tree(key);
			binary_node *ub_node = this->successor(node);
			if (ub_node == nullptr)
			{
				ub_node = node;
			}
			return std::make_pair(ub_node->key, ub_node->data);
		}
	};
}

#endif