#include <stack>
#include <stdio.h>
#include <vector>
#include <functional>

template <typename T1, typename T2>
class Red_Black_Tree
{
private:
    enum Node_Color
    {
        RED,
        BLACK
    };

    // Node in the tree
    struct Node
    {
        T1 key;
        T2 data;
        Node *left_child, *right_child, *parent;
        Node_Color color;

        Node(T1 key, T2 data)
        {
            this->key = key;
            this->data = data;
            this->left_child = nullptr;
            this->right_child = nullptr;
            this->parent = nullptr;
            this->color = RED;
        }
    };

    Node *root;

    Node *NIL;

    /**
     * Left rotates a node in tree by replacing its position
     * with its right child and making the given node the left child
     * of the replacing node
     */
    void left_rotate(Node *current)
    {
        Node *right = current->right_child;
        current->right_child = right->left_child;

        if (right->left_child != this->NIL)
        {
            right->left_child->parent = current;
        }

        right->parent = current->parent;
        if (current->parent == this->NIL)
        {
            this->root = right;
        }
        else if (current->parent->right_child == current)
        {
            current->parent->right_child = right;
        }
        else
        {
            current->parent->left_child = right;
        }

        right->left_child = current;
        current->parent = right;
    }

    /**
     * Right rotates a node in tree by replacing its position
     * with its left child and making the given node the right child
     * of the replacing node.
     */
    void right_rotate(Node *current)
    {
        Node *left = current->left_child;
        current->left_child = left->right_child;

        if (left->right_child != this->NIL)
        {
            left->right_child->parent = current;
        }

        left->parent = current->parent;
        if (current->parent == this->NIL)
        {
            this->root = left;
        }
        else if (current->parent->left_child == current)
        {
            current->parent->left_child = left;
        }
        else
        {
            current->parent->right_child = left;
        }

        left->right_child = current;
        current->parent = left;
    }

    /**
     * Inserts a node into the tree
     */
    void rb_insert(Node *new_node)
    {
        if (new_node == this->NIL)
        {
            return;
        }
        Node *trailing = this->NIL;
        Node *cur = this->root;

        while (cur != this->NIL)
        {
            trailing = cur;
            if (new_node->key < cur->key)
            {
                cur = cur->left_child;
            }
            else
            {
                cur = cur->right_child;
            }
        }

        new_node->parent = trailing;
        if (trailing == this->NIL)
        {
            this->root = new_node;
        }
        else if (new_node->key < trailing->key)
        {
            trailing->left_child = new_node;
        }
        else
        {
            trailing->right_child = new_node;
        }
        new_node->left_child = this->NIL;
        new_node->right_child = this->NIL;
        this->rb_insert_fixup(new_node);
    }

    /**
     * Fixes up the tree so that the tree remains balanced
     * after insertion
     */
    void rb_insert_fixup(Node *current)
    {
        while (current->parent->color == RED)
        {
            Node *grand_parent = current->parent->parent;
            if (grand_parent->left_child == current->parent)
            {
                Node *right = grand_parent->right_child;
                if (right->color == RED)
                {
                    current->parent->color = BLACK;
                    right->color = BLACK;
                    grand_parent->color = RED;
                    current = grand_parent;
                }
                else
                {
                    if (current == current->parent->right_child)
                    {
                        current = current->parent;
                        this->left_rotate(current);
                    }

                    current->parent->color = BLACK;
                    grand_parent = current->parent->parent;
                    grand_parent->color = RED;
                    this->right_rotate(grand_parent);
                }
            }
            else
            {
                Node *left = grand_parent->left_child;

                if (left->color == RED)
                {
                    current->parent->color = BLACK;
                    left->color = BLACK;
                    grand_parent->color = RED;
                    current = grand_parent;
                }

                else
                {
                    if (current == current->parent->left_child)
                    {
                        current = current->parent;
                        this->right_rotate(current);
                    }

                    current->parent->color = BLACK;
                    grand_parent = current->parent->parent;
                    grand_parent->color = RED;
                    this->left_rotate(grand_parent);
                }
            }
        }
        this->root->color = BLACK;
    }

    /**
     * Replaces a node with another node
     */
    void rb_transplant(Node *replaced, Node *replacing)
    {
        if (replaced->parent == this->NIL)
        {
            this->root = replacing;
        }
        else if (replaced->parent->left_child == replaced)
        {
            replaced->parent->left_child = replacing;
        }
        else
        {
            replaced->parent->right_child = replacing;
        }
        replacing->parent = replaced->parent;
    }

    /**
     *  Returns the minimum node in a given sub-tree
     */
    Node *min_in_tree(Node *current)
    {
        if (current->left_child == this->NIL)
        {
            return current;
        }
        else
        {
            return this->min_in_tree(current->left_child);
        }
    }

    /**
     * Returns the maximum node in a given sub-tree
     */
    Node *max_in_tree(Node *current)
    {
        if (current->right_child == this->NIL)
        {
            return current;
        }
        else
        {
            return this->max_in_tree(current->right_child);
        }
    }

    /**
     * Deletes a given a node in the tree
     */
    void rb_delete(Node *del_node)
    {
        Node_Color orginal_color = del_node->color;
        Node *next_node;

        if (del_node->left_child == this->NIL)
        {
            next_node = del_node->right_child;
            this->rb_transplant(del_node, del_node->right_child);
        }
        else if (del_node->right_child == this->NIL)
        {
            next_node = del_node->left_child;
            this->rb_transplant(del_node, del_node->left_child);
        }
        else
        {
            Node *successor = this->min_in_tree(del_node->right_child);
            orginal_color = successor->color;
            next_node = successor->right_child;

            if (successor->parent == del_node)
            {
                next_node->parent = successor;
            }
            else
            {
                this->rb_transplant(successor, successor->right_child);
                successor->right_child = del_node->right_child;
                successor->right_child->parent = successor;
            }

            this->rb_transplant(del_node, successor);
            successor->left_child = del_node->left_child;
            successor->left_child->parent = successor;
            successor->color = del_node->color;
        }

        if (orginal_color == BLACK)
        {
            this->rb_delete_fixup(next_node);
        }
    }

    /**
     * Maintains the tree height after a node has been deleted
     */
    void rb_delete_fixup(Node *current)
    {
        while (current != this->root && current->color == BLACK)
        {
            if (current == current->parent->left_child)
            {
                Node *right = current->parent->right_child;
                if (right->color == RED)
                {
                    right->color = BLACK;
                    current->parent->color = RED;
                    this->left_rotate(current->parent);
                    right = current->parent->right_child;
                }

                if (right->left_child->color == BLACK && right->right_child->color == BLACK)
                {
                    right->color = RED;
                    current = current->parent;
                }
                else
                {
                    if (right->right_child->color == BLACK)
                    {
                        right->left_child->color = BLACK;
                        right->color = RED;
                        this->right_rotate(right);
                        right = current->parent->right_child;
                    }

                    right->color = current->parent->color;
                    current->parent->color = BLACK;
                    right->right_child->color = BLACK;
                    this->left_rotate(current->parent);
                    current = this->root;
                }
            }
            else
            {
                Node *left = current->parent->left_child;
                if (left->color == RED)
                {
                    left->color = BLACK;
                    current->parent->color = RED;
                    this->right_rotate(current->parent);
                    left = current->parent->left_child;
                }

                if (left->left_child->color == BLACK && left->right_child->color == BLACK)
                {
                    left->color = RED;
                    current = current->parent;
                }
                else
                {
                    if (left->left_child->color == BLACK)
                    {
                        left->right_child->color = BLACK;
                        left->color = RED;
                        this->left_rotate(left);
                        left = current->parent->left_child;
                    }

                    left->color = current->parent->color;
                    current->parent->color = BLACK;
                    left->left_child->color = BLACK;
                    this->right_rotate(current->parent);
                    current = this->root;
                }
            }
        }
        current->color = BLACK;
    }

    Node *rb_search(T1 key)
    {
        Node *current = this->root;
        while (current != this->NIL)
        {
            if (key < current->key)
            {
                current = current->left_child;
            }
            else if (key > current->key)
            {
                current = current->right_child;
            }
            else
            {
                return current;
            }
        }
        return this->NIL;
    }

public:
    Red_Black_Tree()
    {
        this->NIL = new Node(T1(), T2());
        this->NIL->left_child = this->NIL;
        this->NIL->right_child = this->NIL;
        this->NIL->color = BLACK;
        this->root = this->NIL;
    }

    ~Red_Black_Tree()
    {
        std::function<void(Node *)> delete_node =
            [&delete_node, this](Node *current) -> void
        {
            if (current != this->NIL)
            {
                delete_node(current->left_child);
                delete_node(current->right_child);
                delete current;
            }
        };

        delete_node(this->root);
        delete this->NIL;
    }

    /**
     * Inserts a node into the tree with the given key and value
     */
    void insert(T1 key, T2 data)
    {
        Node *new_node = new Node(key, data);
        this->rb_insert(new_node);
    }

    /**
     * Removes a node with given key in the tree
     */
    void remove(T1 key)
    {
        Node *cur = this->rb_search(key);
        if (cur != this->NIL)
        {
            this->rb_delete(cur);
        }
    }

    /**
     * Preorder traversal
     * Returns the elements in preorder traversal
     */
    std::vector<std::pair<T1, T2>> preorder_traversal()
    {
        std::vector<std::pair<T1, T2>> result;
        std::stack<Node *> stack;

        if (this->root != this->NIL)
        {
            stack.push(this->root);

            while (!stack.empty())
            {
                Node *current = stack.top();
                stack.pop();

                result.push_back(std::make_pair(current->key, current->data));

                if (current->right_child != this->NIL)
                {
                    stack.push(current->right_child);
                }

                if (current->left_child != this->NIL)
                {
                    stack.push(current->left_child);
                }
            }
        }
        return result;
    }

    /**
     * Inorder traversal
     * Returns all the key and data pairs in a vector
     */
    std::vector<std::pair<T1, T2>> inorder_traversal()
    {
        std::vector<std::pair<T1, T2>> result;
        std::stack<Node *> stack;
        Node *current = this->root;

        while (!stack.empty() || current != this->NIL)
        {
            if (current != this->NIL)
            {
                stack.push(current);
                current = current->left_child;
            }
            else
            {
                Node *top = stack.top();
                stack.pop();
                result.push_back(std::make_pair(top->key, top->data));
                current = top->right_child;
            }
        }

        return result;
    }

    /**
     * Post-Order Traversal
     */
    std::vector<std::pair<T1, T2>> postorder_traversal()
    {
        std::vector<std::pair<T1, T2>> result;
        Node *last_node = this->NIL, *current = this->root;
        std::stack<Node *> stack;

        while (current != this->NIL || !stack.empty())
        {
            if (current != this->NIL)
            {
                stack.push(current);
                current = current->left_child;
            }
            else
            {
                Node *top = stack.top();

                if (top->right_child != this->NIL && last_node != top->right_child)
                {
                    current = top->right_child;
                }
                else
                {
                    result.push_back(std::make_pair(top->key, top->data));
                    last_node = top;
                    stack.pop();
                }
            }
        }
        return result;
    }
};