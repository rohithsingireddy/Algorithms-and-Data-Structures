

template<typename T>
class QueueArray{
	
	// Tail points to the element after last inserted element
	// Head points to the element that should be returned
	private:
		int head, tail, max_size, current_size;
		T* queue;
		bool is_empty, is_full;
	
	public:
		QueueArray(int N) {
			head = 0;
			tail = 0;
			max_size = N;
			current_size = 0;
			queue = new int[max_size];
			is_empty = true;
			is_full = false;
		}

		void enqueue(T value) {

			if( is_full ) {
				throw "Queue is full.\n";
			}

			queue[tail] = value;
			tail += 1;
			tail %= max_size;
			is_full = ( head == tail );

			//If enqueue is successful, queue is not empty.
			is_empty = false;

			
		}

		T dequeue() {
			if( is_empty ) {
				throw "Queue is empty.\n";
			}
			T element = queue[head];
			head = (head+1) % max_size;
			is_empty = ( tail == head );

			//If dequeue is successful, queue is not full.
			is_full = false;
	
			return element;
		}

		bool isFull() const {
			return is_full;
		}

		bool isEmpty() const {
			return is_empty;
		}


	
};
