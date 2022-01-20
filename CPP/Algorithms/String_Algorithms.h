#include <string>
#include <stdexcept>
#include "Math_Algorithms.h"
#include "Sort_Algorithms.h"

namespace String_Algorithms
{
    /**
     * Pattern matching in a text using Rabin-Karp Algorithm.
     * Does not work for most inputs due to integer overflows
     * Same logic is implemented in python where it works
     * Takes a text, pattern strings, max. possible characters, and prime as input
     */
    bool rabin_karp_matching(std::string text, std::string pattern, long long max_characters = 256, unsigned long long prime = 999983)
    {
        if (text.size() < pattern.size())
        {
            throw std::invalid_argument("Text cannot be less than pattern");
        }
        long long text_size = text.size(), pattern_size = pattern.size();
        long long h = (long long)Math_Algorithms::binary_exponentiation(max_characters, pattern_size - 1, prime);
        long long text_hash = 0, pattern_hash = 0;

        for (long long i = 0; i < pattern_size; ++i)
        {
            text_hash = (((max_characters * text_hash) % prime + (long long)text[i]) % prime);
            pattern_hash = (((max_characters * pattern_hash) % prime + (long long)pattern[i]) % prime);
        }

        long long i = pattern_size;
        for (;;)
        {
            if (text_hash == pattern_hash)
            {
                long long j = 0;
                int text_index = i - pattern_size;
                for (j; j < pattern_size; j++)
                {
                    if (text[text_index + j] != pattern[j])
                    {
                        break;
                    }
                }
                if (j == pattern_size)
                {
                    return true;
                }
            }
            if ((i) >= text_size)
            {
                break;
            }

            // overflow might occur below
            long long temp = (text[i - pattern_size] * h) % prime;
            text_hash = (text_hash - temp) % prime;
            text_hash = (text_hash * max_characters) % prime;
            text_hash = (text_hash + text[i]) % prime;
            i++;
        }

        return false;
    }

    /**
     * Knuth Morris Pratt algorithm
     * Takes text and pattern strings as input
     * Throws an exception if pattern is larger than string
     * Returns all indices where the pattern starts
     */
    std::vector<int> kmp_matcher(std::string text, std::string pattern)
    {
        int text_size = text.size(), pattern_size = pattern.size();

        // max length ( < i ) of suffix of p[1..i] that is als prefix of p[1..i]
        // value at (i - 1) contains the info about length i in function
        std::vector<int> prefix_function(pattern_size);
        std::vector<int> result;

        int k = 0;
        prefix_function[0] = 0;
        for (int i = 1; i < pattern_size; i++)
        {
            while (k > 0 && pattern[k] != pattern[i])
            {
                k = prefix_function[k - 1];
            }

            if (pattern[k] == pattern[i])
            {
                k++;
            }
            prefix_function[i] = k;
        }

        k = 0;
        for (int i = 0; i < text_size; i++)
        {
            while (k > 0 && pattern[k] != text[i])
            {
                k = prefix_function[k - 1];
            }

            if (pattern[k] == text[i])
            {
                k++;
            }

            if (k == pattern_size)
            {
                result.push_back(i - k + 1);
                k = prefix_function[k - 1];
            }
        }
        return result;
    }

    /**
     * Suffix array
     * Takes a string, maximum value of single character and sentinel as input
     * Returns a vector containing the suffix array
     * Works for tested inputs
     * For more info, see https://cp-algorithms.com/string/suffix-array.html
     */
    std::vector<int> get_suffix_array(std::string s, int max_char = 256, std::string sentinel = "$")
    {
        s += sentinel;
        int size = s.size();

        std::vector<int> suffix_array(size - 1), class_array(size);

        struct String_Index
        {
            int index; // stores p[i]
            int value; // stores s[i] for first iteration, c[p[i]] in step iteration

            operator int() const
            {
                return (int)value;
            }

            void operator=(const String_Index &other)
            {
                this->index = other.index;
                this->value = other.value;
            }

            void set(int index, int value)
            {
                this->index = index;
                this->value = value;
            }
        };

        std::vector<String_Index> string_array(size);
        for (int i = 0; i < size; i++)
        {
            string_array[i].index = i;
            string_array[i].value = s[i];
        }

        Sort::count_sort(string_array, max_char, false);

        int c = 0;
        class_array[string_array[0].index] = 0;
        for (int i = 1; i < size; i++)
        {
            if (s[string_array[i - 1].index] != s[string_array[i].index])
            {
                c++;
            }
            class_array[string_array[i].index] = c;
        }

        for (int step = 1; step < size; step *= 2)
        {
            for (int i = 0; i < size; i++)
            {
                int index = string_array[i].index - step;
                if (index < 0)
                {
                    index += size;
                }
                string_array[i].set(index, class_array[index]);
            }

            Sort::count_sort(string_array, c);

            c = 0;
            class_array[string_array[0].index] = 0;
            for (int i = 1; i < size; i++)
            {
                int range_1_left = string_array[i - 1].value;
                int range_1_right = class_array[(string_array[i - 1].index + step) % size];

                int range_2_left = string_array[i].value;
                int range_2_right = class_array[(string_array[i].index + step) % size];

                if (range_1_left != range_2_left || range_1_right != range_2_right)
                {
                    c++;
                }

                class_array[string_array[i].index] = c;
            }
        }
        for (int i = 1; i < size; i++)
        {
            suffix_array[i - 1] = string_array[i].index;
        }
        return suffix_array;
    }

    /**
     * Longest common prefix Array
     * Takes a string and suffix array as input
     * Returns a vector array that has longest prefix length between s[i...n] and s[i + 1 ... n]
     * at index i
     */
    std::vector<int> get_lcp_array(const std::string &s, const std::vector<int> suffix_array)
    {
        int size = s.size();
        std::vector<int> rank(size), lcp(size);
        for( int i = 0; i < size; i++ )
        {
            rank[suffix_array[i]] = i;
        }

        int k = 0;
        for( int i = 0; i < size; i++ )
        {
            if( rank[i] == size - 1)
            {
                lcp[rank[i]] = -1;
                k = 0;
            }
            else
            {
                // Index of smallest suffix s[j...n] lexiographically greater than current suffix s[i...n]
                int j = suffix_array[rank[i] + 1]; 
                while( j + k < size && i + k < size && s[i + k] == s[j + k])
                {
                    k++;
                }
                lcp[rank[i]] = k;
                
                if( k > 0 )
                {
                    k--;
                }
            }
        }

        return lcp;
        
    }

    /**
     * Z-Algorithm
     * Takes a string, pattern and sentinel as input
     * Returns the indices where the pattern exists in the string
     */
    std::vector<int> z_matcher(std::string str, std::string pattern, std::string sentinel = "$")
    {
        int pattern_size = pattern.size();
        str = pattern + sentinel + str;
        int size  = str.size();
        std::vector<int> z_lengths(size), indices;

        z_lengths[0] = size;

        // For z-box
        int left = -1, right = -1; 
        for( int i = 1; i < size; i++ )
        {
            if( i > right )
            {
                int length = 0;
                while( i + length < size && str[length] == str[i + length])
                {
                    length++;
                }
                z_lengths[i] = length;

                left = i;
                right = i + length - 1;
            }
            else
            {
                // Right to i in z-box
                int remaining = right - i + 1;

                // Index in prefix where char at i is in one-to-one relationship
                // Or i - left
                int index_in_prefix = pattern_size - remaining;

                z_lengths[i] = z_lengths[index_in_prefix];

                if( z_lengths[i] >= remaining )
                {
                    int length = 0, 
                        j = right + 1, 
                        k = index_in_prefix + z_lengths[i];
                    while( j + length < size && str[j + length] == str[k + length])
                    {
                        length++;
                    }
                    z_lengths[i] += length;

                    left = i, right = i + z_lengths[i] - 1;
                }
            }
            if( z_lengths[i] == pattern_size )
            {
                indices.push_back(i - pattern_size - 1);
            }
        }
        return indices;
    }

}