#include <unordered_map>
#include <string>
#include <stdio.h>

class Suffix_Tree
{
private:
    std::string text;
    int size, remainder;
    struct Node
    {
        int start, end, length;
        std::unordered_map<char, Node *> edges;
        Node *suffix_link;

        Node(int start = -1, int end = -1, int length = 0)
        {
            this->start = start;
            this->end = end;
            this->length = length;
            this->suffix_link = nullptr;
            this->edges['\0'] = this;
        }

        bool is_in_edge(const std::string &s, char active_edge, int active_length, int index)
        {
            if (active_length == 0)
            {
                return this->edges.find(s[index]) != this->edges.end();
            }
            else
            {
                Node *cur = this->edges[active_edge];
                int char_index = cur->start + active_length;
                return s[char_index] == s[index];
            }
        }
    } * root;

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

    void insert_node(int index, Node *prev = nullptr)
    {
        Node *current = this->active.node;
        if (current->is_in_edge(this->text, this->active.edge, this->active.length, index))
        {
            if (this->active.length + 1 < current->edges[this->active.edge]->length)
            {
                this->active.set(current, this->active.edge, this->active.length + 1);
            }
            else
            {
                this->active.set(current->edges[this->text[index]], '\0', 1);
            }
            this->remainder++;
        }
        else
        {
            if (this->active.length != 0)
            {
                this->split_node(current->edges[this->active.edge], index, prev);
            }
            else
            {
                Node *new_node = new Node(index, this->size - 1, this->size - index);
                current->edges.insert({this->text[index], new_node});
                this->remainder--;
            }
        }
    }

    void split_node(Node *cur, int s_index, Node *prev_split)
    {
        if (prev_split != nullptr)
        {
            prev_split->suffix_link = cur;
        }
        
        cur->end = cur->start + this->active.length - 1;
        cur->length = this->active.length;

        Node *new_node_1 = new Node(
            cur->end + 1, 
            this->size - 1, 
            this->size - cur->end - 1);
        
        Node *new_node_2 = new Node(
            s_index, 
            this->size - 1, 
            this->size - s_index);

        cur->edges.insert({this->text[cur->end + 1], new_node_1});
        cur->edges.insert({this->text[s_index], new_node_2});
        this->remainder--;

        if (this->active.node == this->root)
        {
            this->active.set(
                this->root,
                this->text[s_index - this->remainder + 1],
                this->active.length - 1);
        }
        else
        {
            this->active.set(
                (cur->suffix_link == nullptr) ? this->root : cur->suffix_link,
                this->active.edge,
                this->active.length);
        }
        this->insert_node(s_index, cur);
    }

    void create_suffix_tree()
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->remainder <= 0)
            {
                this->remainder = 1;
            }
            this->insert_node(i);
        }
    }

public:
    explicit Suffix_Tree(const std::string s, char delimiter = '$')
    {
        this->root = new Node();

        this->active = Active();
        this->active.set(this->root, '\0', 0);

        this->text = s + delimiter;
        this->size = this->text.size();
        this->remainder = 0;

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
        printf("%d %d\n", current->start, current->end);
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
