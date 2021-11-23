class LinkedNode:

    def __init__(self, value):
        self.next = None
        self.prev = None
        self.value = value
    


class LinkedList:

    # Initializing variables
    def __init__(self):
        self.size = 0
        self.tail = None
        self.head = None
    

    # Inserting at last of the list
    def addNodeLast(self, value):
        node = LinkedNode(value)
        
        if self.tail != None:
            node.prev = self.tail
            self.tail.next = node
        
        else:
            self.head = node
        
        self.tail = node
        self.size += 1


    #Deleting a given node
    def deleteNode(self, node):
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

    
    #searching for a node with a given value
    def searchForNode(self, value):
        current_node = self.head
        while current_node != None and current_node.value != value:
            current_node = current_node.next
        return current_node


    #For use in 'for' loops
    def listRange(self):
        temp = self.head
        while temp != None:
            yield temp
            temp = temp.next