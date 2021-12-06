#include <vector>
#include <deque>
#include <stdexcept>
#include <climits>
#include <functional>

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

    int no_of_nodes;
    //Node in graph
    struct Node
    {
        int label, connected_components;
        int in_degree, out_degree;
        Color color = WHITE;
        std::vector<Node *> adjacent_nodes;

        Node *parent_in_traversal = nullptr;
        int distance_from_source = INT_MAX;

        T data;
    };

    int no_of_edges;
    //Edge between two nodes
    struct Edge
    {
        Node *from;
        Node *to;
        int weight;

        void insert(Node *from, Node *to, int weight)
        {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };

    /*
     * Helper function for inserting edge
     * So that I don't DRMyself
     */ 
    void insert_single_edge(int from, int to, int weight)
    {
        nodes[from].adjacent_nodes.push_back(&nodes[to]);
        nodes[from].out_degree++;
        nodes[to].in_degree++;
        edges[edge_index++].insert(&nodes[from], &nodes[to], weight);
    }

    int edge_index = 0;
    bool is_directed;
    Node *nodes;
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
        }
        edges = new Edge[this->no_of_edges];
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
        if (!is_directed)
        {
            insert_single_edge(to, from, weight);
        }
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
     * Resets distances and parents of each node
     */
    void reset()
    {
        for (int i = 0; i < no_of_nodes; i++)
        {
            nodes[i].distance_from_source = INT_MAX;
            nodes[i].parent_in_traversal = nullptr;
        }
    }

    /*
     * Takes the source vertex index as input
     * Traversed the graph using Breadth First search
     */
    void breadth_traversal(int source_index)
    {
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
                    printf("%d\n", adj->label);
                    adj->color = GRAY;
                    adj->distance_from_source = 1 + current->distance_from_source;
                    adj->parent_in_traversal = current;
                    deque.push_back(adj);
                }
            }
            current->color = BLACK;
        }
    }

    std::vector<int> nodes_in_path(int from, int to)
    {
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

    int operator[](int index) const
    {
        return nodes[index].distance_from_source;
    }
};