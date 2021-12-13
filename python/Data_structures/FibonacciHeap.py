from math import ceil, log
from LinkedList import LinkedList

'''
    The logic is wrong but it works for small inputs
    Somewhat different from cpp implementation
    Program terminates but I have yet to verify the correctness of the program
    TODO: Implement bound checks
'''

class Fib_Node:
    def __init__(self):
        self.parent = None
        self.children = set()
        self.key = None
        self.data = None
        self.degree = 0
        self.mark = False


    def insert(self, key, data):
        '''
            Inserts key and data into the node
        '''
        self.key = key
        self.data = data


    def __str__(self):
        '''
            Returns string representation of key and data
        '''
        return str(self.key) + str(self.data)




class FibonacciHeap:
    def __init__(self):
        self.min = None
        self.no_of_nodes = 0
        self.root_list = LinkedList()
        self.index = 0
        self.node_dict = {}


    def link(self, child:Fib_Node, parent:Fib_Node):
        '''
            Helper function to connect two nodes of same degree
            and create a parent child relationship between them 
            based on their keys
        '''
        self.root_list.deleteNode(child)
        parent.children.add(child)
        child.parent = parent
        parent.degree += 1
        child.mark = False


    def cut(self, child:Fib_Node, parent:Fib_Node):
        '''
            Helper function to take a child of node in heap and 
            add it to the root list in case it has lower key than
            the parent
        '''
        parent.children.remove(child)
        parent.degree -= 1
        self.root_list.addNodeLast(child)
        child.parent = None
        child.mark = False


    def cascading_cut(self, parent:Fib_Node):
        '''
            Helper function to recursively implement the cut
            until the heap property is maintained
        '''
        grand_parent = parent.parent
        if grand_parent != None:
            if not parent.mark:
                parent.mark = True
            else:
                self.cut(parent, grand_parent)
                self.cascading_cut(grand_parent)

        
    def consolidate(self):
        '''
            Helper function to maintain the heap rule
            in the tree after extracting the min node
        '''
        degree_dict = {}
        for current in self.root_list:
            
            current_degree = current.degree
            if current_degree not in degree_dict:
                degree_dict[current_degree] = None
            
            while degree_dict[current_degree] != None:
                another_node = degree_dict[current_degree]
                
                if current.key > another_node.key:
                    current, another_node = another_node, current
                
                self.link(another_node, current)
                degree_dict[current_degree] = None
                
                current_degree += 1
                if current_degree not in degree_dict:
                    degree_dict[current_degree] = None
            
            degree_dict[current_degree] = current
        
        self.min = None
        for current in degree_dict.values():
            if current != None:
                if self.min == None:
                    self.root_list = LinkedList()
                    self.root_list.addNodeLast(current)
                    self.min = current
                else:
                    self.root_list.addNodeLast(current)
                    
                    if current.key < self.min.key:
                        self.min = current
        
        
    def check_index(self, index:int):
        '''
            Pseudo bound checking for node dict
        '''
        if not index in self.node_dict:
            raise Exception("Index out of range")
    

    def insert(self, key, data):
        '''
            Inserts the key and data into a fib node and 
            then inserts the node into the heap
        '''
        created_node = Fib_Node()
        created_node.insert(key, data)
        
        if (self.min == None or (self.min != None and self.min.key > key)):
            self.min = created_node
        
        
        self.root_list.addNodeLast(created_node)
        self.no_of_nodes += 1
        self.node_dict.update({self.index : created_node})
        self.index += 1
        return self.index - 1


    def heap_union(self, heap1):
        '''
            Connects another finbonacci heap to this heap
            The other heaps elements cannot be modified after
            this operation
        '''
        self.root_list.merge(heap1.root_list)
        if self.min == None or ( heap1.min != None and self.min.key > heap1.min.key):
            self.min = heap1.min
        self.no_of_nodes += heap1.no_of_nodes


    def is_empty(self):
        '''
            Returns true if heap is empty
        '''
        return self.no_of_nodes == 0


    def extract_min(self):
        '''
            Gets the minimum node( or root node )
            and returns its key and data
            Throws an exception if heap is empty
        '''
        if self.is_empty():
            raise Exception("Empty heap\n")
        top = self.min
        key, data  = None, None
        
        if top != None:
            for child in top.children:
                self.root_list.addNodeLast(child)
            self.root_list.deleteNode(top)

            self.min = None
            self.consolidate()
            key, data = top.key, top.data
        
        self.no_of_nodes -= 1
        return key, data

    
    def decrease_key(self, index_of_key, new_key):
        '''
            Takes an index of node and new key to decrease
            the key. 
            Throws an exception if new key is greater than current key
        '''
        self.check_index(index_of_key)
        node = self.node_dict[index_of_key]

        if new_key > node.key:
            raise Exception("Cannot update key with a greater key\n")
        
        node.key = new_key
        parent = node.parent

        if parent != None and node.key < parent.key:
            self.cut(node, parent)
            self.cascading_cut(parent)
        
        if node.key < self.min.key:
            self.min = node
    

    def delete_node(self, node_index:int, lowest_key_possible):
        '''
            Deleting node is best done in program that uses 
            this class. 
        '''
        self.check_index(node_index)
        self.decrease_key(node_index, lowest_key_possible)
        self.extract_min()


