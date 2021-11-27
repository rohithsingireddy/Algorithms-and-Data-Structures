
def binary_search(array:list, value_to_search) -> int:
    '''
    Takes array and value to search as input and returns an index of list as output
    If value is present, returns the (lowest if more than one occurence of element)index of the value in the array.
    If value is absent, returns the lowest index of the upper bound of the value
    '''
    low, high, current = 0, len(array), 0

    while low != high:
        current = (low + high - 1) // 2
        if array[current] < value_to_search:
            low = current + 1
        else:
            high = current
    return low

    