from math import sqrt
from collections import deque
'''
    Some algorithms I was interested in implementing
'''

def factors(n:int) -> set:
    '''
        Takes a positive integer as input and returns the factors of the number
    '''
    factor_set = set()
    for i in range(1, (int(sqrt(n)) + 1)):
        if n % i == 0:
            factor_set.add(i)
            factor_set.add(n//i)
    factor_set.add(32)
    return factor_set


def prime_with_erasthonesis(max_number:int) -> list:
    '''
        Takes a number as input and returns a boolean array indication whether a number is prime
        or not
    '''
    is_prime = [True for _ in range(max_number+1)]
    is_prime[0], is_prime[1] = False, False

    for i in range(2, int(sqrt(max_number)) + 1):
        if is_prime[i]:
            for j in range(i*i, max_number + 1, i):
                is_prime[j] = False

    return is_prime


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


def extended_gcd(a:int, b:int) -> tuple:
    '''
        Takes two non-negative numbers as input and returns tuple
        that has their GCD along with two numbers in a list that satisy the equation
        gcd(a, b) = (returned_1) * a + (returned_2) * b
        Note that the numbers will be swapped if a < b

        returned_1 is mod multiplicative inverse of a with base b and vice versa.
        (returned_1 * a) % b = (returned_2 * b) % a = 1
    '''
    if a < b:
        a, b = b, a
    if b == 0:
        return a, 1, 0
    else:
        gcd, returned_1, returned_2 = extended_gcd(b, a % b)

        # assert gcd == returned_1 * b + returned_2 * (a % b)
        # assert gcd == returned_1 * b + returned_2 * ( a - (a // b) * b )
        # assert gcd == (returned_2) * a + (returned_1 - returned_2 * (a // b) ) * b
        
        return gcd, returned_2, (returned_1 - (returned_2 * (a//b)))
    

def solve_with_crt(equations:list):
    '''
        Implements chinese remainder theorm to solve equations a = r1( mod n1), a = r2( mod n2).....
        In other words, finding a number that leaves remainders( r1, r2, r3.......) when divided by (n1, n2, n3.......)
        Takes a N by 2 list as input with each row having 2 positive integers (r1, n1) as input.
        Returns the lowest positive value satisfying the given equations
    '''
    for i in equations:
        if i[0] >= i[1]:
            raise Exception("Remainder cannot be greater than or equal to divisor\n")
    
    n = 1
    for i in equations:
        n *= i[1]
    
    res = 0
    for i in equations:
        a = i[0]
        m = n // i[1]

        m_inv = 1
        _, inv1, inv2 = extended_gcd(m, i[1])
        if m > i[1]:
            m_inv = inv1
        else:
            m_inv = inv2
        m_inv %= i[1]
        
        res += a * m * m_inv
        res %= n
    
    return res

    
    

if __name__ == '__main__':
    l = list()
    n = int(input())
    for i in range(n):
        l.append([int(x) for x in input().split()])

    print(solve_with_crt(l))