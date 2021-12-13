#include <stdexcept>
#include <vector>

namespace Data_Structures
{
    class Fenwick_Tree
    {
    private:
        long long *array;
        long long size;

        /*
         * Gets the integer value of the least significant bit whose value is 1
         * If index is 188( 10111100 ), then the return value is 4( 100 )
         */
        inline long long lsb(long long index) const
        {
            return index & -index;
        }

        /*
         * Returns the last index whose value is added to value at given index
         */
        inline long long prev(long long index) const
        {
            return index - lsb(index);
        }

        /*
         * Returns the next index where the value at the current index to be added
         */
        inline long long next(long long index) const
        {
            return index + lsb(index);
        }

        /*
         * Index bound checking. Throws an exception if index is out of bound
         */
        inline void check_index(long long index)
        {
            if (index < 0 || index >= this->size)
            {
                throw std::invalid_argument("Index out of range");
            }
        }

    public:
        Fenwick_Tree(long long s)
        {
            this->size = s + 1;
            array = new long long[this->size];
        }

        /*
         * Converts and stores the given vector array as a Fenwick Array
         */
        Fenwick_Tree(std::vector<long long> given_array)
        {
            this->size = given_array.size() + 1;
            array = new long long[this->size];
            for (long long i = 0; i < given_array.size(); i++)
            {
                this->array[i + 1] = given_array[i];
            }

            for (long long i = 1; i < this->size; i++)
            {
                long long next_index = this->next(i);
                if (next_index < this->size)
                {
                    this->array[next_index] += this->array[i];
                }
            }
        }

        ~Fenwick_Tree()
        {
            delete[] array;
        }

        /*
         * Adds the value to elements at indices given that two selected
         * consecutive indices differ from each other by one bit
         * In other words, it adds value to element at index
         */
        void add(long long index, long long value)
        {
            index++;
            this->check_index(index);
            for (index; index < this->size; index = this->next(index))
            {
                this->array[index] += value;
            }
        }

        /*
         * Inserts the value at an index
         */
        void insert(long long index, long long value)
        {
            this->add(index, value - this->get_value_at(index));
        }

        /*
         * Gets the sum of all elements between left index (inclusive )
         * and right index( exclusive )
         */
        long long range_sum(long long left, long long right)
        {
            if( left > right )
            {
                std::swap(left, right);
            }
            this->check_index(left);
            this->check_index(right);
            long long sum = 0;
            for (right; right > left; right = this->prev(right))
            {
                sum += this->array[right];
            }

            for (left; left > right; left = this->prev(left))
            {
                sum -= this->array[left];
            }

            return sum;
        }

        /*
         * Gets the sum between first element and (index - 1)'th element
         */
        long long prefix_sum(long long index)
        {
            this->check_index(index);
            long long sum = 0;
            for (index; index > 0; index = this->prev(index))
            {
                sum += this->array[index];
            }
            return sum;
        }

        /*
         * Gets the value at the given index
         */
        long long get_value_at(long long index)
        {
            return this->range_sum(index, index + 1);
        }

        /*
         * Returns the array used for construction
         */
        std::vector<long long> get_array()
        {
            std::vector<long long> result(this->size - 1);

            long long* array = new long long[this->size];

            for( long long i = 0; i < this->size; i++ )
            {
                array[i] = this->array[i];
            }

            for (long long i = this->size - 1; i > 0; i--)
            {
                long long next_index = this->next(i);
                if (next_index < this->size)
                {
                    array[next_index] -= array[i];
                }
            }

            for( int i = 1; i < this->size; i++ )
            {
                result[i - 1] = array[i];
            }
            delete[] array;

            return result;
        }


    };
}