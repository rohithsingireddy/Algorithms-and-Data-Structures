#include <iostream>

template <typename T = int>
struct LinkedNode
{
	LinkedNode<T> *prev = nullptr, *next = nullptr;
	T val = T();
	LinkedNode(T v) : val{v} {}
};

template <typename T = int>
struct LinkedList
{
	LinkedNode<T> *head = nullptr, *tail = nullptr;
	LinkedList() {}

	/*
	 * Takes a value and inserts it at the end of list
	 * Returns null
	 */ 
	void insert(T v)
	{
		if (head == nullptr)
		{
			head = new LinkedNode<T>(v);
			tail = head;
		}
		else
		{
			LinkedNode<T> *temp = new LinkedNode<T>(v);
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}

	
	/*
	 * Takes a value and searches for the node that has the value
	 * Returns the node if present else null
	 */
	LinkedNode<T> *search(T val)
	{
		auto temp = head;
		while (temp != nullptr)
		{
			if (temp->val == val)
				return temp;
			temp = temp->next;
		}
		return nullptr;
	}


	
	/*
	 * Takes a node that is to be removed from the list
	 * Returns null
	 */
	void remove(LinkedNode<T> *temp)
	{
		if (temp == head)
		{
			head = head->next;
			if (head != nullptr)
				head->prev = nullptr;
		}
		else if (temp == tail)
		{
			tail = tail->prev;
			if (tail != nullptr)
				tail->next = nullptr;
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
		}
	}

	
	/*
	 * Prints the  content of the list in forward
	 * Returns null
	 */
	void print()
	{
		auto temp = head;
		while (temp)
		{
			std::cout << temp->val << ' ';
			temp = temp->next;
		}
		std::cout << '\n';
	}

	
	/*
	 * Merges two disjoint list
	 * Returns the pointer to the list that called this method after merging
	 */
	LinkedList<T> *merge(LinkedList<T> *b)
	{
		if (b->head == nullptr)
			return this;
		else if (head == nullptr)
			return b;
		else
		{
			this->tail->next = b->head;
			b->head->prev = this->tail;
			this->tail = b->tail;
			return this;
		}
	}
};
