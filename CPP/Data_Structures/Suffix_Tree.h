#include <unordered_map>
#include <vector>
#include <string>
#include <stdio.h>

/**
 * Only tested for small inputs like abcabxabcd
 * Does not work correctly
 * Implemmented by following explanation at https://stackoverflow.com/a/9513423 
 * and https://stackoverflow.com/a/14580102 used under CC BY-SA 4.0
 */
class Suffix_Tree
{
private:
    std::string text;
    int size, remainder;

    /**
     * Node used in suffix tree
     */
    struct Node
    {
        int start, end, length;
        std::unordered_map<char, Node *> edges;
        Node *suffix_link, *parent;
        bool is_leaf;

        explicit Node(Node *parent, int start = -1, int end = -1)
        {
            this->start = start;
            this->end = end;
            this->length = end - start;
            this->suffix_link = nullptr;
            this->parent = parent;
            this->is_leaf = true;

            this->edges.insert({'\0', this});
        }

        void update_indices(int start, int end)
        {
            this->start = start;
            this->end = end;
            this->length = end - start;
        }
    } * root;

    int max_char_code;
    /**
     * Active point that tracks the latest node at which 
     * current suffix is to be inserted
     */
    struct Active
    {
        Node *node;
        char edge;
        int length;

        void set(Node *node, char edge, int length)
        {
            this->node = node;
            this->edge = edge;
            this->length = length;
        }

    } active;

    /**
     * Inserts a single node into the tree
     */
    void insert_node(Node *current, int start, int end)
    {
        Node *new_node = new Node(current, start, end);

        new_node->suffix_link = this->root;

        current->edges.insert({this->text[start], new_node});
        current->is_leaf = false;
    }

    /**
     * Splits a given node by inserting a new node in its position
     */
    Node *split_node(Node *cur, Node *prev_split = nullptr)
    {
        Node *new_node = new Node(cur->parent, cur->start, cur->start + this->active.length);

        cur->parent->edges[this->text[cur->start]] = new_node;

        cur->update_indices(new_node->end, cur->end);
        new_node->edges.insert({this->text[cur->start], cur});
        cur->parent = new_node;

        new_node->suffix_link = cur->suffix_link;
        cur->suffix_link = nullptr;
        new_node->is_leaf = false;

        if (prev_split != nullptr)
        {
            prev_split->suffix_link = new_node;
        }

        return new_node;
    }

    /**
     * Returns true if the character at given index is present 
     * in the active edge path
     */
    bool is_in_active_edge(int index)
    {
        Node *cur = this->active.node;
        if (this->active.edge == '\0')
        {
            return cur->edges.find(this->text[index]) != cur->edges.end();
        }
        else
        {
            if (cur->edges.find(this->active.edge) != cur->edges.end())
            {
                Node *temp = cur->edges.find(this->active.edge)->second;
                int char_index = temp->start + this->active.length;
                if (char_index == temp->end)
                {
                    return temp->edges.find(this->text[index]) != temp->edges.end();
                }

                return this->text[char_index] == this->text[index];
            }
        }
        return false;
    }

    /**
     * Inserts the character at given index at the given tree
     */
    void insert(int index)
    {

        Node *last_node = nullptr;
        int prev_index = index - this->remainder + 1;
        do
        {
            Node *temp;
            prev_index++;

            if (this->is_in_active_edge(index))
            {
                Node *cur = this->active.node->edges[this->active.edge];
                if (this->active.length + 1 > cur->length)
                {
                    this->active.set(
                        cur,
                        this->text[index],
                        1);
                }
                else
                {
                    this->active.set(
                        this->active.node,
                        this->active.edge,
                        this->active.length + 1);
                }
                
                if(last_node != nullptr )
                {
                    last_node->suffix_link = this->active.node;
                }
                // this->remainder++;
                break;
            }
            else
            {
                if (this->active.node->edges.find(this->active.edge) != this->active.node->edges.end())
                {
                    temp = this->active.node->edges[this->active.edge];
                }
                else
                {
                    temp = this->active.node;
                }

                if (this->can_split(temp))
                {
                    temp = this->split_node(temp, last_node);
                    last_node = temp;
                }

                this->insert_node(temp, index, this->size);
                this->remainder--;

                if (this->active.node == this->root && this->active.length > 0)
                {
                    this->active.set(
                        this->root,
                        (prev_index <= index) ? this->text[prev_index] : '\0',
                        this->active.length - 1);
                }
                else
                {
                    this->active.set(
                        this->active.node->suffix_link,
                        this->active.edge,
                        this->active.length);
                }

            }

        } while (this->remainder > 0);
        // The below might be wrong
        if (this->remainder == 0)
        {
            this->active.set(
                this->active.node,
                '\0',
                0);
        }
    }

    /**
     * Returns true if a given node should be split to insert new nodes
     */
    bool can_split(Node *cur)
    {
        //Might not be the correct condition
        return cur->start + this->active.length < cur->end;
    }

    /**
     * Creates the suffix tree for given string
     */
    void create_suffix_tree()
    {
        for (int i = 0; i < this->size; i++)
        {
            this->remainder = (this->remainder <= 0) ? 1 : this->remainder + 1;
            this->insert(i);
        }
    }

    void dfs(Node *current, std::string s, std::vector<std::string> &result)
    {
        if (current == nullptr)
            return;
        std::string append = "";
        bool flag = false;

        if (current != this->root)
        {
            append = this->text.substr(current->start, current->length);
        }

        s += append;
        for (int i = 1; i < 256; i++)
        {
            if (current->edges.find((char)i) != current->edges.end())
            {
                dfs(current->edges[(char)i], s, result);
                flag = true;
            }
        }

        if (!flag)
        {
            result.push_back(s);
        }
    }

public:
    /**
     * Constructor
     */
    explicit Suffix_Tree(const std::string s, int max_char_code = 256, char delimiter = '$')
    {

        this->text = s + delimiter;
        this->size = this->text.size();
        this->remainder = 0;

        this->root = new Node(nullptr);

        this->root->suffix_link = this->root;
        this->active = Active();
        this->active.set(this->root, '\0', 0);

        this->max_char_code = max_char_code;
        this->create_suffix_tree();
    }

    /**
     * Copy constructor
     */
    Suffix_Tree(const Suffix_Tree &other)
    {
        this->text = other.text;
        this->size = this->text.size();
        this->remainder = 0;

        this->root = new Node(nullptr);

        this->root->suffix_link = this->root;
        this->active = Active();

        this->active.set(this->root, '\0', 0);

        this->max_char_code = other.max_char_code;
        this->create_suffix_tree();
    }

    /**
     * Returns a vector of all suffixes in sorted order
     */
    std::vector<std::string> DFS()
    {
        std::vector<std::string> result;
        this->dfs(this->root, "", result);

        result.erase(result.begin());
        for (auto &&s : result)
        {
            s.erase(--s.end());
        }
        return result;
    }
};
