'''
    Array uses one-based indexing to access elements
    Implements Max-Heap Tree
    Can be used for max priority queue
'''
class HeapTree:

    def __init__(self, value:int):
        self.array = [0]
        self.heap_size = 0
        self.max_size = value


    def left_child(self, index:int):
        '''
            Returns the possible index of left child
        '''
        return 2 * index


    def right_child(self, index:int):
        '''
            Returns the possible index of right child
        '''
        return 2 * index + 1


    def parent(self, index:int):
        '''
            Returns the possible index of the parent
        '''
        return index // 2


    def max_heapify(self, index:int):
        '''
            Takes index as input
            Recursively "heapifies" the parent and its children
            Recursion stops when the parent is not swapped with one of its children
        '''
        if index > self.heap_size:
            raise Exception('Index out of bounds' + str(index))
            return

        left_index, right_index, largest = self.left_child(index), self.right_child(index), index

        if left_index <= self.heap_size and self.array[largest] < self.array[left_index]:
            largest = left_index
        
        if right_index <= self.heap_size and self.array[largest] < self.array[right_index]:
            largest = right_index
        
        if largest != index:
            self.array[largest], self.array[index] = self.array[index], self.array[largest]
            self.max_heapify(largest)
        

    def build_max_heap(self):
        '''
            Heapifies the entire array to follow the max-heap rule
        '''
        self.heap_size = self.max_size
        for i in range( self.max_size // 2, 0, -1):
            self.max_heapify(i)
    

    def heap_sort(self):
        '''
            Sorts the array by using heap rule
            The array stops being a max heap after the operation
        '''
        self.build_max_heap()
        for i in range(self.max_size, 1, -1):
            self.heap_size -= 1
            self.array[i], self.array[1] = self.array[1], self.array[i]
            self.max_heapify(1)


    def insert(self, value, index = -1):
        '''
            Takes the value and an optional index( less than the heap size ) as input
            If index is given, the value to be overwritten should be less than the value given
        '''
        if  (index > self.heap_size or 
            (index == -1 and 
            self.heap_size + 1 > self.max_size)):
            raise Exception('Index Out of Bounds')
            return

        if index == -1:
            self.array.append(value)
            self.heap_size += 1
            index = self.heap_size
        else:
            if self.array[index] > value:
                raise Exception('Cannot replace with a lower value')
                return
            self.array[index] = value
        
        while self.parent(index) != 0  and self.array[self.parent(index)] < self.array[index]:
            self.array[self.parent(index)], self.array[index] = self.array[index], self.array[self.parent(index)]
            index = self.parent(index)


    def remove(self, index):
        '''
            Removes the element with given index from the tree
            and rearranges the tree accordingly.
        '''
        if( index < 1 and index > max_size):
            raise Exception("Index out of bounds")
            return
        self.array[index], self.array[self.heap_size] = self.array[self.heap_size], self.array[index]
        self.heap_size -= 1
        self.max_heapify(index)
    

    def print_tree(self):
        print(self.array[1:])

