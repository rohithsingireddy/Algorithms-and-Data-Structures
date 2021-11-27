#include <iostream>

template<typename T>
class QueueArray{
	
	/*
	 * Tail points to the element after last inserted element
	 * Head points to the element that should be returned
	 */ 
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


		/*
	 	* Takes a value and inserts it into back of the queue
	 	* Returns null
	 	*/		
		void enqueue(T value) {

			if( is_full ) {
				throw std::runtime_error("Invalid due to queue being full\n");
			}

			queue[tail] = value;
			tail += 1;
			tail %= max_size;
			is_full = ( head == tail );

			//If enqueue is successful, queue is not empty.
			is_empty = false;

			
		}

		
		/*
		* Returns and removes the element at the front of the list
		* Returns element at the front of the list
		*/

		T dequeue() {
			if( is_empty ) {
				throw std::runtime_error("Invalid operation due to queue being empty\n");
			}
			T element = queue[head];
			head = (head+1) % max_size;
			is_empty = ( tail == head );

			//If dequeue is successful, queue is not full.
			is_full = false;
	
			return element;
		}
		

		/*
		* Returns true if the queue is full
		* else false
		*/
		bool isFull() const {
			return is_full;
		}

			
		/*
		* Returns true if the queue is empty
		* else false
		*/
		bool isEmpty() const {
			return is_empty;
		}


	
};
