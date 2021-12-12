from collections import deque
from enum import Enum
from math import inf

from DisjointSetTree import DisjointSetTree


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
        self.connected_component_label = 0

        #Used in both DFS and BFS
        self.color = Node_Color.WHITE
        self.adjacent_nodes = list()
        self.og_edge_indices = dict()

        #Used for storing the predecessor in traversal
        self.parent_in_traversal = None

        #Calcualted in DFS, BFS, Bellman-Ford and Djikistra
        self.distance_from_source = inf

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
        if is_directed:
            self.no_of_edges *= 2
        self.no_of_type_edges = {x:0 for x in Edge_Type}

        self.is_directed = False

        #For use in inserting edges
        self.edge_index = 0
        
        #This list should not be manipulated or sorted
        self.edges = [Edge() for _ in range(self.no_of_edges)]
        self.nodes = [Node(i) for i in range(self.no_of_nodes)]

        #For use in all pair short paths
        self.predecessor = list()
        self.short_path_weights = list()

        self.nodes_topological = list()
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
        self.nodes[from_index].og_edge_indices[to_index] = self.nodes[to_index]
        self.edges[self.edge_index].insert(self.nodes[from_index], self.nodes[to_index], weight, reversed_edge)

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
        for i in self.no_of_nodes:
            matrix.append(list())
            for j in self.no_of_nodes:
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
        if self.directed:
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
        if self.is_directed:
            self.insert_single_edge(to_index, from_index, weight, True)
    
    
    def reset(self):
        '''
            Resets all the nodes calculated values in the graph 
        '''
        for i in range(self.no_of_nodes):
            self.nodes[i].reset()
    

        
    



    


    

    

    
    





        




if __name__ == '__main__':
    n, e = map(lambda x: int(x), input().split())

    graph  = Graph(n, e, False)

    for _ in range(e):
        u, v, w = map(lambda x:int(x), input().split())
        graph.insert_single_edge(u,v,w)

