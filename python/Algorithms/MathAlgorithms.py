from math import sqrt, inf
from collections import deque

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


def binary_exponentiation(number:int, power:int, base:int = inf):
    '''
        Uses binaray exponentiation to find power of a number modulo base
        Takes number, power and base as input
        Returns power of number modulo base
    '''
    i = 1
    c = 0
    running_product = number
    result = 1
    while power > 0:
        
        if power & 1:
            c += i
            result *= running_product
            result %= base
        
        i <<= 1

        running_product *= running_product
        running_product %= base
        
        # Assert number^c == result
        power >>= 1
    
    return int(result)





if __name__ == '__main__':
    print(binary_exponentiation(int(input()), int(input()), 2**64))  