
def max_price_for_rod(price_for_length:list):
    '''
        Rod cutting problem. Finds the maximum price possible given a list of prices for different lengths
        Returns the maximum price and the possible lengths to cut the rod into
    '''
    max_length = len(price_for_length)
    cut_off = [i for i in range(max_length+1)]
    dp_array = [i for i in price_for_length]
    dp_array.insert(0, 0)

    for cut in range(max_length+1):
        for length in range(cut, max_length+1):
            if dp_array[length] < dp_array[cut] + dp_array[length - cut]:
                dp_array[length] = dp_array[cut] + dp_array[length - cut]
                cut_off[length] = cut
    
    result = [dp_array[max_length]]

    cut = max_length
    while cut > 0:
        result.append(cut_off[cut])
        cut -= cut_off[cut]
    
    return result


def common_subsequence( string_1:str, string_2:str)-> str:
    '''
        Finds the common subsequence between two given strings
        Returns the string with the sequence of characters
        Should correct for input abracadabraemalesmagic abracadabrayfemalemagic
    '''
    string_mat = []
    for i in range(len(string_1)):
        string_mat.append([0 for _ in range(len(string_2))])

    for i in range(len(string_1)):
        for j in range(len(string_2)):
            if string_1[i] == string_2[j]:
                string_mat[i][j] = 1 + string_mat[i-1][j-1]
            else:
                string_mat[i][j] = max(string_mat[i-1][j], string_mat[i][j-1])

    i, j = len(string_1)-1, len(string_2)-1
    common_string = ''

    while i >= 0  and j >= 0 :
        if string_1[i] == string_2[j]:
            common_string += string_1[i]
            i -= 1
            j -= 1
        elif string_mat[i-1][j] > string_mat[i][j-1]:
            i -= 1
        else:
            j -= 1

    common_string = ''.join([x for x in reversed(common_string)])
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


if __name__ == '__main__':
    l = input().split()
    print(non_increasing_subsequence(l))

