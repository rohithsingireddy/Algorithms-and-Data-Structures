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

	// Insert a node into the end of the list
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

	// Search for a node with a given value in the list
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

	//Merging a list to the end of another list
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
