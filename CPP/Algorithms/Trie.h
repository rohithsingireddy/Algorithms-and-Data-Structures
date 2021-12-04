#include <cstddef>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

/*
 * Implements a trie structure for objects with string key(ASCII)
 * Assumes each key has only one value associated with it
 */

const int MAX_CHAR_CODE = 128;

template <typename T>
class Trie
{
    struct trie_node
    {
        trie_node *child[MAX_CHAR_CODE] = {};
        bool has_value = false;
        T value = T();
        int no_of_children = 0;

        trie_node *make_or_get_node(char c)
        {
            //TODO: check logic
            if (child[c] == nullptr)
            {
                child[c] = new trie_node();
                no_of_children++;
            }
            return child[c];
        }

        void remove_child(char c)
        {
            //TODO: Implement removing a child when
            //no subsequent children are present
        }

    };

    trie_node *root = nullptr;

public:
    Trie()
    {
        root = new trie_node();
    }

    /*
     * Takes a string and its associated value as input
     * Inserts them into the trie.
     */
    void insert(std::string key, T value)
    {
        trie_node *cur = root;
        for (char c : key)
            cur = cur->make_or_get_node(c);
        cur->value = value;
        cur->has_value = true;
    }

    /*
     * Takes a string as input
     * Returns true if value associated with string is in the trie.
     */
    bool contains(std::string key)
    {
        trie_node *cur = root;
        for (char c : key)
        {
            cur = cur->child[c];
            if (cur == nullptr)
                return false;
        }
        return cur->has_value;
    }

    /*
     * Removes the value with the given key from the tree through lazy removal
     */
    void remove(std::string key)
    {
        //TODO: Implement eager removal

        trie_node* current = root;
        int index = 0, size = key.size();
        while( current != nullptr && index < size )
        {
            current = current->child[(int)key[index++]];
        }

        if( current != nullptr )
        {
            current->value = T();
            current->has_value = false;
        }

    }

    /*
     * Takes a string as input
     * Throws an exception if key does not exist in trie
     * Returns value associated with string as input or default value if there is no value
     */
    T get_value(std::string key)
    {
        trie_node *cur = root;
        for (char c : key)
        {
            cur = cur->child[c];
            if (cur == nullptr)
            {
                throw std::invalid_argument("Invalid key");
            }
        }
        return cur->value;
    }

    /*
     * Takes a string as input
     * Returns all the (key,values) whose key have input string as prefix
     */
    std::vector<std::pair<std::string, T>> auto_complete(std::string key)
    {
        std::vector<std::pair<std::string, T>> values;

        trie_node *cur = root;
        for (char c : key)
        {
            cur = cur->child[c];
            if (cur == nullptr)
                return values;
        }

        // Helper function for recursively searching for required keys
        std::function<void(trie_node *, std::string)> search_values =
            [&values, &search_values](trie_node *current, std::string prefix) -> void
        {
            if (current != nullptr)
            {
                if (current->has_value)
                {
                    values.push_back(std::make_pair(prefix, current->value));
                }

                for (int i = 0; i < MAX_CHAR_CODE; i++)
                {
                    search_values(current->child[i], prefix + (char)i);
                }
            }
        };

        search_values(cur, key);
        return values;
    }

    /*
     * Returns all keys and values currently present in trie in order
     * sorted by key in increasing order
     */
    std::vector<std::pair<std::string, T>> all_keys_and_values()
    {
        return auto_complete("");
    }
};
