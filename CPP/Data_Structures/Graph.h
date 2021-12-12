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

/*
 * Uses pointer based representation of graph
 * Recommended to use reset if trying to use multiple algorithms on same graph object
 * This file is subject to mission creep
 * Weights cannot be over 1e7 because that is used as MAX for certain member functions
 * Susceptible to system breaking memory leaks
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

        const static int MAX = 1e7;
        // index of the node
        int label;

        // Yet to be used
        int in_degree, out_degree;

        // Used in DFS
        int start_step, end_step;

        // Used for calculating strongly connected components
        int pre_order_number = -1;
        int connected_component_label = -1;

        // Used in DFS and BFS
        Color color = WHITE;

        std::vector<Node *> adjacent_nodes;

        // outgoing Edge indices
        std::unordered_map<int, int> og_edge_indices;

        // Calculated in both DFS and BFS
        Node *parent_in_traversal = nullptr;

        // Calculated in DFS, BFS, Bellman-Ford and Djikistra
        int distance_from_source = INT_MAX;

        T data;

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
            this->distance_from_source = this->MAX;
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

    std::list<Node *> nodes_topological; // Node indices in topological sorting order
    Disjoint_Set_Tree<int> component;

    int edge_index = 0;
    bool is_directed;
    Node *nodes;
    // Do not manipulate this. Use get_edges() instead
    Edge *edges;

    // For shortest paths
    std::vector<std::vector<int>> predecessor, short_path_weights;

    /*
     * Helper function for inserting edge
     * So that I don't DRMyself
     */
    void insert_single_edge(int from, int to, int weight, bool reverse_edge = false)
    {
        this->nodes[from].adjacent_nodes.push_back(&nodes[to]);
        this->nodes[from].out_degree++;
        this->nodes[to].in_degree++;
        this->nodes[from].og_edge_indices.insert({to, edge_index});
        this->edges[edge_index++].insert(&nodes[from], &nodes[to], weight, reverse_edge);

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

    /*
     * Helper function to get a copy of edges
     */
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

    /*
     * Returns the matrix representation of edges of graph
     * with weights.
     * Uses nodes labels for matrix indices
     */
    std::vector<std::vector<int>> get_edges_matrix()
    {
        std::vector<std::vector<int>> matrix(this->no_of_edges, std::vector<int>(this->no_of_edges));

        for (int i = 0; i < this->no_of_nodes; i++)
        {
            for (int j = 0; j < this->no_of_nodes; j++)
            {
                matrix[i][j] = (i == j) ? 0 : Node::MAX;
            }
        }

        std::vector<Edge> edges = this->get_edges();

        for (Edge edge : edges)
        {
            int u = edge.from->label;
            int v = edge.to->label;

            matrix[u][v] = edge.weight;
        }

        return matrix;
    }

    /*
     * Helper function to check if a graph is undirected and
     * is connected
     */
    void check_if_st_possible()
    {

        if (this->is_directed)
        {
            throw std::runtime_error("Algorithm cannot find spanning tree for directed graph\n");
        }
        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (this->component.find_parent(0) != this->component.find_parent(i))
            {
                throw std::runtime_error("Graph has to be connected to find spanning tree\n");
            }
        }
    }

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

        this->predecessor.resize(this->no_of_nodes);
        this->short_path_weights.resize(this->no_of_nodes);

        for (int i = 0; i < this->no_of_nodes; i++)
        {
            this->predecessor[i].resize(this->no_of_nodes, -1);
            this->short_path_weights[i].resize(this->no_of_nodes, 0);
        }
    }

    ~Graph()
    {
        delete[] nodes;
        delete[] edges;
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
     * Resets predecessor and shortest path matrices
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
        this->check_if_st_possible();

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
     * Fib heap can be replaced with another min-priority queue that provides decrese method
     * Segmentation fault for some inputs
     */
    std::vector<std::pair<int, int>> prim_min_spanning_tree(int source_index)
    {
        this->check_if_st_possible();

        std::vector<std::pair<int, int>> result;
        bool *is_in_queue = new bool[this->no_of_nodes];
        int *key_of = new int[this->no_of_nodes];

        Fibonnaci_Heap<int, Node *> fb_min_heap;
        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (i != source_index)
            {
                fb_min_heap.insert(Node::MAX, &(this->nodes[i]));
                key_of[i] = Node::MAX;
            }
            else
            {
                fb_min_heap.insert(0, &(this->nodes[i]));
                key_of[i] = 0;
            }
            is_in_queue[i] = true;
        }

        while (!fb_min_heap.is_empty())
        {
            std::pair<int, Node *> min_node = fb_min_heap.extract_min();
            int key = min_node.first;
            Node *current = min_node.second;
            is_in_queue[current->label] = false; // Segmentation fault occurs here

            for (Node *adj : current->adjacent_nodes)
            {
                int node_index = adj->label;
                int edge_index = current->og_edge_indices[node_index];

                if (is_in_queue[node_index] &&
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
            if (u != source_index && nodes[u].parent_in_traversal != nullptr)
            {
                int v = nodes[u].parent_in_traversal->label;
                int edge_index = nodes[u].og_edge_indices[v];
                result.push_back(std::make_pair(v, u));
                min_spanning_weight += this->edges[edge_index].weight;
                printf("%d\n", key_of[v]);
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
     * Due to integer overflows might not work for big values
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
                int u_dist = u->distance_from_source;
                int v_dist = v->distance_from_source;
                int temp_weight = u_dist + current_edge.weight;
                if (v_dist > temp_weight)
                {
                    v->distance_from_source = temp_weight;
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
     * Segmentation fault for some inputs. Don't know why
     *
     */
    void djikstra_shortest_path(int source_index)
    {
        Fibonnaci_Heap<int, Node *> fb_min_heap;
        for (int i = 0; i < this->no_of_nodes; i++)
        {
            if (i != source_index)
            {
                fb_min_heap.insert(Node::MAX, &(this->nodes[i]));
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
            int src_dist = current->distance_from_source; // Segment Fault happens here

            for (Node *adj : current->adjacent_nodes)
            {
                int edge_index = current->og_edge_indices[adj->label];
                int weight = this->edges[edge_index].weight;
                int adj_dist = adj->distance_from_source;
                if (weight < 0)
                {
                    throw std::invalid_argument("Cannot use this on a graph with negative weights\n");
                }

                int temp_weight = src_dist + weight;
                if (adj_dist > temp_weight)
                {
                    adj->distance_from_source = temp_weight;
                    adj->parent_in_traversal = current;
                    fb_min_heap.decrease_key(adj->label, temp_weight);
                }
            }
        }
    }

    /*
     * FloydWarshall Algorithm
     * Updates the short path weights and predecessor matrix
     * Returns the short path weights in a vector matrix
     */
    std::vector<std::vector<int>> floyd_all_shortest_path()
    {
        auto matrix = this->get_edges_matrix();
        int n = this->no_of_nodes;

        std::vector<std::vector<int>> short_paths(n, std::vector<int>(n, 1e7)); //Won't compile with node::MAX
        std::vector<std::vector<int>> pred(n, std::vector<int>(n, -1));

        for (int i = 0; i < n; ++i)
        {
            short_paths[i][i] = 0;
        }

        for (Edge i : this->get_edges())
        {
            int u = i.from->label;
            int v = i.to->label;

            short_paths[u][v] = i.weight;
            pred[u][v] = u;
        }

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i != j)
                    {
                        int temp_weight = short_paths[i][k] + short_paths[k][j];
                        if (short_paths[i][j] > temp_weight)
                        {
                            short_paths[i][j] = temp_weight;
                            pred[i][j] = pred[k][j];
                        }
                    }
                }
            }
        }
        this->short_path_weights = short_paths;
        this->predecessor = pred;
        return short_paths;
    }

    /*
     * All pair shortest path
     * Updates the shortest weights and predecessor matrix
     * Returns the updated shortest weights in a vector matrix
     */
    std::vector<std::vector<int>> all_pair_shortest_paths()
    {
        auto matrix = this->get_edges_matrix();
        int n = this->no_of_nodes;

        std::vector<std::vector<int>> short_paths(n, std::vector<int>(n, 1e7)); // Won't compile with Node::MAX
        std::vector<std::vector<int>> temp_weights(n, std::vector<int>(n));

        std::vector<std::vector<int>> pred(n, std::vector<int>(n, -1));
        std::vector<std::vector<int>> temp_pred(n, std::vector<int>(n, -1));

        for (int i = 0; i < n; ++i)
        {
            short_paths[i][i] = 0;
        }

        for (Edge i : this->get_edges())
        {
            int u = i.from->label;
            int v = i.to->label;

            short_paths[u][v] = i.weight;
            pred[u][v] = u;
        }

        for (int ii = 1; ii < n - 1; ii *= 2)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    temp_weights[i][j] = (i == j) ? 0 : Node::MAX;
                    for (int k = 0; k < n; k++)
                    {
                        int temp = short_paths[i][k] + short_paths[k][j];
                        if (temp < temp_weights[i][j])
                        {
                            temp_weights[i][j] = temp;
                            temp_pred[i][j] = (pred[i][j] == -1) ? k : pred[i][j];
                        }
                    }
                }
            }
            short_paths = temp_weights;
            pred = temp_pred;
        }
        this->short_path_weights = short_paths;
        this->predecessor = pred;
        return pred;
    }

    /*
     * Path due to predecessor matrix
     * Returns all the indices between the path in a vector
     * Should check if it terminates for more inputs
     * Seems to work for both floyd warshall and all pair shortest path predecessor matrices
     */
    std::deque<int> get_shortest_path(int source, int dest)
    {
        this->check_index(source);
        this->check_index(dest);

        if (this->predecessor[source][dest] == -1)
        {
            return std::deque<int>();
        }

        std::deque<int> result;
        int current = dest;
        while (current != -1)
        {
            result.push_front(current);
            current = this->predecessor[source][current];
        }
        return result;
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
     *
     */

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
        int k = this->nodes[index].distance_from_source;
        if (k >= Node::MAX)
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
        check_index(index);
        return this->get_distance_from_source(index);
    }

    /*
     * Returns the start and end steps for a node after depth_traversal is called
     */
    std::pair<int, int> operator()(int index)
    {
        check_index(index);
        return std::make_pair(nodes[index].start_step, nodes[index].end_step);
    }
};