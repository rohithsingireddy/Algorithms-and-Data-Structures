

def rabin_karp_matching(
        text: str,
        pattern: str,
        max_char: int = 256,
        prime: int = 999983) -> bool:
    '''
        Pattern matching in a string using rabin karp algorithm
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


if __name__ == "__main__":
    s = input()
    p = input()
    for i in kmp_matcher(s, p):
        print(i)
        assert( s[i:(i+len(p))] == p )