from LinkedList import LinkedList

'''
    TODO: Bounding inputs and more unit tests
'''


class Set_node:
    '''
        Helper class for storing individual nodes
    '''
    def __init__(self):
        self.rank = 0
        self.children = LinkedList()
        self.data = None
        self.parent = self
    
    def insert(self, data):
        self.data = data
        self.children.addNodeLast(self)
    
    def __str__(self):
        return str(self.data)


class DisjointSetTree:
    def __init__(self):
        self.nodes = []
        self.size = 0
    
    def find_set(self, node:Set_node) -> Set_node:
        '''
            Takes a Set_node as input
            Find parent( or representative of set it belongs to) of node
        '''
        if node != node.parent:
            node.parent = self.find_set(node.parent)
        return node.parent
    
    def find_parent(self, index:int):
        '''
            Takes set index as input
            Returns the parent of set it belongs to
        '''
        return self.find_set(self.nodes[index])
    
    def union_sets(self, i:int, j:int):
        '''
            Takes indices of sets( indices based on insertion order) as input
            Connects sets of i and j if they are disjoint. Otherwise does nothing.
        '''
        x = self.nodes[i]
        y = self.nodes[j]
        x_parent = self.find_set(x)
        y_parent = self.find_set(y)

        if x_parent == y_parent:
            return 
        if x_parent.rank > y_parent.rank:
            y_parent.parent = x_parent
            x_parent.children.merge(y_parent.children)
        else:
            x_parent.parent = y_parent
            y_parent.children.merge(x_parent.children)
            if x_parent.rank == y_parent.rank:
                y_parent.rank +=  1
    
    def insert(self, data):
        '''
            Takes an object as input
            Inserts the objects into seperate disjoint sets and
            returns its set number
        '''
        node = Set_node()
        node.insert(data)
        self.nodes.append(node)
        self.size += 1
        return self.size - 1
    
    def get_set_data(self, set_number):
        '''
            Takes a set number as input
            Returns the set elements if the given set number is a parent
            Otherwise returns an empty list
        '''
        s = self.nodes[set_number]
        parent = self.find_set(s)
        result = []

        if parent != s:
            return result
        
        return parent.children
    



if __name__ == '__main__':
    s = DisjointSetTree()
    n = int(input())
    s.insert(0)
    s.insert(1)
    index = 2
    while n != -1:
        s.insert(n)
        if n % 2 == 0:
            s.union_sets(index, 0)
        else:
            s.union_sets(index, 1)
        index += 1
        n = int(input())
    
    for i in s.get_set_data(0):
        print(i, end=' ')
    print()
    for i in s.get_set_data(1):
        print(i, end=' ')

    
