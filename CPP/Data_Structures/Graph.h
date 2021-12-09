#include <vector>
#include <deque>
#include <stdexcept>
#include <climits>
#include <deque>
#include <stack>
#include <list>
#include <functional>
#include <unordered_map>
#include "Disjoint_Set_Tree.h"
#include "Fibonnaci_Heap.h"

const int MAX = 1000;

/*
 * Uses pointer based representation of graph
 * Recommended to use reset if trying to use multiple algorithms on same graph object
 * This file is subject to mission creep
 */

template <typename T>
class Graph
{
    // Used during traversal
    enum Color
    {
        WHITE,
        GRAY,
        BLACK
    };

    // Types of edges after depth-traversal
    // Can be TREE, BACK, FORWARD, CROSS
    enum Edge_type
    {
        TREE,
        BACK,
        FORWARD,
        CROSS
    };

    int no_of_nodes;
    // Node in graph
    struct Node
    {
        //index of the node
        int label;

        // Yet to be used
        int in_degree, out_degree;

        // Used in DFS
        int start_step, end_step;

        // Used for calculating strongly connected components
        int pre_order_number = -1;
        int connected_component_label = -1;

        //Used in DFS and BFS
        Color color = WHITE;

        std::vector<Node *> adjacent_nodes;

        //outgoing Edge indices
        std::unordered_map<int, int> og_edge_indices;

        //Calculated in both DFS and BFS
        Node *parent_in_traversal = nullptr;

        //Calculated in DFS, BFS and Djikistra
        int distance_from_source = INT_MAX;

        T data;

        //Used for min-heap-tree in prim spanning tree
        bool operator<(const Node other)
        {
            return this->distance_from_source < other.distance_from_source;
        }

        void operator=(const Node other)
        {
            this->distance_from_source = other.distance_from_source;
            this->parent_in_traversal = other.parent_in_traversal;
            this->start_step = other.start_step;
            this->end_step = other.end_step;
            this->connected_component_label = other.connected_component_label;
            this->pre_order_number = other.pre_order_number;

            this->data = other.data;
        }

        void reset()
        {
            this->distance_from_source = INT_MAX;
            this->parent_in_traversal = nullptr;
            this->start_step = 0;
            this->end_step = 0;
            this->connected_component_label = -1;
            this->pre_order_number = -1;
        }
    };

    int no_of_edges;
    std::unordered_map<Edge_type, int> no_of_type_edges;
    // Edge between two nodes
    struct Edge
    {
        Node *from;
        Node *to;
        int weight;
        Edge_type type;
        bool reverse_edge = false; // For undirected graphs

        void insert(Node *from, Node *to, int weight, bool reverse_edge = false)
        {
            this->from = from;
            this->to = to;
            this->weight = weight;
            this->reverse_edge = reverse_edge;
        }

        bool operator<(const Edge &other) const
        {
            return weight < other.weight;
        }

        void operator=(const Edge &other)
        {
            this->from = other.from;
            this->to = other.to;
            this->weight = other.weight;
            this->type = other.type;
        }
    };

    /*
     * Helper function for inserting edge
     * So that I don't DRMyself
     */
    void insert_single_edge(int from, int to, int weight, bool reverse_edge = false)
    {
        nodes[from].adjacent_nodes.push_back(&nodes[to]);
        nodes[from].out_degree++;
        nodes[to].in_degree++;
        nodes[from].og_edge_indices.insert({to, edge_index});
        edges[edge_index++].insert(&nodes[from], &nodes[to], weight, reverse_edge);

        component.union_set(from, to);
    }

    /*
     * Helper function for checking index bounds
     */
    inline void check_index(int index)
    {
        if (index >= this->no_of_nodes)
        {
            throw std::invalid_argument("Index out of bounds");
        }
    }

    std::vector<Edge> get_edges()
    {
        std::vector<Edge> result;
        for (int i = 0; i < this->no_of_edges; i++)
        {
            if (!this->edges[i].reverse_edge)
            {
                result.push_back(edges[i]);
            }
        }
        return result;
    }

    std::list<Node *> nodes_topological; // Node indices in topological sorting order
    Disjoint_Set_Tree<int> component;

    int edge_index = 0;
    bool is_directed;
    Node *nodes;
    //Do not manipulate this. Use get_edges() instead
    Edge *edges;

public:
    Graph(int no_of_nodes, int no_of_edges, bool is_directed = true)
    {
        this->no_of_nodes = no_of_nodes;
        this->no_of_edges = no_of_edges;
        this->is_directed = is_directed;
        if (!is_directed)
        {
            this->no_of_edges = no_of_edges * 2;
        }
        nodes = new Node[no_of_nodes];
        for (int i = 0; i < no_of_nodes; i++)
        {
            nodes[i].label = i;
            component.insert(i);
        }
        edges = new Edge[this->no_of_edges];

        for (int i = 0; i < 4; i++)
        {
            no_of_type_edges.insert({(Edge_type)i, 0});
        }
    }

    /*
     * Takes index of from node and to node and weight associated with the edge
     * Inserts edges into the graph
     * The same edge is inserted twice in case of undirected graph
     */
    void insert_edge(int from, int to, int weight = 1)
    {
        if (from >= no_of_nodes || to >= no_of_nodes)
        {
            throw std::invalid_argument("Node indices or edges are out of bounds");
        }

        insert_single_edge(from, to, weight);
        if (!this->is_directed)
        {
            insert_single_edge(to, from, weight, true);
        }
    }

    /*
     * Resets distances and parents of each node (Required for BFS)
     * Resets start_step and end_step of each node(Required for DFS)
     * Resets connected_component_label of each node( Required for finding Strongly connected components)
     */
    void reset()
    {
        for (int i = 0; i < no_of_nodes; i++)
        {
            nodes[i].reset();
        }
    }

    /*
     * Takes the source vertex index as input
     * Traversed the graph using Breadth First search
     */
    void breadth_traversal(int source_index)
    {
        check_index(source_index);
        nodes[source_index].color = GRAY;
        nodes[source_index].distance_from_source = 0;

        std::deque<Node *> deque;
        deque.push_back(&nodes[source_index]);

        while (!deque.empty())
        {
            Node *current = deque.front();
            deque.pop_front();

            for (Node *adj : current->adjacent_nodes)
            {
                if (adj->color == WHITE)
                {
                    adj->color = GRAY;
                    adj->distance_from_source = 1 + current->distance_from_source;
                    adj->parent_in_traversal = current;
                    deque.push_back(adj);
                }
            }
            current->color = BLACK;
        }
    }

    /*
     * Depth first search
     * Assigns the start_step and end_step for each node
     * The assignments are influenced by the ordering of the node indices
     */
    void depth_traversal(bool sort_topologically = false)
    {
        int step = 0;
        if (sort_topologically)
        {
            this->nodes_topological.clear();
        }
        std::function<void(Node *)> visit_node =
            [&step, sort_topologically, &visit_node, this](Node *current)
        {
            step++;
            current->start_step = step;
            current->color = GRAY;
            for (Node *adj : current->adjacent_nodes)
            {
                int index_of_edge = current->og_edge_indices[adj->label];
                Edge_type type;
                if (adj->color == WHITE)
                {
                    type = TREE;

                    adj->parent_in_traversal = current;
                    visit_node(adj);
                }
                else if (adj->color == GRAY)
                {
                    type = BACK;
                    if (sort_topologically)
                    {
                        throw std::runtime_error("Cannot find topological sort for a graph with a cycle");
                    }
                }
                else
                {
                    if (current->start_step < adj->start_step)
                    {
                        type = FORWARD;
                    }
                    else
                    {
                        type = CROSS;
                    }
                }
                this->edges[index_of_edge].type = type;
                this->no_of_type_edges[type]++;
            }
            current->color = BLACK;
            step++;
            current->end_step = step;

            if (sort_topologically)
            {
                this->nodes_topological.push_front(current);
            }
        };

        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (nodes[i].color == WHITE)
            {
                visit_node(&nodes[i]);
            }
        }
    }

    /*
     * Finds the strongly connected components of the graph using
     * Path based strong component algorithm
     */
    void path_based_strong_components()
    {
        int counter = 0;
        int index_of_cc = 0; // Index for connected components
        std::stack<Node *> unassigned, different;

        std::function<void(Node *)> visit_node =
            [&counter, &visit_node, &unassigned, &different,
             &index_of_cc](Node *current)
        {
            current->pre_order_number = counter++;
            unassigned.push(current);
            different.push(current);
            for (Node *adj : current->adjacent_nodes)
            {
                if (adj->pre_order_number == -1)
                {
                    // Tree Edge
                    visit_node(adj);
                }
                else if (adj->connected_component_label == -1)
                {
                    while (different.top()->pre_order_number > adj->pre_order_number)
                    {
                        different.pop();
                    }
                }
            }
            if (current == different.top())
            {
                while (unassigned.top() != current)
                {
                    unassigned.top()->connected_component_label = index_of_cc;
                    unassigned.pop();
                }
                unassigned.top()->connected_component_label = index_of_cc++;
                unassigned.pop();
                different.pop();
            }
        };

        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (nodes[i].pre_order_number == -1)
            {
                visit_node(&nodes[i]);
            }
        }
    }

    /*
     * Minimum Spanning Tree using Kruskal Algorithm
     * Returns the edges that are in Kruskal minimum spanning tree in a vector of pairs
     * The last element of returned vector has weight of spanning tree
     * The edges are represented using the indices( or labels ) of nodes.
     */
    std::vector<std::pair<int, int>> kruskal_min_spanning_tree()
    {
        std::vector<std::pair<int, int>> edges;
        Disjoint_Set_Tree<int> nodes_in_tree;

        for (int i = 0; i < this->no_of_nodes; i++)
        {
            nodes_in_tree.insert(i);
        }
        auto temp_edges = this->get_edges();

        std::sort(temp_edges.begin(), temp_edges.end());
        int min_weight = 0;
        for (auto i : temp_edges)
        {
            int u_label = i.from->label;
            int v_label = i.to->label;
            if (nodes_in_tree.find_parent(u_label) != nodes_in_tree.find_parent(v_label))
            {
                edges.push_back(std::make_pair(u_label, v_label));
                min_weight += i.weight;
                nodes_in_tree.union_set(u_label, v_label);
            }
        }
        edges.push_back(std::make_pair(min_weight, -1));
        return edges;
    }

    /*
     * Prim's spanning tree algorithm
     * Takes a source index and creates a min spanning tree 
     * with given index'th node as input
     * Returns all the edges( in form of (from, to) repr. )
     * Returns the weight of spanning tree at the end of vector
     */
    std::vector<std::pair<int, int>> prim_min_spanning_tree(int source_index)
    {
        // TODO: Have to use fibbnacci min_heap
        std::vector<std::pair<int, int>> result;
        bool *is_in_spanning_tree = new bool[this->no_of_nodes];
        int *key_of = new int[this->no_of_nodes];

        Fibonnaci_Heap<int, Node *> fb_min_heap;
        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (i != source_index)
            {
                fb_min_heap.insert(MAX, &(this->nodes[i]));
                key_of[i] = MAX;
            }
            else
            {
                fb_min_heap.insert(0, &(this->nodes[i]));
                key_of[i] = 0;
            }
            is_in_spanning_tree[i] = false;
        }

        while (!fb_min_heap.is_empty())
        {
            std::pair<int, Node *> min_node = fb_min_heap.extract_min();
            int key = min_node.first;
            Node *current = min_node.second;

            is_in_spanning_tree[current->label] = true;
            for (Node *adj : current->adjacent_nodes)
            {
                int node_index = adj->label;
                int edge_index = current->og_edge_indices[node_index];
                if (!is_in_spanning_tree[node_index] &&
                    this->edges[edge_index].weight < key_of[node_index])
                {
                    adj->parent_in_traversal = current;
                    key_of[node_index] = this->edges[edge_index].weight;
                    fb_min_heap.decrease_key(node_index, key_of[node_index]);
                }
            }
        }

        int min_spanning_weight = 0;
        for (int u = 0; u < this->no_of_nodes; u++)
        {
            if (u != source_index)
            {
                int v = nodes[u].parent_in_traversal->label;
                int edge_index = nodes[u].og_edge_indices[v];
                result.push_back(std::make_pair(u, v));
                min_spanning_weight += this->edges[edge_index].weight;
            }
        }
        result.push_back(std::make_pair(min_spanning_weight, -1));
        return result;
    }

    /*
     * Bellman Ford Algorithm
     * Returns the shortest path from source to other nodes in case of different integer weights
     * It is impossible to have shortest path between nodes in graphs with negative weight cycles
     * So, the algorithm checks for that
     * Takes the index of source node as input
     * Returns true if no negative weight cycle is found in the graph
     * Else false
     */
    bool bellman_ford_path_weights(int source_index)
    {
        nodes[source_index].distance_from_source = 0;
        std::vector<Edge> temp_edges = this->get_edges();

        for (int i = 1; i < this->no_of_nodes; i++)
        {
            for (Edge current_edge : temp_edges)
            {
                Node *u = current_edge.from;
                Node *v = current_edge.to;
                if (v->distance_from_source > u->distance_from_source + current_edge.weight)
                {
                    v->distance_from_source = u->distance_from_source + current_edge.weight;
                    v->parent_in_traversal = u;
                }
            }
        }

        for (Edge current_edge : temp_edges)
        {
            Node *u = current_edge.from;
            Node *v = current_edge.to;
            if (v->distance_from_source > u->distance_from_source + current_edge.weight)
            {
                return false;
            }
        }

        return true;
    }

    /*
     * Dijkstra Algorithm
     * Finds the shortest path of all nodes from the node with source_index
     * Cannot be used on graphs with negative weights
     */
    void djikstra_shortest_path(int source_index)
    {
        Fibonnaci_Heap<int, Node *> fb_min_heap;
        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (i != source_index)
            {
                fb_min_heap.insert(MAX, &(this->nodes[i]));

            }
            else
            {
                fb_min_heap.insert(0, &(this->nodes[i]));
                this->nodes[i].distance_from_source = 0;
            }
        }
        
        while (!fb_min_heap.is_empty())
        {
            std::pair<int, Node *> min_node = fb_min_heap.extract_min();
            int key = min_node.first;
            Node *current = min_node.second;

            for (Node *adj : current->adjacent_nodes)
            {
                int edge_index = current->og_edge_indices[adj->label];
                int weight = this->edges[edge_index].weight;
                if( weight < 0 )
                {
                    throw std::invalid_argument("Cannot use this on a graph with negative weights\n");
                }
                if (adj->distance_from_source >
                    current->distance_from_source + weight)
                {
                    adj->distance_from_source = current->distance_from_source + weight;
                    
                    fb_min_heap.decrease_key(adj->label, adj->distance_from_source);
                }
            }
        }
    }

    /*
     * Returns the nodes between the from index node and to index node
     * Shoulb be called after running breadth_traversal on node with 'from' index
     * Can also be used to find nodes in path of depth-first tree provided both belong 
     * to the same tree
     * TODO: Perform checks to see if two nodes belong to same depth-first tree
     */
    std::vector<int> nodes_in_path(int from, int to)
    {

        this->check_index(from);
        this->check_index(to);
        std::vector<int> result;

        std::function<void(Node *, Node *)> recurse =
            [&result, &recurse](Node *source, Node *current)
        {
            if (current != nullptr)
            {
                if (current != source)
                {
                    recurse(source, current->parent_in_traversal);
                }
                result.push_back(current->label);
            }
        };

        recurse(&nodes[from], &nodes[to]);

        return result;
    }

    /*
     * Returns labels( indices ) of nodes in topologically sorted order
     * Should be called after running depth_traversal with sort_topologically set as true
     */
    std::vector<int> get_topologically_sorted_order()
    {

        if (this->no_of_type_edges[BACK] != 0)
        {
            throw std::runtime_error("Topological sorting does not exist for cyclic graph");
        }
        std::vector<int> result;
        for (Node *current : this->nodes_topological)
        {
            result.push_back(current->label);
        }
        return result;
    }

    /*
     * Returns true if node with from index can reach the node with to index
     */
    bool can_reach(int from, int to)
    {
        check_index(from);
        check_index(to);
        return component.find_parent(from) == component.find_parent(to);
    }

    /*
     * Takes a index of a node and value to insert as input
     * Stores the given data at 'index'th node
     */
    void update_node(int index, T data)
    {
        nodes[index].data = data;
    }

    /*
     * Takes an index as input and returns the data stored at
     * index'th node
     */
    T get_value_at_node(int index)
    {
        return nodes[index].data;
    }

    /*
     * Returns the distance from a source on which breadth_traversal is called
     */
    int get_distance_from_source(int index)
    {
        check_index(index);
        int k =  this->nodes[index].distance_from_source;
        if( k >= MAX )
        {
            k = -1;
        }
        return k;
    }

    /*
     * Returns the start and end steps for a node after depth_traversal is called
     */
    std::pair<int, int> get_start_and_end_steps(int index)
    {
        check_index(index);
        return std::make_pair(nodes[index].start_step, nodes[index].end_step);
    }

    /*
     * Returns the label of connected component the node belongs to
     */
    int get_strongly_connected_component(int index)
    {
        check_index(index);
        return nodes[index].connected_component_label;
    }
    /*
     * Returns the distance from a source on which 
     * breadth_traversal or depth_traversal or dijkstra_shortestpath 
     * is called
     */
    int operator[](int index)
    {
        // check_index(index);
        return this->get_distance_from_source( index );
    }

    /*
     * Returns the start and end steps for a node after depth_traversal is called
     */
    std::pair<int, int> operator()(int index)
    {
        if (index >= this->no_of_nodes)
        {
            throw std::invalid_argument("Index out of bounds");
        }
        return std::make_pair(nodes[index].start_step, nodes[index].end_step);
    }
};