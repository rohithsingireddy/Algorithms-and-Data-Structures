#include <math.h>
#include <limits.h>
#include <stdexcept>
#include "LinkedList.h"

/* 
 * Currently only works for numbers and chars
 * Custom classes that overload *, == and double can use the class
 * Uses multiplication method for hashing and chained lists for storing
 */
template <typename T>
class Hash_Array
{
private:
    unsigned long long max_size = 1024; //2^10
    const double A = 0.61803398875;     // golden ratio - 1
    LinkedList<T> **data;

    /*
     * Returns a hash of given array using the multiplication method 
     * in 'Introduction to Algorithms' by CLRS
     * Currently only works for integers and chars
     */
    unsigned long long hash(T value)
    {
        /*
         * TODO: Make it work for a generic object and type
         */
        double fraction = (A * (double)value) - std::floor(A * value);
        return (unsigned long long)((double)max_size * fraction);
    }

public:
    Hash_Array()
    {
        data = new LinkedList<T> *[max_size];
    }

    Hash_Array(unsigned long long size)
    {
        if (size >= INT64_MAX)
        {
            throw std::invalid_argument("The size cannot be represented\n");
        }
        max_size = size;
        data = new LinkedList<T> *[max_size];
    }

    /*
     * Inserts a value into the list with hash index
     */
    void insert(T value)
    {
        unsigned long long key = hash(value);
        if (data[key] == nullptr)
        {
            data[key] = new LinkedList<T>();
        }
        data[key]->insert(value);
    }

    /*
     * Checks whether a value exists in the hash list
     */
    bool contains(T value)
    {
        unsigned long long key = hash(value);
        if (data[key] == nullptr)
        {
            return false;
        }
        return data[key]->search(value) != nullptr;
    }

    /*
     * Removes a value from the hash list if it exists
     */
    void remove(T value)
    {
        unsigned long long key = hash(value);
        if (data[key] == nullptr)
        {
            return;
        }
        data[key]->remove(value);
    }
};
