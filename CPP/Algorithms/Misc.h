#include <functional>
#include <vector>
#include <deque>
#include <stdio.h>
#include <limits.h>
#include <stdexcept>
#include <set>
#include <assert.h>
#include <math.h>
// Contains some algorithms that I was interested in implementing
namespace Misc {


    /*
     * Takes a number as input and returns its factors in an ordered set
     * There is a faster method to calculate number of factors for relatively small numbers
     */
    std::set<unsigned long long> get_factors(unsigned long long number) {
        std::set<unsigned long long> factor_set;
        for( unsigned long long i = 1; i * i <= number; i++ ) {
            if( number % i == 0 ) {
                factor_set.insert(i);
                factor_set.insert(number/i);
            }
        }
        return factor_set;

    }

    /*
     * Takes a number as input and returns a bool array indicating which number below the given number are not prime
     * Implemented using Sieve of erasthonesis
     */
    bool* prime_with_erasthonesis(const unsigned long long number) {
        if( number >= INT64_MAX ) {
            throw std::invalid_argument("Cannot be used\n");
        }
        bool* is_prime = new bool[number+1];
        for( unsigned long long i = 0; i <= number; i++ ) {
            is_prime[i] = true;
        }

        is_prime[0] = false;
        is_prime[1] = false;
        
        for( unsigned long long i = 2; i * i <= number; i++ ) {
            if( is_prime[i] ) {
                for( unsigned long long j = i*i; j <= number; j += i ) {
                    is_prime[j] = false;
                }
            }
        }
        return is_prime;
    } 

    /*
     * Takes a sorted array(0th or base permutation) of elements, its size and the nth permutation to find
     * Arranges the given array's element to represent the order of them in nth permutation
     * Due to int limitations, only works with size 12 or less
     */
    template<typename T>
    void nth_permutation_of(T* array, int size, int nth_permutation) {
        
        int* new_indices = new int[size];
        int factorial = 1; 
        
        for( int i = 1, j = size - 1; i <= size; i++, j-- ) {
            
            new_indices[j] = j;

            if( nth_permutation != 0 ) {
                nth_permutation /= factorial;
                new_indices[j] += (nth_permutation % i); 
                factorial *= i; // Will overflow if size is greater than 12
            }
        
        }

        // The element at new index will be inserted at current index
        for( int i = 0; i < size; i++ ) {
            
            if( new_indices[i] != i ) {
                
                int temp = array[new_indices[i]];
                for( int j = new_indices[i]; j > i; j-- ) {
                    array[j] = array[j-1];
                }
                array[i] = temp;
            }
        
        }
    }

    /*
     * A naive implementation for printing every permutation of a sequence using backtracking.
     * Assumes the given array is sorted.
     * Takes sequence array and its size as input
     * Returns a pointer to an array of elements which have all the permutaions
     * int limitations require size to be less than 13
     */
    template<typename T>
    T** all_permutations(T* sequence, int size) {

        bool* is_this_considered = new bool[size];

        std::deque<T> deque;

        int factorial = 1;
        for(int i = 1; i <= size; i++ ) {
            factorial *= i;
            is_this_considered[i-1] = false;
        }

        T** permutations = new T*[factorial];
        int index = 0;

        std::function<void()> recurse_for_permutations = 
        [&size, &is_this_considered, &permutations, &deque, 
        &recurse_for_permutations, &index, &sequence]() {

            if( deque.size() == size ) {
                permutations[index] = new T[size];
                for( int i = 0; i < size; i++ ) {
                    permutations[index][i] = deque[i];
                }
                index++;
            }
            else {
                for( int i = 0; i < size; i++ ) {
                    if( !is_this_considered[i] ) {
                        is_this_considered[i] = true;
                        deque.push_back(sequence[i]);
                        recurse_for_permutations();
                        is_this_considered[i] = false;
                        deque.pop_back();   
                    }
                }
            }
        };
        recurse_for_permutations();
        return permutations;
    }


    /*
     * N Queen Puzzle Problem through backtracking
     * Problem involves finding a valid state in which n queens can be placed on a nxn chess board 
     * without being in a position to be attacked by other queens
     * Takes a positive integer ( > 3 ) as input 
     * Returns a pointer to an array of boolean pointers  which represent whether the queen is placed on the position
     * if chess_board[i][j] is true, then queen is placed there.
     */
    bool** n_queen_puzzle_problem( int n ) {
        if( n < 4 ) {
            throw std::invalid_argument("Cannot be placed on a chess board with size less than 4");
        }

        bool** chess_board = new bool*[n];
        
        for( int i = 0; i < n; i++ ) {
            chess_board[i] = new bool[n];
            for( int j = 0; j < n; j++ ) {
                chess_board[i][j] = false;
            }
        }

        // Helper function to validate a candidate solution
        auto validate = [&chess_board, &n](int i, int j) -> bool {
            for( int k = 0; k < n; k++ ) {
                if( chess_board[k][j] || 
                    chess_board[i][k] ||
                    ( i-k >= 0 && j-k >= 0 && chess_board[i-k][j-k] ) ||
                    ( i+k < n && j+k < n && chess_board[i+k][j+k] )   ||
                    ( i-k >= 0 && j + k < n && chess_board[i-k][j+k]) ||
                    ( i+k < n && j - k >= 0 && chess_board[i+k][j-k])) {
                    
                    return false;
                }
            }
            return true;
        };


        int queens  = n;

        // Helper function for backtracking
        std::function<bool(int)> place_queen = 
        [&chess_board, &n, &validate, &queens, &place_queen](int row) -> bool{
            
            if( row >= n ) {
                return queens == 0;
            }

            for( int col = 0; col < n; col++ ) {
                if( validate(row, col) ) {
                    chess_board[row][col] = true;
                    queens--;
                    if( place_queen(row+1) ) {
                        break;
                    }
                    else {
                        chess_board[row][col] = false;
                        queens++;
                    }
                }
            }

            return queens == 0;

        };

        place_queen(0);
        return chess_board;
    }


    /*
     * Takes two non-negative numbers as input and returns a poiinter to an array 
     * that has their GCD along with two numbers in a array that satisy the equation 
     * gcd(number_1, number_2) = (returned_1) * number_1 + (returned_2) * number_2
     * Note that the numbers will be swapped if number_1 < number_2
     *
     * returned_1 is mod multiplicative inverse of number_1 with base number_2 and vice versa.
     * (returned_1 * number_1) % number_2 = 1 and (returned_2 * number_2) % number_1 = 1
     */
    long long* extended_gcd(long long number_1, long long number_2) {
        
        long long* gcd_array = new long long[3];
        if( number_1 < number_2 ) {
            std::swap(number_1, number_2);
        }
        if( number_2 == 0 ) {
            gcd_array[0] = number_1;
            gcd_array[1] = 1;
            gcd_array[2] = 0;
        }
        else {
            long long* temp_gcd_array = extended_gcd(number_2, number_1 % number_2);
            gcd_array[0] = temp_gcd_array[0];
            
            // assert(
            //     gcd_array[0] == 
            //         temp_gcd_array[1] * number_2 + 
            //         temp_gcd_array[2] * (number_1 % number_2));

            gcd_array[1] = temp_gcd_array[2];
            gcd_array[2] = temp_gcd_array[1] - ((number_1/number_2) * temp_gcd_array[2]);
        }
        return gcd_array;
    }


    /*
     * Implements chinese remainder theorm to solve equations a = r1( mod n1), a = r2( mod n2).....
     * In other words, finding a number that leaves remainders( r1, r2, r3.......) when divided by (n1, n2, n3.......)
     * Takes a N by 2 array as input with each row having 2 positive integers (r1, n1)) and number of equations as input.
     * Returns the lowest positive value satisfying the given equations
     */
    int solve_with_crt(long long** equations, int number_of_equations) {
        // equation[i][0] - remainder, equation[i][1] - divisor
        for( int i = 0; i < number_of_equations; i++ ) {
            if( equations[i][0] >= equations[i][1] ) {
                throw std::invalid_argument("Remainders cannot be less than Divisors");
            }
        }
        long long n = 1;
        for( int i = 0; i < number_of_equations; i++ ) {
            n *= equations[i][1];
        }
        
        int result = 0;

        for( int i = 0; i < number_of_equations; i++ ) {
            long long a = equations[i][0];
            long long m = n / equations[i][1];

            long long m_inv;
            long long* gcd_array = extended_gcd(m, equations[i][1]);
            if( m > equations[i][1] ) {
                m_inv = gcd_array[1];
            }
            else {
                m_inv = gcd_array[2];
            }
            m_inv %= equations[i][1];
            if( m_inv < 0 ) {
                m_inv += equations[i][1];
            }

            result += (a * m * m_inv);
            result %= n;

        }
        return result;
    }

}
