

def insertion_sort(array:list):
    '''
        Takes a list as input and uses insertion sort to sort the list
    '''
    size =  len(array)
    for i in range(1,size):
        current = array[i]
        j = i - 1
        while j >= 0 and array[j] > current:
            array[j+1] = array[j]
            j -= 1
        array[j+1] = current


def selection_sort(array:list):
    '''
        Takes a list as input and uses selection sort to sort the list
    '''    
    size = len(array)
    for i in range(size - 1):
        min_index = i
        for j in range(i, size):
            if array[min_index] > array[j]:
                min_index = j
    
        array[min_index], array[i] = array[i], array[min_index]


def quick_sort(array:list):
    '''
        Takes a list as input and uses Quick sort to sort the list
    '''
    size = len(array)
    stack = [(0, size-1)]
    while len(stack) != 0:
        start, end = stack.pop()
        pivot = array[end]

        #partition procedure begins
        
        #Index before which elements are less than pivot (Inclusive)
        i = start - 1
        
        for j in range(start, end):
            if array[j] < pivot:
                i += 1
                array[j], array[i] = array[i], array[j]
        
        partition_index = i + 1
        array[partition_index], array[end] = array[end], array[partition_index]
        #partition procedure ends

        if start < partition_index - 1:
            stack.append((start, partition_index - 1))
        
        if partition_index + 1 < end:
            stack.append((partition_index + 1, end))


def count_sort(array:list, max_value:int, be_stable:bool = True):
    '''
        Takes array and maximum value of list as input and uses count sort to sort the list
        Count sort can only be used when the values to be sorted are non-negative integers and the 
        max value of the values is known. 
    '''
    size = len(array)

    counting_array = [0 for _ in range(max_value+1)]

    for i in array:
        counting_array[i] += 1
    
    for i in range(1, max_value+1):
        counting_array[i] += counting_array[i-1]
    
    sorted_array = [0 for _ in range(size)]

    if be_stable:
        for i in reversed(array):
            counting_array[i] -= 1
            sorted_array[counting_array[i]] = i
    else:
        for i in array:
            counting_array[i] -= 1
            sorted_array[counting_array[i]] = i
    
    for i in range(size):
        array[i] = sorted_array[i]



def radix_sort(array:list, max_digits:int = 10):
    '''
        Uses Radix sort to sort the list
        Radix sort can only be used with non-negative integers and with the maximum digits used known.
    '''
    class Number:
        def __init__(self, value):
            self.value = value
            self.digit = 0
            self.actual_value = value
        
        def __repr__(self):
            return str(self.actual_value)

    size = len(array)
    number_array = [Number(i) for i in array]
    while max_digits > 0:        
        for i in number_array:
            i.digit = i.value % 10
            i.value //= 10
        
        #Partial sorting through count sort
        counting_array = [0 for _ in range(10)]
        for i in number_array:
            counting_array[i.digit] += 1
        for i in range(1,10):
            counting_array[i] += counting_array[i - 1]
        partial_sorted_array = [None for _ in range(size)]
        for i in reversed(number_array):
            counting_array[i.digit] -= 1
            partial_sorted_array[counting_array[i.digit]] = i
        number_array = partial_sorted_array.copy()
        max_digits -= 1
    
    for i in range(size):
        array[i] = number_array[i].actual_value


def merge_sort(array:list):
    '''
        Takes a list as input and uses merge sort to sort the elements
    '''
    size = len(array)
    
    widths = [1]
    while widths[-1] < size:
        widths.append(widths[-1]*2)
    widths.append(size-1)

    for width in widths:
        for left in range(0, size, width*2):
            
            right = min(left + 2*width - 1, size - 1)
            mid = min(left + width, size - 1)

            left_array = [array[i] for i in range(left, mid)]
            right_array = [array[i] for i in range(mid, right+1)]

            left_index, current_index, right_index = 0, left, 0

            while left_index < len(left_array) and right_index < len(right_array):
                if left_array[left_index] < right_array[right_index]:
                    array[current_index] = left_array[left_index]
                    left_index += 1
                else:
                    array[current_index] = right_array[right_index]
                    right_index += 1
                current_index += 1
            
            while left_index < len(left_array):
                array[current_index] = left_array[left_index]
                left_index += 1
                current_index += 1
            
            while right_index < len(right_array):
                array[current_index] = right_array[right_index]
                right_index += 1
                current_index += 1
        

