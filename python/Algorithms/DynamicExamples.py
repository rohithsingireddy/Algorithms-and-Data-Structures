from math import inf

def max_price_for_rod(price_for_length:list) -> tuple:
    '''
        Rod cutting problem. Finds the maximum price possible given a list of prices for different lengths
        Returns the maximum price and the possible lengths to cut the rod into
    '''
    max_length = len(price_for_length)
    cut_off = [i for i in range(max_length+1)]
    dp_array = [i for i in price_for_length]
    dp_array.insert(0, 0)

    for length in range(1, max_length+1):
        for cut in range(length):
            if dp_array[length] < dp_array[cut] + dp_array[length - cut]:
                dp_array[length] = dp_array[cut] + dp_array[length - cut]
                cut_off[length] = cut
    
    result = []

    cut = max_length
    while cut > 0:
        result.append(cut_off[cut])
        cut -= cut_off[cut]
    
    return dp_array[max_length], result


def common_subsequence( string_1:str, string_2:str)-> str:
    '''
        Finds the largest common subsequence between two given strings
        Returns the string with the sequence of characters
    '''
    string_mat = []
    for i in range(len(string_1) + 1):
        string_mat.append([0 for _ in range(len(string_2) + 1)])

    for i in range(1, len(string_1) + 1):
        for j in range(1, len(string_2) + 1):
            if string_1[i - 1] == string_2[j - 1]:
                string_mat[i][j] = 1 + string_mat[i-1][j-1]
            else:
                string_mat[i][j] = max(string_mat[i-1][j], string_mat[i][j-1])

    i, j = len(string_1), len(string_2)
    common_string = []

    while i > 0  and j > 0 :
        if string_1[i - 1] == string_2[j - 1]:
            common_string.append(string_1[i - 1])
            i -= 1
            j -= 1
        elif string_mat[i-1][j] > string_mat[i][j-1]:
            i -= 1
        else:
            j -= 1

    common_string.reverse()
    return common_string


def non_increasing_subsequence(sequence:list) -> list:
    '''
        Takes a sequence with comparable as input
        Returns a list of longest non-increasing subsequence
    '''
    size = len(sequence)
    last_index_at = [-1 for _ in range(size)] #stores the previous index of sequence current element belongs to
    size_at = [1 for _ in range(size)] #Stores the size of longest sequence the current element belongs to

    max_index, max_length = -1, -1

    for i in range(1, size):
        for j in range(i-1, -1, -1):
            if sequence[j] >= sequence[i] and size_at[j] + 1 > size_at[i]:
                size_at[i] = size_at[j] + 1
                last_index_at[i] = j
        
        if max_length < size_at[i]:
            max_length = size_at[i]
            max_index = i
    
    res = list()
    while max_index >= 0:
        print(max_index)
        res.append(sequence[max_index])
        max_index = last_index_at[max_index]
    
    return [x for x in reversed(res)]


def solve_knapsack(weights:list, values:list, max_weight:int):
    '''
        0-1 Knapsack Problem
        Takes a list of weights, values, max_weight as input
        Returns a tuple with max values and a set of weights that are associated with it
    '''
    size = len(weights)

    # size by max_weight matrix array. The (i, j)th element represents 
    # the maximum value using some or all of the first i elements whose 
    # combined weight is less than or equal to j
    dp_array = [list() for _ in range(size + 1)]
    for i in range(size + 1):
        dp_array[i] = [0 for _ in range(max_weight + 1)]

    for i in range(1, size+1):
        for weight in range(max_weight+1):
            if weights[i-1] > weight:
                dp_array[i][weight] = dp_array[i - 1][weight]
            else:
                dp_array[i][weight] = max( dp_array[i - 1][weight], dp_array[i - 1][weight - weights[i - 1]] + values[i - 1])
    
    res, weight = -1, max_weight
    while res <= 0 and weight > 0:
        res = dp_array[size][weight]
        weight -= 1

    result = []
    i, j = size, max_weight
    while i > 0:
        if dp_array[i-1][j] < dp_array[i][j]:
            result.append(weights[i - 1])
            j -= weights[i - 1]
        i -= 1
    
    return res, result


def coin_exchange(coins:list, value:int):
    '''
        Coin Exchange problem. Similar to knapsack problem
        Takes a list of coins and value as input
        
        Returns a tuple containing minimum number of coins required to create the value
        and a dict contiaing info about the chosen coins
    '''
    size = len(coins)
    
    '''
        (i, j)th element represents the min coins taken from first i elements
        that are used to represent sum that is greatest value less than or equal 
        to j
    '''
    dp_array = [None for _ in range(size + 1)]
    for i in range(size + 1):
        dp_array[i] = [inf for _ in range(value + 1)]
        dp_array[i][0] = 0

    for i in range(1, size + 1):
        for j in range(1, value + 1):
            if j < coins[i - 1]:
                dp_array[i][j] = dp_array[i - 1][j]
            else:
                dp_array[i][j] = min( dp_array[i - 1][j], dp_array[i][j - coins[i - 1]] + 1)

    result = {}
    j = value
    i = size
    while j > 0 and i > 0:
        if dp_array[i - 1][j] == dp_array[i][j]:
            i -= 1
        else:
            coin = coins[i - 1]
            if coin in result:
                result[coin] += 1
            else:
                result[coin] = 1
            j -= coin
        
    # s = 0
    # for i in result:
    #     s += (i * result[i])
    # assert(s == value)

    return dp_array[-1][-1], result


if __name__ == '__main__':
    
    value = int(input())
    
    coins = [int(x) for x in input().split()]
        
    print(coin_exchange(coins, value))


