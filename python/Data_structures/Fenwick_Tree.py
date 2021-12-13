
class Fenwick_Tree:
    def __init__(self, size):
        self.size = size + 1
        self.array = [0 for _ in range(self.size)]
    

    def __len__(self):
        '''
            Called when len is called on object
        '''
        return self.size
    

    def lsb(self, index:int) -> int:
        '''
            Returns integer value of least significant bit which is 1
            If index is 352(101100000), then return value is 32(100000)
        '''
        return index & -index
    

    def prev(self, index:int) -> int:
        '''
            Returns last index whose element is added to element at given index
        '''
        return index - self.lsb(index)
    

    def next(self, index:int) -> int:
        '''
            Returns next index where element of current index is added
        '''
        return index + self.lsb(index)
    

    def check_index(self, index:int) -> None:
        '''
            Index bound checking
            Throws an exception if index is out of bounds
        '''
        if index < 0 or index >= self.size:
            raise ValueError("Index out of bounds")
    

    def array_to_fenwick(self, array:list) -> None:
        '''
            Converts the given array into a Fenwick array
            Writes over the data present in the object before 
            calling this function
        '''
        self.size = len(array) + 1
        
        self.array = [0]
        for i in array:
            self.array.append(i)

        for i in range(1, self.size):
            next_index = self.next(i)
            if next_index < self.size:
                self.array[next_index] += self.array[i]
        
    
    def add(self, index:int, value:int) -> None:
        '''
            Adds value to element at index and updates the 
            Fenwick tree accordingly
        '''
        index += 1
        self.check_index(index)
        while index < self.size:
            self.array[index] += value
            index = self.next(index)
    

    def insert(self, index:int, value:int) -> None:
        '''
            Replaces old value at index with given value
        '''
        self.add(index, value - self.get_value_at(index))

    
    def range_sum(self, left:int, right:int) -> int:
        '''
            Gets the sum of all elements between left index (inclusive)
            and right index( exclusive)
        '''
        if left > right:
            left, right = right, left
        
        self.check_index(left)
        self.check_index(right)
        s = 0
        while right > left:
            s += self.array[right]
            right = self.prev(right)
        
        while left > right:
            s -= self.array[left]
            left = self.prev(left)
        return s


    def prefix_sum(self, index:int):
        '''
            Gets the sum of all elements between first element and
            (index - 1)th element
        '''
        self.check_index(index)
        s = 0
        while index > 0:
            s += self.array[index]
            index = self.prev(index)
        return s


    def get_value_at(self, index:int) -> int:
        '''
            Gets the value at the given index
        '''
        return self.range_sum(index, index + 1)
    

    def get_array(self) -> list:
        '''
            Returns the orginal values of array
        '''
        array = self.array.copy()
        
        for i in range(self.size - 1, 0, -1):
            next_index = self.next(i)
            if next_index < self.size:
                array[next_index] -= array[i]
        
        array.pop(0)
        return array

    
