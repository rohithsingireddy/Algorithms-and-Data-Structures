from enum import Enum

class Node_Color(Enum):
    '''
        Represents a node color
    '''
    RED = 1
    BLACK = 2



class Node:
    '''
        Represents a node in a tree
    '''
    def __init__(self, key, data):
        '''
            Default Constructor
        '''
        self.key = key
        self.data = data
        self.left_child = None
        self.right_child = None
        self.parent = None
        self.color = Node_Color.RED




class Red_Black_Tree:
    '''
        A self-balancing binary tree
    '''
    def __init__(self):
        self.NIL = Node(None,None)
        self.NIL.left_child = self.NIL
        self.NIL.right_child = self.NIL
        self.NIL.parent = self.NIL
        self.NIL.color = Node_Color.BLACK
        self.root = self.NIL
    
    def __left_rotate__(self, current:Node):
        '''
            Left rotates a node in tree by replacing its position
            with its right child and making the given node the left
            child of the replacing ndoe
        '''
        right = current.right_child
        current.right_child = right.left_child

        if right.left_child != self.NIL:
            right.left_child.parent = current
        
        right.parent = current.parent
        if current.parent == self.NIL:
            self.root = right
        elif current.parent.right_child == current:
            current.parent.right_child = right
        else:
            current.parent.left_child = right

        right.left_child = current
        current.parent = right


    def __right_rotate__(self, current:Node):
        '''
            Right rotates a node in a tree by replacing its position
            with its left child and making the given node the right
            child of the replacing ndoe
        '''
        left = current.left_child
        current.left_child = left.right_child

        if left.right_child != self.NIL:
            left.right_child.parent = current
        
        left.parent = current.parent
        if current.parent == self.NIL:
            self.root = left
        elif current.parent.left_child == current:
            current.parent.left_child = current
        else:
            current.parent.right_child = current
        
        left.right_child = current
        current.parent = left


    def __rb_insert__(self, new_node:Node):
        '''
            Inserts a node into the tree
        '''
        trailing = self.NIL
        cur = self.root

        while cur != self.NIL:
            trailing = cur
            if new_node.key < cur.key:
                cur = cur.left_child
            else:
                cur = cur.right_child
        new_node.parent = trailing
        if trailing == self.NIL:
            self.root = new_node
        elif new_node.key < trailing.key:
            trailing.left_child = new_node
        else:
            trailing.right_child = new_node
        new_node.left_child = self.NIL
        new_node.right_child = self.NIL
        self.__rb_insert_fixup__(new_node)
    
    
    def __rb_insert_fixup__(self, current:Node):
        '''
            Fixes up the tree so that the tree remains balanced
            after insertion
        '''
        while current.parent.color == Node_Color.RED:
            grand_parent = current.parent.parent
            
            if grand_parent.left_child == current.parent:
                right = grand_parent.right_child

                if right.color == Node_Color.RED:
                    current.parent.color = Node_Color.BLACK
                    right.color = Node_Color.BLACK
                    grand_parent.color = Node_Color.RED
                    current = grand_parent
                else:
                    if current == current.parent.right_child:
                        current = current.parent
                        self.__left_rotate__(current)
                    
                    current.parent.color = Node_Color.BLACK
                    grand_parent = current.parent.parent
                    grand_parent.color = Node_Color.RED
                    self.__right_rotate__(grand_parent)
            
            else:
                left = grand_parent.left_child

                if left.color == Node_Color.RED:
                    current.parent.color = Node_Color.BLACK
                    left.color = Node_Color.BLACK
                    grand_parent.color = Node_Color.RED
                    current = grand_parent
                else:
                    if current == current.parent.left_child:
                        current = current.parent
                        self.__right_rotate__(current)
                    
                    current.parent.color = Node_Color.BLACK
                    grand_parent = current.parent.parent
                    grand_parent.color = Node_Color.RED
                    self.__left_rotate__(grand_parent)
        
        self.root.color = Node_Color.BLACK


    def __rb_transplant__(self, replaced:Node, replacing:Node):
        '''
            Replaces a node with another node
        '''
        if replaced.parent == self.NIL:
            self.root = replacing
        elif replaced.parent.left_child == replaced:
            replaced.parent.left_child = replacing
        else:
            replaced.parent.right_child = replacing
        replacing.parent = replaced.parent
    

    def __min_in_tree__(self, current:Node):
        '''
            Returns the minimum node in a given subtree
        '''
        if current.left_child == self.NIL:
            return current
        return self.__min_in_tree__(current.left_child)
    

    def __max_in_tree__(self, current:Node):
        '''
            Returns the maximum node in a given subtree
        '''
        if current.right_child == self.NIL:
            return current
        return self.__max_in_tree__(current.right_child)
    

    def __rb_delete__(self, del_node:Node):
        '''
            Deletes a given node in the sub-tree
        '''
        orginal_color = del_node.color
        next_node = None

        if del_node.left_child == self.NIL:
            next_node = del_node.right_child
            self.__rb_transplant__(del_node, next_node)
        elif del_node.right_child == self.NIL:
            next_node = del_node.left_child
            self.__rb_transplant__(del_node, next_node)
        else:
            successor = self.__min_in_tree__(del_node.right_child)
            orginal_color = successor.color
            next_node = successor.right_child

            if successor.parent == del_node:
                next_node.parent = successor
            else:
                self.__rb_transplant__(successor, successor.right_child)
                successor.right_child = del_node.right_child
                successor.right_child.parent = successor
            
            self.__rb_transplant__(del_node, successor)
            successor.left_child = del_node.left_child
            successor.left_child.parent = successor
            successor.color = del_node.color

        if orginal_color == Node_Color.BLACK:
            self.__rb_delete_fixup__(next_node)
        
        del del_node
    

    def __rb_delete_fixup__(self, current):
        '''
            Keeps the tree balanced in case of red tree rule violation
            after a node deletion
        '''
        while current != self.root and current.color == Node_Color.BLACK:
            if current == current.parent.left_child:
                right = current.parent.right_child

                if right.color == Node_Color.RED:
                    right.color = Node_Color.BLACK
                    current.parent.color = Node_Color.RED
                    self.__left_rotate__(current.parent)
                    right = current.parent.right_child
                
                if (right.left_child.color == Node_Color.BLACK and 
                    right.right_child.color == Node_Color.BLACK):
                    right.color = Node_Color.RED
                    current = current.parent
                
                else:
                    if right.right_child.color == Node_Color.BLACK:
                        right.left_child.color = Node_Color.BLACK
                        right.color = Node_Color.RED
                        self.__right_rotate__(right)
                        right = current.parent.right_child
                    
                    right.color = current.parent.color
                    current.parent.color = Node_Color.BLACK
                    right.right_child.color = Node_Color.BLACK
                    self.__left_rotate__(current.parent)
                    current = self.root

            else:
                left = current.parent.left_child
                if left.color == Node_Color.RED:
                    left.color = Node_Color.BLACK
                    current.parent.color = Node_Color.RED
                    self.__right_rotate__(current.parent)
                    left = current.parent.left_child
                
                if (left.left_child.color == Node_Color.BLACK and
                    left.right_child.color == Node_Color.BLACK):
                    left.color = Node_Color.RED
                    current = current.parent
                else:
                    if left.left_child.color == Node_Color.BLACK:
                        left.right_child.color = Node_Color.BLACK
                        left.color = Node_Color.RED
                        self.__left_rotate__(left)
                        left = current.parent.left_child
                    
                    left.color = current.parent.color
                    current.parent.color = Node_Color.BLACK
                    left.left_child.color = Node_Color.BLACK
                    self.__right_rotate__(current.parent)
                    current = self.root
        
        current.color = Node_Color.BLACK


    def __rb_search__(self, key):
        '''
            Searches for a node with the given key and returns it.
            If node does not exist, returns NIL
        '''
        current = self.root
        while current != self.NIL:
            if key == current.key:
                return current
            elif key < current.key:
                current = current.left_child
            else:
                current = current.right_child
        
        return current


    

    def __predecessor_of__(self, current:Node):
        '''
            Returns a node that is the greatest value less than the
            given node's key
        '''
        if current.left_child != self.NIL:
            return self.__max_in_tree__(current.left_child)
        current_parent = current.parent
        while current_parent != self.NIL and current_parent.left_child ==current:
            current = current_parent
            current_parent = current.parent
        return current_parent
    

    def __successor_of__(self, current:Node):
        '''
            Returns a node that is the least value greater than the
            given node's key
        '''
        if current.right_child != self.NIL:
            return self.__min_in_tree__(current.right_child)
        current_parent = current.parent
        while current_parent != self.NIL and current_parent.right_child == current:
            current = current_parent
            current_parent = current.parent
        return current_parent

    
    def insert(self, key, data):
        '''
            Inserts the key and data into the tree
        '''
        new_node = Node(key, data)
        self.__rb_insert__(new_node)
    

    def remove(self, key):
        '''
            Removes a node with given key in the tree if it exists
            Otherwise does nothing
        '''
        cur = self.__rb_search__(key)
        if cur != self.NIL:
            self.__rb_delete__(cur)
    

    def search(self, key):
        '''
            Returns data associated with key along with key if key is in tree
            Else throws an exception
        '''
        searched_node = self.__rb_search__(key)
        if searched_node == self.NIL:
            raise RuntimeError("Key is not in tree\n")
        return key, searched_node.data


    def get_predecessor(self, key):
        '''
            Returns the lower bound of given key in tree
        '''
        searched_node = self.__rb_search__(key)
        inserted_node = self.NIL
        if searched_node == self.NIL:
            inserted_node = Node(key, None)
            self.__rb_insert__(inserted_node)
            searched_node = inserted_node
        
        pred_node = self.__predecessor_of__(searched_node)
        result = (pred_node.key , pred_node.data)

        if inserted_node != self.NIL:
            self.__rb_delete__(inserted_node)
        
        return result

    
    def get_successor(self, key):
        '''
            Returns the upper bound of given key in tree
        '''
        searched_node = self.__rb_search__(key)
        inserted_node = self.NIL
        if searched_node == self.NIL:
            inserted_node = Node(key, None)
            self.__rb_insert__(inserted_node)
            searched_node = inserted_node
        
        succ_node = self.__successor_of__(searched_node)

        result = (succ_node.key, succ_node.data)

        if inserted_node != self.NIL:
            self.__rb_delete__(inserted_node)
        
        return result



    def preorder_traversal(self) -> list:
        '''
            Preorder Traversal
            Returns the elements as key, data tuples in preorder traversal
        '''
        result = list()
        stack = list()
        
        if self.root != self.NIL:
            stack.append(self.root)
            
            while len(stack) > 0:
                current = stack.pop()
                result.append(tuple([current.key, current.data]))
                
                if current.right_child != self.NIL:
                    stack.append(current.right_child)
                
                if current.left_child != self.NIL:
                    stack.append(current.left_child)
        
        return result
    

    def inorder_traversal(self) -> list:
        '''
            Inorder Traversal
            Returns all the key and data in a list of tuples
        '''
        result, stack = list(), list()

        current = self.root
        while len(stack) > 0 or current != self.NIL:
            if current != self.NIL:
                stack.append(current)
                current = current.left_child
            else:
                top = stack.pop()
                result.append(tuple([top.key, top.data]))
                current = top.right_child
        
        return result

    
    def postorder_traversal(self) -> list:
        '''
            Post Order Traversal
            Returns all the keys and data pairs in a vector
        '''
        result, stack = list(), list()

        current, last_node = self.root, self.NIL
        while current != self.NIL or len(stack) > 0:
            if current != self.NIL:
                stack.append(current)
                current = current.left_child
            else:
                top = stack[-1]
                if top.right_child != self.NIL and last_node != top.right_child:
                    current = top.right_child
                else:
                    result.append(tuple([top.key, top.data]))
                    last_node = top
                    stack.pop()
        
        return result
    

    def contains(self, key):
        return self.__rb_search__(key) == self.NIL



if __name__ == "__main__":
    rb = Red_Black_Tree()
    for i in range(100):
        rb.insert(i, i)
    
    for i in range(1, 100, 2):
        rb.remove(i)
    
    print(rb.get_predecessor(0))
    print(rb.get_successor(99))

    for i in rb.inorder_traversal():
        print(i[0], end=' ')



