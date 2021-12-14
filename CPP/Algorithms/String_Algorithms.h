#include <string>
#include <stdexcept>
#include "Math_Algorithms.h"

namespace String_Algorithms
{
    /*
     * Pattern matching in a text using Rabin-Karp. 
     * Does not work for most inputs due to integer overflows
     * Same logic is implemented in python where it works
     * Takes a text, pattern strings, max. possible characters, and prime as input
     */
    bool rabin_karp_matching(std::string text, std::string pattern, long long max_characters = 256, unsigned long long prime = 999983)
    {
        if( text.size() < pattern.size())
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

        long long  i = pattern_size;
        for(;;)
        {
            if( text_hash == pattern_hash )
            {
                long long j = 0;
                int text_index = i - pattern_size;
                for( j; j < pattern_size; j++ )
                {
                    if( text[text_index + j] != pattern[j] )
                    {
                        break;
                    }
                }
                if( j == pattern_size )
                {
                    return true;
                }
            }
            if( (i) >= text_size )
            {
                break;
            }

            //overflow might occur below
            long long temp = (text[i - pattern_size] * h) % prime;
            text_hash = (text_hash - temp) % prime; 
            text_hash = (text_hash * max_characters) % prime;
            text_hash = (text_hash + text[i]) % prime;
            printf("%d\n", text_hash);
            i++;
        }

        return false;
    }

    /*
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
        for( int i = 1; i < pattern_size; i++ )
        {
            while( k > 0 && pattern[k] != pattern[i] )
            {
                k = prefix_function[k - 1];
            }

            if( pattern[k] == pattern[i])
            {
                k++;
            }
            prefix_function[i] = k;
        }

        k = 0;
        for( int i = 0; i < text_size; i++ )
        {
            while( k > 0 && pattern[k] != text[i])
            {
                k = prefix_function[k - 1];
            }

            if( pattern[k] == text[i] )
            {
                k++;
            }

            if( k == pattern_size )
            {
                result.push_back(i - k + 1);
                k = prefix_function[k - 1];
            }
        }
        return result;

    }
}