class LinkedNode:
    def __init__(self, value):
        self.next = None
        self.prev = None
        self.value = value
    
    def setNext(self, next):
        self.next = next
    
    def setPrev(self, prev):
        self.prev = prev
    

class LinkedList:

    def __init__(self):
        self.size = 0
        self.tail = None
        self.head = None
    
    def addNodeLast(self, value):
        node = LinkedNode(value)
        if self.tail != None:
            node.prev = self.tail
            self.tail.next = node
        else:
            self.head = node
        self.tail = node
        self.size += 1
    
    
    def listRange(self):
        temp = self.head
        while temp != None:
            yield temp
            temp = temp.next