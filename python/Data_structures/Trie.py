class trie_node:
    '''
        A node in a trie data structure
    '''
    def __init__(self):
        self.children = {}
        self.has_value = False
        self.value = None

    def make_or_get_node(self, c: str):
        #TODO: Check Logic
        if c not in self.children:
            self.children[c] = trie_node()
        return self.children[c]

    def remove_child(self):
        '''
            TODO:Implement removing a child
            from the trie node
        '''


class Trie:

    def __init__(self):
        self.root = trie_node()

    def insert(self, key:str, value):
        '''
            Inserts the given value using the given key
        '''
        cur = self.root
        for i in key:
            cur = cur.make_or_get_node(i)
        cur.value = value
        cur.has_value = True

    def contains(self, key:str):
        '''
            Takes a key as input 
            Returns true if the trie contains a value 
            for given key
        '''
        cur = self.root
        for i in key:
            if i not in cur.children:
                return False
            cur = cur.children[i]
        return cur.has_value

    def remove(self, key:str):
        '''
            Removes value associated with given key using lazy removal
            Does nothing if key is not in trie
            TODO: Implement eager removal
        '''
        cur = self.root
        for i in key:
            if i not in cur.children:
                return
            cur = cur.children[i]
        if cur != None:
            cur.value = None
            cur.has_value = False

    def get_value(self, key:str):
        '''
            Takes a string as input
            Throws an exception if key is not in trie
            Returns value associated with key
        '''
        cur = self.root
        for i in key:
            if i not in cur.children:
                raise Exception("Invalid key")
            cur = cur.children[i]
        return cur.value

    def auto_complete(self, key):
        '''
            Takes a string as input
            Returns all the (key, value) pairs who have input string as prefix
        '''
        values = {}
        cur = self.root
        for i in key:
            if i not in cur.children:
                break
            cur = cur.children[i]

        #Helper function for recursively searching for required keys
        def search_values(current, prefix):
            nonlocal values
            if current is not None:
                if current.has_value:
                    values[prefix] = current.value
                for i in current.children:
                    search_values(current.children[i], prefix + i)

        search_values(cur, key)
        return values

    def all_keys_and_values(self):
        '''
            Returns all keys and values currently present in trie
            Returns them in insertion order.
        '''
        return self.auto_complete("")


