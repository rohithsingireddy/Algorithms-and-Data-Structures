#include <functional>
#include <vector>
#include <deque>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <set>
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
                factorial *= i; // Will overflow if size is greater than 14
            }
        
        }

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





}