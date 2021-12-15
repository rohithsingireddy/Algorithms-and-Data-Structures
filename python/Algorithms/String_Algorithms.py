from Sorts import count_sort

def rabin_karp_matching(
        text: str,
        pattern: str,
        max_char: int = 256,
        prime: int = 999983) -> bool:
    '''
        Pattern matching in a string using rabin karp algorithm.
        Takes a text and pattern as input and returns true
        if the pattern occurs in string
    '''
    if len(text) < len(pattern):
        raise ValueError("Text cannot be less than pattern")

    text_size, pattern_size = len(text), len(pattern)
    h = ((max_char ** (pattern_size-1)) % prime)

    text_hash, pattern_hash = 0, 0
    for i in range(pattern_size):
        text_hash = (((max_char * text_hash) + ord(text[i])) % prime)
        pattern_hash = (((max_char * pattern_hash) + ord(pattern[i])) % prime)
    
    i = pattern_size
    while True:
        if text_hash == pattern_hash:
            text_index, pattern_index = i - pattern_size, 0
            while pattern_index < pattern_size:
                if text[text_index + pattern_index] != pattern[pattern_index]:
                    break
                pattern_index += 1
            if pattern_index == pattern_size:
                return True
            
        if i >= text_size:
            break
        
        text_hash -= (ord(text[i - pattern_size]) * h)
        text_hash *= max_char
        text_hash += ord(text[i])
        text_hash %= prime
        print(text_hash)
        i += 1
    
    return False


def kmp_matcher(text:str, pattern:str) -> list:
    '''
        Knuth Morris Pratt algorithm
        Takes text and pattern as input
        Throws an exception if pattern is larger than text
        Returns all indices where the pattern starts  
    '''
    text_size, pattern_size = len(text), len(pattern)
    result = list()

    #max length( < i ) of suffix of p[1...i] that is also the prefix of p[1...i]
    #value at (i - 1) contains info about length i in prefix function
    prefix_function = [0 for _ in range(pattern_size)]

    k = 0
    for i in range(1, pattern_size):
        while k > 0 and pattern[k] != pattern[i]:
            k = prefix_function[k - 1]
        
        if pattern[k] == pattern[i]:
            k += 1
        
        prefix_function[i] = k

    k = 0
    for i in range(text_size):
        while k > 0 and pattern[k] != text[i]:
            k = prefix_function[k - 1]
        
        if pattern[k] == text[i]:
            k += 1
        
        if k == pattern_size:
            result.append(i - k + 1)
            k = prefix_function[k - 1]
    
    return result



def get_suffix_array(s:str, max_char:int = 256) -> list:
    '''
        Suffix Array
        Takes a string and maximum value of a single character
        Returns a vector containing the suffix array
        Works for tested inputs
        For more info, see https://cp-algorithms.com/string/suffix-array.html
    '''
    s += '$'
    size = len(s)

    suffix_array = [0 for _ in range(size - 1)]
    class_array = [0 for _ in range(size)]

    class String_Index:
        def __init__(self, i:int, v:int):
            self.index = i
            self.value = v
        
        def __index__(self):
            return self.value
        
        def set_var(self, index:int, value:int):
            self.index = index
            self.value = value
    
    string_array = [String_Index(i, ord(s[i])) for i in range(size)]

    count_sort(string_array, max_char, False)
    c = 0
    class_array[string_array[0].index] = 0

    for i in range(1, size):
        if s[string_array[i - 1].index] != s[string_array[i].index]:
            c += 1
        class_array[string_array[i].index] = c
    
    step = 1
    while step < size:
        for i in range(size):
            index = (string_array[i].index - step) % size
            string_array[i].set_var(index, class_array[index])
        
        count_sort(string_array, c)
        
        c = 0
        class_array[string_array[0].index] = 0
        for i in range(1, size):
            range_1_left = string_array[i].index
            range_1_right = class_array[(string_array[i].index + step) % size]

            range_2_left = string_array[i - 1].index
            range_2_right = class_array[(string_array[i - 1].index + step) % size]

            if range_1_left != range_2_left or range_1_right != range_2_right:
                c += 1
            class_array[string_array[i].index] = c
        
        step *= 2
    
    for i in range(1, size):
        suffix_array[i - 1] = string_array[i].index
    
    return suffix_array


def get_lcp_array(s:str, suffix_array:list) -> list:
    '''
        Longest Common Prefix Array
        Takes a string and suffix array as input
        Returns a vector array that has longest prefix between
        s[i...n] and s[i + 1 .... n] at index i
    '''
    size = len(s)
    lcp = [0 for _ in range(size)]
    rank = lcp.copy()

    for i in range(size):
        rank[suffix_array[i]] = i
    
    k = 0
    for i in range(size):
        if rank[i] == size - 1:
            lcp[rank[i]] = -1
            k = 0
        else:
            # Index of smallest suffix s[j...n] lexiographically greater than current suffix s[i...n]
            j = suffix_array[rank[i] + 1]
            while j + k < size and i + k < size and s[i + k] == s[j + k]:
                k += 1
            
            lcp[rank[i]] = k

            if k > 0:
                k -= 1
    
    return lcp



