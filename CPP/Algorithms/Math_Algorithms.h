#include <functional>
#include <vector>
#include <deque>
#include <stdio.h>
#include <limits.h>
#include <stdexcept>
#include <set>
#include <assert.h>
#include <math.h>

namespace Math_Algorithms
{

    /*
     * Takes a number as input and returns its factors in an ordered set
     * There is a faster method to calculate number of factors for relatively small numbers
     */
    std::set<unsigned long long> get_factors(unsigned long long number)
    {
        std::set<unsigned long long> factor_set;
        for (unsigned long long i = 1; i * i <= number; i++)
        {
            if (number % i == 0)
            {
                factor_set.insert(i);
                factor_set.insert(number / i);
            }
        }
        return factor_set;
    }

    /*
     * Takes a number as input and returns a bool array indicating which number below the given number are not prime
     * Implemented using Sieve of erasthonesis
     */
    bool *prime_with_erasthonesis(const unsigned long long number)
    {
        if (number >= INT64_MAX)
        {
            throw std::invalid_argument("Cannot be used\n");
        }
        bool *is_prime = new bool[number + 1];
        for (unsigned long long i = 0; i <= number; i++)
        {
            is_prime[i] = true;
        }

        is_prime[0] = false;
        is_prime[1] = false;

        for (unsigned long long i = 2; i * i <= number; i++)
        {
            if (is_prime[i])
            {
                for (unsigned long long j = i * i; j <= number; j += i)
                {
                    is_prime[j] = false;
                }
            }
        }
        return is_prime;
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
    long long *extended_gcd(long long number_1, long long number_2)
    {

        long long *gcd_array = new long long[3];
        if (number_1 < number_2)
        {
            std::swap(number_1, number_2);
        }
        if (number_2 == 0)
        {
            gcd_array[0] = number_1;
            gcd_array[1] = 1;
            gcd_array[2] = 0;
        }
        else
        {
            long long *temp_gcd_array = extended_gcd(number_2, number_1 % number_2);
            gcd_array[0] = temp_gcd_array[0];

            // assert(
            //     gcd_array[0] ==
            //         temp_gcd_array[1] * number_2 +
            //         temp_gcd_array[2] * (number_1 % number_2));

            gcd_array[1] = temp_gcd_array[2];
            gcd_array[2] = temp_gcd_array[1] - ((number_1 / number_2) * temp_gcd_array[2]);
        }
        return gcd_array;
    }

    /*
     * Implements chinese remainder theorm to solve equations a = r1( mod n1), a = r2( mod n2).....
     * In other words, finding a number that leaves remainders( r1, r2, r3.......) when divided by (n1, n2, n3.......)
     * Takes a N by 2 array as input with each row having 2 positive integers (r1, n1)) and number of equations as input.
     * Returns the lowest positive value satisfying the given equations
     */
    int solve_with_crt(long long **equations, int number_of_equations)
    {
        // equation[i][0] - remainder, equation[i][1] - divisor
        for (int i = 0; i < number_of_equations; i++)
        {
            if (equations[i][0] >= equations[i][1])
            {
                throw std::invalid_argument("Remainders cannot be less than Divisors");
            }
        }
        long long n = 1;
        for (int i = 0; i < number_of_equations; i++)
        {
            n *= equations[i][1];
        }

        int result = 0;

        for (int i = 0; i < number_of_equations; i++)
        {
            long long a = equations[i][0];
            long long m = n / equations[i][1];

            long long m_inv;
            long long *gcd_array = extended_gcd(m, equations[i][1]);
            if (m > equations[i][1])
            {
                m_inv = gcd_array[1];
            }
            else
            {
                m_inv = gcd_array[2];
            }
            m_inv %= equations[i][1];
            if (m_inv < 0)
            {
                m_inv += equations[i][1];
            }

            result += (a * m * m_inv);
            result %= n;
        }
        return result;
    }

    /*
     * Uses binary exponentiation to calculate the power of a number modulo another number.
     * Takes the number, power and base as input
     * Returns the power of number modulo base as output
     * Overflow may occur for sufficiently large numbers if the base is default
     */
    unsigned long long binary_exponentiation(
        unsigned long long number,
        unsigned long long power,
        unsigned long long base = UINT64_MAX)
    {

        unsigned long long result = 1;
        unsigned long long running_product = number;

        unsigned long long i = 1; // Used for 'for' loop invariant
        unsigned long long c = 0; // Above comment

        while (power > 0)
        {

            if ((power & 1) == 1)
            {
                c += i;
                result *= running_product; // Overflow may occur here
                result %= base;
            }
            i *= 2;
            running_product *= running_product; // Overflow may occur here
            running_product %= base;

            // Assert (number ^ c) % base == result
            power >>= 1;
        }
        return result;
    }

}
