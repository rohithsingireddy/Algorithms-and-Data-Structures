from collections import deque
from enum import Enum
from math import inf
from random import random

from DisjointSetTree import DisjointSetTree
from FibonacciHeap import FibonacciHeap


class Node_Color(Enum):
    '''
        For use in BFS and DFS
    '''
    WHITE = 1
    GRAY = 2
    BLACK = 3




class Edge_Type(Enum):
    '''
        Types of edges in graph
        Identified after breadth traversal
    '''
    TREE = 1
    BACK = 2
    FORWARD = 3
    CROSS = 4




class Node:
    '''
        Represents a node in a graph
    '''
    MAX = 1e7

    def __init__(self, index:int):
        #For index of node
        self.label = index

        #Counting ingoing and outgoing edges
        self.in_degree = 0
        self.out_degree = 0

        #Calculated in DFS
        self.start_step = 0
        self.end_step = 0

        #Used in strongly connected component method
        self.pre_order_number = -1
        self.connected_component_label = -1

        #Used in both DFS and BFS
        self.color = Node_Color.WHITE
        self.adjacent_nodes = list()
        self.og_edge_indices = dict()

        #Used for storing the predecessor in traversal
        self.parent_in_traversal = None

        #Calcualted in DFS, BFS, Bellman-Ford and Djikistra
        self.distance_from_source = inf

        self.data = None

    def reset(self):
        '''
            Used for resetting node values before using for certain methods
        '''
        self.start_step = 0
        self.end_step = 0

        self.pre_order_number = -1
        self.connected_component_label = 0

        self.parent_in_traversal = None
        self.distance_from_source = inf




class Edge:
    '''
        Represents a edge in a graph
    '''
    def __init__(self):
        self.from_node = None
        self.to_node = None
        self.weight = 0
        self.type = Edge_Type.CROSS
        self.reverse_edge = False
    
    def insert(self, from_node:Node, to_node:Node, weight:int, reverse_edge:bool):
        self.from_node = from_node
        self.to_node = to_node
        self.weight = weight
        self.reverse_edge = reverse_edge
    
    def __lt__(self, other):
        return self.weight < other.weight



class Graph:

    def __init__(self, no_of_nodes:int, no_of_edges:int, is_directed:bool = False):
        self.no_of_nodes = no_of_nodes
        self.no_of_edges = no_of_edges
        if not is_directed:
            self.no_of_edges *= 2
        self.no_of_type_edges = {x:0 for x in Edge_Type}

        self.is_directed = is_directed

        #For use in inserting edges
        self.edge_index = 0
        
        #This list should not be manipulated or sorted
        self.edges = [Edge() for _ in range(self.no_of_edges)]
        self.nodes = [Node(i) for i in range(self.no_of_nodes)]

        #For use in all pair short paths
        self.predecessor = list()
        self.short_path_weights = list()

        self.nodes_topological = deque()
        self.component = DisjointSetTree()

        for i in range(self.no_of_nodes):
            self.component.insert(i)

        for i in range(self.no_of_nodes):
            self.predecessor.append([-1 for _ in range(self.no_of_nodes)])
            self.short_path_weights.append([inf for _ in range(self.no_of_nodes)])


    def insert_single_edge(self, from_index:int, to_index:int, weight:int, reversed_edge:bool = False):
        '''
            Helper function for inserting one edge into the graph
        '''
        self.nodes[from_index].adjacent_nodes.append(self.nodes[to_index])
        self.nodes[from_index].out_degree += 1
        self.nodes[to_index].in_degree += 1
        self.edges[self.edge_index].insert(self.nodes[from_index], self.nodes[to_index], weight, reversed_edge)
        self.nodes[from_index].og_edge_indices[to_index] = self.edge_index

        self.edge_index += 1
        self.component.union_sets(from_index, to_index)
    

    def check_index(self, index:int):
        '''
            Helper function for checking for index bounds
        '''
        if index >= self.no_of_nodes:
            raise RuntimeError("Index out of bounds")
    

    def get_edges(self):
        '''
            Returning the copy of edges list
        '''
        result = list()
        for i in range(self.no_of_edges):
            if not self.edges[i].reverse_edge:
                result.append(self.edges[i])
        return result


    def get_edges_matrix(self):
        '''
            Gets the matrix representation of edges in graph
        '''
        matrix = list()
        for i in range(self.no_of_nodes):
            matrix.append(list())
            for j in range(self.no_of_nodes):
                matrix[-1].append(0 if i == j else inf)
        
        current_edges = self.get_edges()
        for x in current_edges:
            u = x.from_node.label
            v = x.to_node.label
            matrix[u][v] = x.weight
        
        return matrix

    
    def check_if_st_possible(self):
        '''
            Helper function to check if spanning tree is possible for a given graph
        '''
        if self.is_directed:
            raise ValueError("Cannot find spanning tree for directed graphs")
        
        for i in range(self.no_of_nodes):
            if( self.component.find_parent(0) != self.component.find_parent(i)):
                raise ValueError("Graph is not connected.")
        
        return True
    

    def insert_edge(self, from_index:int, to_index:int, weight:int):
        '''
            Inserts edge into the graph and reverse edge if graph is undirected
        '''
        self.check_index(from_index)
        self.check_index(to_index)

        self.insert_single_edge(from_index, to_index, weight)
        if not self.is_directed:
            self.insert_single_edge(to_index, from_index, weight, True)
    
    
    def reset(self):
        '''
            Resets all the nodes calculated values in the graph 
        '''
        for i in range(self.no_of_nodes):
            self.nodes[i].reset()
    

    def breadth_traversal(self, src_index:int):
        '''
            Breadth First Search
            Takes a source index as input
            Traversed the graph and updates distance from source using BFS
        '''
        self.check_index(src_index)
        self.nodes[src_index].color = Node_Color.GRAY
        self.nodes[src_index].distance_from_source = 0

        dq = deque()
        dq.append(src_index)

        while len(dq) > 0:
            u_index = dq.popleft()
            u = self.nodes[u_index]

            for i in u.adjacent_nodes:
                print( i.label, u.label)
                if i.color == Node_Color.WHITE:
                    i.color = Node_Color.GRAY
                    i.distance_from_source = 1 + u.distance_from_source
                    i.parent_in_traversal = u
                    dq.append(i.label)
            
            u.color = Node_Color.BLACK
    

    def depth_traversal(self, sort_topologically:bool = False):
        '''
            Depth First Search
            Assigns the start_step and end_step for each node
            The assignements are influenced by the ordering of the nodes
        '''
        step = 0
        if sort_topologically:
            self.nodes_topological.clear()
        
        def visit_node(node:Node):
            '''
                Helper function to perform DFS on nodes
            '''
            nonlocal step
            step += 1
            node.start_step = step
            node.color = Node_Color.GRAY
            
            for adj in node.adjacent_nodes:
                index_of_edge = node.og_edge_indices[adj.label]
                edge_type = Edge_Type.CROSS

                if adj.color == Node_Color.WHITE:
                    edge_type = Edge_Type.TREE
                    adj.parent_in_traversal = node
                    visit_node(adj)
                
                elif adj.color == Node_Color.GRAY:
                    edge_type = Edge_Type.BACK
                    if sort_topologically:
                        raise RuntimeError("Cannot find topological sort for graph with a cycle")
                
                else:
                    if node.start_step < node.end_step:
                        edge_type = Edge_Type.FORWARD
                    else:
                        edge_type = Edge_Type.CROSS

                self.edges[index_of_edge].type = edge_type
                self.no_of_type_edges[edge_type] += 1

            node.color = Node_Color.BLACK
            step += 1
            node.end_step = step

            if sort_topologically:
                self.nodes_topological.appendleft(node)
        
        for i in self.nodes:
            if i.color == Node_Color.WHITE:
                visit_node(i)
    

    def path_based_strong_component(self):
        '''
            Finds strongly connected components of graph using 
            Path based strong component algorithm
        '''
        counter = 0
        index_of_cc = 0
        unassigned, different = list(), list()

        def visit_node(node):
            '''
                Helper function to perform DFS on nodes
            '''
            nonlocal counter
            nonlocal index_of_cc

            node.pre_order_number = counter
            counter += 1
            unassigned.append(node)
            different.append(node)

            for adj in node.adjacent_nodes:
                if adj.pre_order_number == -1:
                    visit_node(adj)
                elif adj.connected_component_label == -1:
                    while different[-1].pre_order_number > adj.pre_order_number:
                        different.pop()
            
            if node == different[-1]:
                while unassigned[-1] != node:
                    unassigned[-1].connected_component_label = index_of_cc
                    unassigned.pop()
                unassigned.pop()
                node.connected_component_label = index_of_cc
                index_of_cc += 1
                different.pop()
        
        for i in self.nodes:
            if i.pre_order_number == -1:
                visit_node(i)
    

    def kruskal_min_spanning_tree(self):
        '''
            Minimum spanning tree using kruskal algorithm
            Returns the edges that are in spanning tree in a list of tuples
            The last element of returned tuple has weight of spanning tree
            The edges are represented using from and to node indices
        '''
        self.check_if_st_possible()

        edges = list()
        nodes_in_tree = DisjointSetTree()

        for i in self.nodes:
            nodes_in_tree.insert(i.label)
        
        temp_edges = self.get_edges()

        min_weight = 0
        for i in sorted(temp_edges):
            u, v = i.from_node.label, i.to_node.label
            if nodes_in_tree.find_parent(u) != nodes_in_tree.find_parent(v):
                edges.append(tuple([u, v]))
                min_weight += i.weight
                nodes_in_tree.union_sets(u, v)
        edges.append(tuple([min_weight, -1]))
        
        return edges

    
    def prim_min_spanning_tree(self, src_index:int):
        '''
            Prim's spanning tree algorithm
            Takes a source index and creates a min spanning tree
            with the given index'th node as input
            Returns all the edges in a list of tuples
            Fib heap can be replaced with another min-priority queue that implements decrease-key
        '''
        self.check_if_st_possible()

        result = list()
        key_of = [inf for _ in range(self.no_of_nodes)]
        fib_heap = FibonacciHeap()

        for i in self.nodes:
            fib_heap.insert(0 if i.label == src_index else inf, i.label)

        is_in_queue = [True for _ in range(self.no_of_nodes)]
        key_of[src_index] = 0

        while not fib_heap.is_empty():
            key, index = fib_heap.extract_min()
            u = self.nodes[index]
            is_in_queue[index] = False

            for adj in u.adjacent_nodes:
                edge_index = u.og_edge_indices[adj.label]

                if is_in_queue[adj.label] and self.edges[edge_index].weight < key_of[adj.label]:
                    adj.parent_in_traversal = u
                    key_of[adj.label] = self.edges[edge_index].weight
                    fib_heap.decrease_key(adj.label, key_of[adj.label])
            
        min_weight = 0
        for i in self.nodes:
            if i.label != src_index and i.parent_in_traversal != None:
                v = i.parent_in_traversal.label
                edge_index = self.nodes[v].og_edge_indices[i.label]
                result.append(tuple([v, i.label]))
                min_weight += self.edges[edge_index].weight
        
        result.append(tuple([min_weight, -1]))
        return result
    

    def bellman_ford_path_weights(self, src_index:int):
        '''
            Bellman Ford Algorithm
            Returns the shortest path from source to other nodes in case of diff. integer weights
            It is impossible to have shortest paths in a graph with negative weight cycle. 
            So the algorithm checks for that
            Returns true if no negative weight cycle is found else false
            Only works for directed graphs
        '''
        self.nodes[src_index].distance_from_source = 0
        temp_edges = self.get_edges()

        for _ in range(1, self.no_of_nodes):
            for edge in temp_edges:
                u = edge.from_node
                v = edge.to_node
                u_dist = u.distance_from_source
                v_dist = v.distance_from_source
                
                temp_weight = u_dist + edge.weight
                if v_dist > temp_weight:
                    v.distance_from_source = temp_weight
                    v.parent_in_traversal = u
        
        for edge in temp_edges:
            u = edge.from_node
            v = edge.to_node
            u_dist = u.distance_from_source
            v_dist = v.distance_from_source
            
            temp_weight = u_dist + edge.weight     
            if v_dist > temp_weight:
                return False
        
        return True
    

    def djikstra_shortest_path(self, src_index):
        '''
            Djikstra Algorithm
            Finds the shortest path of all nodes from the node with min spanning tree
            Cannot be used on graphs with negative weights
            Only works for undirected graphs
        '''
        fib_heap = FibonacciHeap()
        for i in self.nodes:
            fib_heap.insert(0 if i.label == src_index else inf, i.label)
        self.nodes[src_index].distance_from_source = 0

        while not fib_heap.is_empty():
            key, index = fib_heap.extract_min()
            u = self.nodes[index]
            src_dist = u.distance_from_source

            for adj in u.adjacent_nodes:
                edge_index = u.og_edge_indices[adj.label]
                weight = self.edges[edge_index].weight
                adj_dist = adj.distance_from_source
                
                if weight < 0:
                    raise RuntimeError("Negative weights cannot be used with this algorithm")
                
                temp_weight = weight + src_dist
                if adj_dist > temp_weight:
                    adj.distance_from_source = temp_weight
                    adj.parent_in_traversal = u
                    fib_heap.decrease_key(adj.label, temp_weight)
            
    
    def floyd_all_shortest_path(self):
        '''
            Floyd-Warshall Algorithm
            Updats the short path weights and predecessor matrix
            Returns the short path weights in a vector matrix
        '''
        #matrix = self.get_edges_matrix()
        n = self.no_of_nodes

        short_paths = [[inf for _ in range(n)] for _ in range(n)]
        pred = [[-1 for _ in range(n)] for _ in range(n)]

        for i in range(n):
            short_paths[i][i] = 0
        
        for edge in self.get_edges():
            u = edge.from_node.label
            v = edge.to_node.label

            short_paths[u][v] = min(edge.weight, short_paths[u][v])
            pred[u][v] = u if u != v else -1
    
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if i != j:
                        temp_weight = short_paths[i][k] + short_paths[k][j]
                        if short_paths[i][j] > temp_weight:
                            short_paths[i][j] = temp_weight
                            pred[i][j] = pred[k][j]
        
        self.short_path_weights = short_paths.copy()
        self.predecessor = pred.copy()
        return short_paths


    def all_pair_shortest_paths(self):
        '''
            All pair shortest path
            Updates the shortest weights and predecessor matrix
            Returns the updated shortest path weights in a vector matrix
        '''
        matrix = self.get_edges_matrix()
        n = self.no_of_nodes

        short_paths = [[inf for _ in range(n)] for _ in range(n)]
        pred = [[-1 for _ in range(n)] for _ in range(n)]

        temp_weights = short_paths.copy()
        temp_pred = pred.copy()

        for i in range(n):
            short_paths[i][i] = 0
        
        for edge in self.get_edges():
            u = edge.from_node.label
            v = edge.to_node.label

            short_paths[u][v] = min(edge.weight, short_paths[u][v])
            pred[u][v] = u if u != v else -1

        ii = 1
        while ii < n - 1:
            for i in range(n):
                for j in range(n):
                    temp_weights[i][j] = (0 if i == j else inf)
                    for k in range(n):
                        temp = short_paths[i][k] + matrix[k][j]
                        if temp < temp_weights[i][j]:
                            temp_weights[i][j] = temp
                            temp_pred[i][j] = (k if pred[i][j] == -1 else pred[i][j])
            
            short_paths = temp_weights.copy()
            pred = temp_pred.copy()

            ii *= 2
        self.short_path_weights = short_paths.copy()
        self.predecessor = pred.copy()

        return short_paths

    
    def get_shortest_path(self, src:int, dest:int):
        '''
            Path due to predecessor matrix
            Returns all the indices between path in a vector
            Should check if it terminates for more inputs
            Should be called after calling either floyd_all_shortest_path or all_pair_shortest_paths
        '''
        self.check_index(src)
        self.check_index(dest)
        result = deque()
        if self.predecessor[src][dest] == -1:
            return result
        
        current = dest
        while current != -1:
            result.appendleft(current)
            current = self.predecessor[src][current]
        
        return result


    def nodes_in_path(self, from_index:int, to_index:int):
        '''
            Returns the nodes between from index and to index
            Should be called after running breadth_traversal or depth_traversal
        '''
        self.check_index(from_index)
        self.check_index(to_index)
        result = list()

        def recurse(src:Node, cur:Node):
            '''
                Helper function to get all nodes of path in order
            '''
            if cur != None:
                if cur != src:
                    recurse(src, cur.parent_in_traversal)
                result.append(cur.label)
        
        recurse(self.nodes[from_index], self.nodes[to_index])
        return result


    def get_topologically_sorted_order(self):
        '''
            Returns labels( indices ) of nodes in topologically sorted order
            Should be called after running depth_traversal with sort_topologically set to true
        '''
        if self.no_of_type_edges[Edge_Type.BACK] != 0:
            raise RuntimeError("Order cannot exist for graphs with cycles")
        
        return [x.label for x in (self.nodes_topological)]


    def can_reach(self, from_index:int, to_index:int):
        '''
            Returns true if node with from index can reach the node with to index.
        '''
        self.check_index(from_index)
        self.check_index(to_index)
        return self.component.find_parent(from_index) == self.component.find_parent(to_index)


    def update_node(self, index:int, data):
        '''
            Takes an index of node as input and updates
            the value stored at the index
        '''
        self.check_index(index)
        self.nodes[index].data = data


    def get_value_at_node(self, index:int):
        '''
            Takes an index of node as input and returns
            the value stored at the index
        '''
        self.check_index(index)
        return self.nodes[index].data
    

    def get_distance_from_source(self, index:int):
        '''
            Returns the distance from source node after
            BFS, DFS, Bellman-Ford or Djikistra are ran 
        '''
        self.check_index(index)
        k = self.nodes[index].distance_from_source
        if k == inf:
            return -1
        return k
    

    def get_start_and_end_steps(self, index:int):
        '''
            Returns the start and end steps for a node after
            DFS is ran
        '''
        self.check_index(index)
        return self.nodes[index].start_step, self.nodes[index].end_step


    def get_strongly_connected_component(self, index:int):
        '''
            Returns the label of connected component the node belongs to
        '''
        self.check_index(index)
        return self.nodes[index].connected_component_label
    


if __name__ == '__main__':
    n, e = map(lambda x:int(x), input().split())
    graph = Graph(n, e)

    for _ in range(e):
        u,v,w = int((n-1) * random()), int((n-1)* random()), int(1e4 *random())
        graph.insert_edge(u,v,w)

    graph.djikstra_shortest_path(0)
    for i in graph.nodes:
        print(i.label, i.distance_from_source)