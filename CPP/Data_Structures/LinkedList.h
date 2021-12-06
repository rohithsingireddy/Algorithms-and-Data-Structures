#include <stdexcept>

template <typename T>
struct LinkedNode
{
	LinkedNode<T> *prev = nullptr, *next = nullptr;
	T val = T();
	LinkedNode(T v) : val{v} {}
};

template <typename T>
struct LinkedList
{

private:
	LinkedNode<T> *head = nullptr, *tail = nullptr;
	LinkedNode<T> *current = nullptr;

public:
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
		if (temp == nullptr)
		{
			return;
		}
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
			// delete temp;
		}
	}

	/*
	 * Takes a value that is to be removed from the list
	 * Returns null
	 */
	void remove(T value)
	{
		remove(search(value));
	}

	/*
	 * Inititalizes current
	 */
	void begin_iteration(bool reverse = false)
	{
		if (reverse)
		{
			current = tail;
		}
		else
		{
			current = head;
		}
	}

	/*
	 * Returns value of next node in the list
	 * Throws an runtime_error if next node does not exist
	 */
	T next()
	{
		// printf("some");
		LinkedNode<T> *temp = current;
		if (current != nullptr)
		{
			current = current->next;
		}
		else
		{
			throw std::runtime_error("Trying to use a null pointer");
		}
		return temp->val;
	}

	/*
	 * Returns value of next node in the list
	 * Throws an runtime_error if previous node does not exist
	 */
	T prev()
	{
		// printf("some");
		LinkedNode<T> *temp = current;
		if (current != nullptr)
		{
			current = current->prev;
		}
		else
		{
			throw std::runtime_error("Trying to use a null pointer");
		}
		return temp->val;
	}


	/*
	 * Returns true if current reached end while iterating
	 */
	bool has_reached_end()
	{
		return current == nullptr;
	}

	/*
	 * Merges two disjoint list
	 * Returns the pointer to the list that called this method after merging
	 * TODO: Some more checks to be done before merging
	 */
	LinkedList<T> *merge(LinkedList<T> *b)
	{
		if (b->head == nullptr)
			return this;
		else if (head == nullptr || tail == nullptr)
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
