
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
