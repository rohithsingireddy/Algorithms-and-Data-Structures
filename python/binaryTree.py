
class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.parent = None
    

    def next(self, value):
        if value < self.value:
            return self.left
        else:
            return self.right




class BinTree:
    def __init__(self):
        self.root = None
    
    #inserting into the tree
    def insert(self, value):
        if self.root == None:
            self.root = TreeNode(value)
            return
        
        currentNode = self.root
        
        while currentNode.next(value) != None:
            currentNode = currentNode.next(value)
        
        node = TreeNode(value)
        if value < currentNode.value:
            currentNode.left = node
        else:
            currentNode.right = node
        node.parent = currentNode

    #Replace a subtree with another sub tree( can be a null sub tree)
    def transplant(self, nodeToReplace, replacingNode):
        if nodeToReplace.parent == None:
            self.root = replacingNode
        elif nodeToReplace == nodeToReplace.parent.left:
            nodeToReplace.parent.left = replacingNode
        else:
            nodeToReplace.parent.right = replacingNode
        
        if replacingNode != None:
            replacingNode.parent = nodeToReplace.parent

    #Deleting a Node in the tree
    def delete(self, node):
        if node.left == None:
            self.transplant(node, node.right)
        elif node.right == None:
            self.transplant(node, node.left)
        else:
            
            successorOfNode = node.right
            while successorOfNode.left != None:
                successorOfNode = successorOfNode.left
            
            if successorOfNode.parent != node:
                self.transplant( successorOfNode, successorOfNode.right)
                successorOfNode.right = node.right
                successorOfNode.right.parent = successorOfNode
            
            self.transplant( node, successorOfNode )
            successorOfNode.left = node.left
            successorOfNode.left.parent = successorNode


    #Searching for a node with given value
    def search_tree(self, value):
        currentNode = self.root
        while currentNode != None:
            if currentNode.value == value:
                return currentNode
            elif value < currentNode.value:
                currentNode = currentNode.left
            else:
                currentNode = currentNode.right
        return None

    #printing the content of the tree in 'Inorder'
    def print_node_values(self, node):
        if node != None:
            self.print_node_values(node.left)
            print(node.value, end=' ')
            self.print_node_values(node.right)
