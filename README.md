# Algorithms and Data-Structures
<!-- Add Urls to algorithms and book page references -->
Some algorithms I implemmented while studying, well, algorithms.

The cpp implementations might leave some dangling pointers in some programs.

Most of the algorithms are implemented by following the pseudo code present in the book `Introduction to Algorithms` by **CLRS** and from `CP-algorithms` with occasional help from `Stack Overflow`.

Algorithms are tested for small to medium random inputs so edge cases might not have been handled well.

---
## Algorithms

The following algorithms are implemented in both `CPP`[^1] and `Python`[^2].

- Divide and Conquer Examples
    - Maximum Sub Array Sum

- Dynamic Problem Solving Examples
    - Rod Cutting Problem
    - Largest Common Substring(LCS) between two strings
    - Knapsack Problem
    - Non-decreasing Subsequence/Non-increasing Subsequence
    - Coin Exchange Problem

- Math Algorithms
    - Factorization of a number
    - Prime numbers using Erasthonesis
    - Greatest Common Divisor (GCD) along with the given number's multiplicate inverses modulo other number
    - Chinese Remainder Theorem (CRT) for solving equations of type a == (r[i] mod n[i]) ∀ i < N
    - Binary Exponentiation modulo number

- Miscellaneous
    - Nth permutation of a given sequence
    - Naive method for getting all permutations of a sequence
    - N Queen puzzle problem using Backtracking

- Search Algorithms
    - Upper Bound algorithm using binary search
    - Lower Bound algorithm using binary search
    - Nth order Element using quick search

- Sort Algorithms
    - Insertion sort
    - Selection Sort
    - Quick Sort
    - Count Sort
    - Radix Sort
    - Merge Sort

- String Algorithms
    - Rabin Karp String Pattern Matching
    - Knuth Morris Pratt Pattern Matching
    - Suffix Array 
    - Largest Common Prefix( LCP ) Array
    - Z-Algorithm for pattern matching

---
## Data Structures

The following data structures are implemented in both `CPP`[^1] and `python`[^2]

- Binary Tree
- Disjoint Set Tree
- Fenwick Tree
- Fibonnaci Min Heap

- Graph with following algorithms
    - Breadth First Search (BFS)
    - Depth First Search (DFS)
    - Path Based Strong Component for Strongly Connected Components(SCC)
    - Kruskal Min Spanning Tree
    - Prim's Min Spanning Tree( using Fibonnaci Heap)
    - Bellman Ford Shortest Paths
    - Djikstra Shortest Paths (using Fibonnaci Heap)
    - Floyd-Warshall All Pair shortest Paths
    - All Pair Shortest Paths

- Min and Max Heap Tree
- Single Linked List
- Red Black Binary Search Tree
- Segment Tree
- Trie for Strings

Below are implemented only in `CPP`[^1]:

- Stack using Array
- Queue using Array
- Hash using Array

---
## Other

The following are some algorithms I want to implement in the future.

- String Algorithms
    - [ ] Suffix Tree 
    - [ ] Suffix Automata
    - [ ] Boyer-Moore String Search
    - [ ] Aho Corasic String Matching 

- NP - Algorithms
    - [ ] Travelling Salesman Problem
    - [ ] Set Covering Problem
    - [ ] Vertex Covering Problem

- Data Structures
    - [ ] Ordered Statistics Tree
    - [ ] van Emde Boas Tree
    - [ ] B-Tree
    - [ ] AVL Tree
    - [ ] Interval Tree

- Miscellaneous
    - [ ] Push-Relabel Algorithms
    - [ ] Greedy Algorithms
    - [ ] RSA


[max-sub-array-sum]: https://en.wikipedia.org/wiki/Maximum_subarray_problem
[stack-overflow]: https://stackoverflow.com/
[cp-site]: https://cp-algorithms.com

[^1]: The cpp programs were compiled and tested with g++ 11.1.0 version
[^2]: The python programs were tested with Python 3.9 - 3.10