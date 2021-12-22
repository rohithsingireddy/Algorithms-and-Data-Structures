#include <unordered_map>
#include <string>
#include <stdio.h>

/*
 * Only tested for small inputs like abcabxabcd
 * Implemmented by following explanation at https://stackoverflow.com/a/9513423 used under CC BY-SA 4.0
 */
class Suffix_Tree
{
private:
    std::string text;
    int size, remainder;
    struct Node
    {
        int start, end, length;
        std::unordered_map<char, Node *> edges;
        Node *suffix_link, *parent;
        bool is_leaf;

        explicit Node(Node *parent, int start = -10, int end = -10)
        {
            this->start = start;
            this->end = end;
            this->length = end - start;
            this->suffix_link = nullptr;
            this->parent = parent;
            this->is_leaf = true;
        }

        void update_indices(int start, int end)
        {
            this->start = start;
            this->end = end;
            this->length = end - start;
        }
    } * root, *NIL;

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

    void insert_node(Node *current, int start, int end)
    {
        Node *new_node = new Node(current, start, end);

        new_node->suffix_link = this->root;

        current->edges.insert({this->text[start], new_node});
        current->is_leaf = false;
    }

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

    bool is_in_active_edge(int index)
    {
        if (this->active.node->edges.find(this->active.edge) != this->active.node->edges.end())
        {
            Node *cur = this->active.node->edges[this->active.edge];
            if (this->active.edge == '\0')
            {
                return cur->edges.find(this->text[index]) != cur->edges.end();
            }
            int char_index = cur->start + this->active.length;
            if (char_index == cur->end)
            {
                return cur->edges.find(this->text[index]) != cur->edges.end();
            }
            return this->text[char_index] == this->text[index];
        }
        return false;
    }

    void insert(int index)
    {

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
        }
        else
        {
            Node *last_split_node = nullptr;
            int prev_index = index - this->remainder + 1;
            while (this->remainder > 0)
            {
                Node *temp;
                prev_index++;
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
                    temp = this->split_node(temp, last_split_node);
                    last_split_node = temp;
                    if (this->active.node == this->root)
                    {
                        this->active.set(
                            this->active.node,
                            (prev_index < this->size) ? this->text[prev_index] : '\0',
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
                this->insert_node(temp, index, this->size);
                this->remainder--;
                if (this->is_in_active_edge(index))
                {
                    this->active.set(
                        this->NIL,
                        '\0',
                        this->active.length + 1);
                    break;
                }
            }
        }
    }

    bool can_split(Node *cur)
    {
        //Might not be the correct condition
        return cur->start + this->active.length < cur->end;
    }

    void create_suffix_tree()
    {
        for (int i = 0; i < this->size; i++)
        {
            this->remainder = (this->remainder <= 0) ? 1 : this->remainder + 1;
            this->insert(i);
        }
    }

public:
    explicit Suffix_Tree(const std::string s, char delimiter = '$')
    {

        this->text = s + delimiter;
        this->size = this->text.size();
        this->remainder = 0;

        this->NIL = new Node(nullptr);
        this->root = new Node(this->NIL);
        this->NIL->is_leaf = false;

        this->root->suffix_link = this->NIL;
        for (int i = 0; i < 256; i++)
        {
            NIL->edges.insert({(char)i, this->root});
        }

        this->active = Active();
        this->active.set(this->NIL, '\0', 0);
        this->create_suffix_tree();
    }

    void DFS()
    {
        dfs(this->root, "");
    }

    void dfs(Node *current, std::string s)
    {
        if (current == nullptr)
            return;
        std::string append = "";
        bool flag = false;

        if (current != this->root)
        {
            append = this->text.substr(current->start, current->length);
        }

        for (int i = 1; i < 256; i++)
        {
            if (current->edges.find((char)i) != current->edges.end())
            {
                dfs(current->edges[(char)i], s + append);
                flag = true;
            }
        }

        if (!flag)
        {
            for (char c : s + append)
            {
                printf("%c", c);
            }
            printf("\n");
        }
    }
};
