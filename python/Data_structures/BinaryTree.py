
class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.parent = None
    

    def next(self, value):
        '''
            Returns the next child to consider given the value
            If value is less than node, left child is returned 
            Else right child is returned
        '''    
        if value < self.value:
            return self.left
        else:
            return self.right




class BinTree:
    
    def __init__(self):
        self.root = None
    

    def insert(self, value):
        '''
            Takes a comparable object and inserts into the tree
        '''
        if self.root == None:
            self.root = TreeNode(value)
            return
        
        current_node = self.root
        
        while current_node.next(value) != None:
            current_node = current_node.next(value)
        
        node = TreeNode(value)
        if value < current_node.value:
            current_node.left = node
        else:
            current_node.right = node
        node.parent = current_node

    
    
    def transplant(self, node_to_replace, replacing_node):
        '''
            Takes two sub-trees and replaces a tree with another tree
        '''
        if node_to_replace.parent == None:
            self.root = replacing_node
        
        elif node_to_replace == node_to_replace.parent.left:
            node_to_replace.parent.left = replacing_node
        
        else:
            node_to_replace.parent.right = replacing_node
        
        if replacing_node != None:
            replacing_node.parent = node_to_replace.parent
    
   
    
    def get_successor_of_node(self, node):
        '''
            Gets the lowest node which is greater than the given node in comparable value
        '''
        if node == None:
            return None

        if node.right != None:
            successor_of_node = node.right
            while successor_of_node.left != None:
                successor_of_node = successor_of_node.left
            return successor_of_node
        
        else:
            #Finding the lowest value that is greater than node valule in its parent subtree
            current_node = node
            parent_of_current_node = current_node.parent
            while parent_of_current_node != None and current_node == parent_of_current_node.right:
                current_node = parent_of_current_node
                parent_of_current_node = current_node.parent
            return parent_of_current_node


    
    def delete(self, node):
        '''
            Deletes a given node from the tree and restructures the tree
        '''
        if node.left == None:
            self.transplant(node, node.right)
        elif node.right == None:
            self.transplant(node, node.left)
        else:
            # Both left and right nodes are present for the node to be deleted
            successor_of_node = node.right
            while successor_of_node.left != None:
                successor_of_node = successor_of_node.left
            
            if successor_of_node.parent != node:
                self.transplant( successor_of_node, successor_of_node.right)
                successor_of_node.right = node.right
                successor_of_node.right.parent = successor_of_node
            
            self.transplant( node, successor_of_node )
            successor_of_node.left = node.left
            successor_of_node.left.parent = successorNode


    
    def search_tree(self, value):
        '''
            Searching for a node with given value
            Returns None if value cannot be found
        '''
        current_node = self.root
        while current_node != None:
            if current_node.value == value:
                return current_node
            elif value < current_node.value:
                current_node = current_node.left
            else:
                current_node = current_node.right
        return None


    
    def print_node_values(self, node):
        '''
            Prints the values of the node through inorder traversal
        '''
        if node != None:
            self.print_node_values(node.left)
            print(node.value, end=' ')
            self.print_node_values(node.right)

