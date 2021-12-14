
class Segment_Node:
    '''
        Represents a node in a segment tree
    '''
    def __init__(self):
        self.left_index = 0
        self.right_index = 0
        self.data = None
        self.left_child = None
        self.right_child = None


class Segment_Tree:
    '''
        Takes an array of elements, placeholder value and function that
        compares two values or returns a different value is given in constructor
        The placeholder value is used when no other value is possible
    '''

    def __init__(self, array:list, placeholder, operation):
        self.root = None
        self.placeholder = placeholder
        self.size = len(array)
        self.operation = operation

        self.__build__(array)
    

    def __build__(self, array:list):
        '''
            Builds the segment tree from the given array
        '''
        self.root = Segment_Node()

        def divide(cur:Segment_Node, left:int, right:int):
            if left == right:
                cur.data = array[left]
            else:
                mid = (left + right) // 2
                cur.left_child = Segment_Node()
                cur.right_child = Segment_Node()

                divide(cur.left_child, left, mid)
                divide(cur.right_child, mid + 1, right)
                cur.data = self.operation(cur.left_child.data, cur.right_child.data)
            
            cur.left_index = left
            cur.right_index = right

        divide(self.root, 0, self.size - 1)    


    def __range__(self, cur:Segment_Node, left:int, right:int):
        '''
            Returns the value after performing the given operation
            between the elements in the range
        '''
        if left > right:
            return self.placeholder

        if cur is None:
            raise RuntimeError("A none object is being referenced")
        
        if cur.left_child == None and cur.right_child == None:
            return cur.data

        if left == cur.left_index and right == cur.right_index:
            return cur.data
        
        
        mid = (cur.left_index + cur.right_index) // 2
        left_range_end = min(mid, right)
        right_range_begin = max(mid + 1, left)

        left_range = self.__range__(cur.left_child, left, left_range_end)
        right_range = self.__range__(cur.right_child, right_range_begin, right)

        return self.operation(left_range, right_range)
    

    def __change_value__(self, cur:Segment_Node, index:int, new_data):
        '''
            Changes the value at given index to new data
        '''
        if cur.left_index == index and cur.right_index == index:
            cur.data = new_data
        else:
            mid = (cur.left_index + cur.right_index) // 2
            if index <= mid:
                self.__change_value__(cur.left_child, index, new_data)
            else:
                self.__change_value__(cur.right_child, index, new_data)
            cur.data = self.operation(cur.left_child.data, cur.right_child.data)
    

    def __check_index__(self, index:int):
        '''
            Pseudo Bound checking
        '''
        if index >= self.size:
            raise ValueError("Index out of range")


    def range_operation(self, left:int, right:int):
        '''
            Performs the operation on elements in the given range
            and returns the result
        '''
        self.__check_index__(left)
        self.__check_index__(right)
        return self.__range__(self.root, left, right)
    

    def update(self, index:int, new_data):
        '''
            Updates the data at given index to new data
        '''
        self.__check_index__(index)
        self.__change_value__(self.root, index, new_data)


if __name__ == "__main__":
    def f(a:int, b:int):
        return a if a > b else b
    from math import inf
    l = [int(x) for x in input().split()]
    t = Segment_Tree(l, -inf, f)

    print(t.range_operation(2, 3))
    t.update(3, 100)
    print(t.range_operation(0, 3))
    

