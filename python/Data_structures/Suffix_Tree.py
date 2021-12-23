

class Node:
    def __init__(self, parent = None, start = -1, end = -1):
        self.start = start
        self.end = end
        self.length = self.end - self.start
        self.suffix_link = None
        self.parent = parent
        self.is_leaf = True

        self.edges = {'\0' : self }
    
    def update_indices(self, start, end):
        self.start = start
        self.end = end
        self.length = self.end - self.start


class Active:
    def __init__(self):
        self.node = None
        self.edge = '\0'
        self.length = 0
    
    def set_point(self, node:Node, edge:str, length:int):
        self.node = node
        self.edge = edge
        self.length = length
    

class Suffix_Tree:
    def __init__(self, s:str, delimiter:str = '$', max_char_code:int = 256):
        self.root = Node()
        self.root.parent = self.root
        self.root.suffix_link = self.root
        
        self.text = s + delimiter
        self.size = len(self.text)

        self.remainder = 0

        self.active = Active()
        self.active.set_point(self.root, '\0', 0)

        self.max_char_code = max_char_code
        self.__create_suffix_tree__()
    

    def __can_split__(self, cur:Node):
        return cur.start + self.active.length < cur.end
    

    def __insert_node__(self, current:Node, start:int, end:int):
        
        new_node = Node(current, start, end)
        new_node.suffix_link = self.root
        
        current.edges[self.text[start]] = new_node
        current.is_leaf = False

    
    def __split_node__(self, cur:Node, prev_split:Node = None):

        new_node = Node(cur.parent, cur.start, cur.start + self.active.length)
        cur.parent.edges[self.text[cur.start]] = new_node

        cur.update_indices(new_node.end, cur.end)
        new_node.edges[self.text[cur.start]] = cur
        cur.parent = new_node

        new_node.suffix_link = cur.suffix_link
        cur.suffix_link = self.root
        new_node.is_leaf = False

        if not prev_split is None:
            prev_split.suffix_link = new_node
        
        return new_node


    def __is_in_active_edge__(self, index:int):
        cur = self.active.node
        if self.active.edge == '\0' and self.active.length == 0:
            return (self.text[index] in cur.edges)
        else:
            if self.active.edge in cur.edges:
                temp = cur.edges[self.active.edge]
                char_index = temp.start + self.active.length

                if char_index > temp.end:
                    raise RuntimeError("Invalid edge is being used")

                if char_index == temp.end:
                    return (self.text[index] in temp.edges)
                
            
                return self.text[char_index] == self.text[index]
        return False
    

    def __insert__(self, index):
        last_node = None
        prev_index = index - self.remainder + 1
        
        while self.remainder > 0:
            temp = None
            prev_index += 1
            
            if self.__is_in_active_edge__(index):
                cur = self.active.node.edges[self.active.edge]
                
                if self.active.length + 1 == cur.length:
                    self.active.set_point(
                        cur, 
                        self.text[index], 
                        1)
                elif self.active.length > cur.length:
                    # TODO: Handle node transitions
                    pass
                else:
                    self.active.set_point(
                        self.active.node, 
                        self.active.edge, 
                        self.active.length + 1)

                if not last_node is None:
                    last_node.suffix_link = self.active.node
                
                break

            else:
                
                if self.active.edge in self.active.node.edges:
                    temp = self.active.node.edges[self.active.edge]
                else:
                    temp = self.active.node

                if self.__can_split__(temp):
                    temp = self.__split_node__(temp, last_node)
                
                self.__insert_node__(temp, index, self.size)
                self.remainder -= 1

                if self.active.node == self.root and self.active.length > 0:
                    last_node = temp
                    self.active.set_point(
                        self.root,
                        self.text[prev_index] if prev_index <= index else '\0',
                        self.active.length - 1
                    )
                if self.active.node != self.root:
                    self.active.set_point(
                        self.active.node.suffix_link,
                        self.active.edge,
                        self.active.length
                    )
                
                if self.active.length == 0:
                    self.active.set_point(
                        self.active.node,
                        '\0',
                        0
                    )
            

    def __create_suffix_tree__(self):
        for i in range(self.size):
            self.remainder = (1 if self.remainder <= 0 else self.remainder + 1)
            self.__insert__(i)
    

    def __dfs__(self, current:Node, s:str, result:list):
        if current is None:
            return
        
        append = ""
        if current != self.root:
            append = self.text[current.start:current.end] 
        # print(append)
        s += append
        for i in range(1, self.max_char_code):
            if chr(i) in current.edges:
                self.__dfs__(current.edges[chr(i)], s, result)
        
        if current.is_leaf:
            result.append(s)
    

    def get_suffix_strings(self):
        result = list()
        self.__dfs__(self.root, "", result) 

        # result.pop(0)
        # for i in result:
        #     i.removesuffix('$')
        
        return result




if __name__ == "__main__":
    s = input()
    st = Suffix_Tree(s)
    j = 0
    for i in st.get_suffix_strings():
        print(i)
        j += 1
    print(len(s), j)