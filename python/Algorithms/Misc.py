from math import sqrt
from collections import deque
'''
    Some algorithms I was interested in implementing
'''


def nth_factorial(sequence:list, nth_permutation:int) -> list:
    '''
        Takes a list of objects in 0th permutation, the nth permutation to find as input
        and returns a list of nth permutation.
        The sequence is modified to represent the the nth permutation
        The order permutation is based on the indices
    '''
    size = len(sequence)
    new_indices = [i for i in range(size)]
    factorial = 1

    for i in range(1, size + 1):
        if nth_permutation > 0:
            nth_permutation //= factorial
            new_indices[size-i] += (nth_permutation % i)
            factorial *= i
    
    for i in range(size):
        if new_indices[i] != i:
            temp = sequence[new_indices[i]]
            for j in range(new_indices[i], i, -1):
                sequence[j] = sequence[j-1]
            sequence[i] = temp
    
    return sequence


def all_factorials(sequence:list) -> list:
    '''
        Takes a list and returns all the permutations of the sequence in another list
        Implemented with a naive backtracking algorithm
    '''
    dq = deque()
    size = len(sequence)
    res = list()
    is_considered = [False for i in range(size)]
       
    def recurse():
        '''
            Helper function to recursively print permutations in order
        '''
        if len(dq) == size:
            res.append([x for x in dq])
        else:
            
            for i in range(size):
                if not is_considered[i]:
                    is_considered[i] = True
                    dq.append(sequence[i])
                    recurse()
                    is_considered[i] = False
                    dq.pop()
    
    recurse()
    return res


def n_queens_on_chess(n:int) -> list:
    '''
        N queens on NxN chess board
        Takes as input and gives a N by N list as output
        Uses backtracking to find a valid solution
    '''

    row = [False for _ in range(n)]
    chess_board = []
    queens = n
    for i in range(n):
        chess_board.append(row.copy())
    
    def valid(row:int, col:int) -> bool:
        '''
            Helper function to validate a candidate solution
        '''
        for k in range(n):
            if (chess_board[row][k] or
                chess_board[k][col] or
                (row - k >= 0 and col - k >= 0 and chess_board[row - k][col - k]) or
                (row + k < n and col + k < n and chess_board[row + k][col + k]) or
                (row - k >= 0 and col + k < n and chess_board[row - k][col + k]) or
                (row + k < n and col - k >= 0 and chess_board[row + k][col - k])):
                return False
        return True
    
    def place_queen(row:int) -> bool:
        '''
            Helper function to recursively find a valid solution to the problem
        '''
        nonlocal queens
        if row >= n:
            return queens == 0 
        else:
            for col in range(n):
                if valid(row, col):
                    chess_board[row][col] = True
                    queens -= 1
                    if not place_queen(row + 1):
                        chess_board[row][col] = False
                        queens += 1
                    else:
                        break
        return queens == 0
    
    place_queen(0)
    return chess_board
