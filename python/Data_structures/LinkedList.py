class LinkedNode:

    def __init__(self, value):
        self.next = None
        self.prev = None
        self.value = value
    


class LinkedList:

    
    def __init__(self):
        self.size = 0
        self.tail = None
        self.head = None
    

    
    def addNodeLast(self, value):
        '''
            Inserts the givent value at the end of the linked list.
        '''
        node = LinkedNode(value)
        
        if self.tail != None:
            node.prev = self.tail
            self.tail.next = node
        
        else:
            self.head = node
        
        self.tail = node
        self.size += 1


    def deleteNode(self, node):
        '''
            Deletes a given node from the list and restructures the list
        '''
        if node == None:
            return

        if node == self.head:
            self.head = node.next
            self.head.prev = None
        
        elif node == self.tail:
            self.tail = node.prev
            self.tail.next = None
        
        else:
            node.next.prev = node.prev
            node.prev.next = node.next

    
    #Searching for a node with a given value
    #Returns none if value is not found in the linkedlist
    def searchForNode(self, value):
        '''
            Searches for a node with given value
            Returns node if the value is present
            Else null
        '''
        current_node = self.head
        while current_node != None and current_node.value != value:
            current_node = current_node.next
        return current_node


    def listRange(self):
        '''
            Yields the content of the list in forward manner
            Useful for use in enumeration loops
        '''
        temp = self.head
        while temp != None:
            yield temp
            temp = temp.next