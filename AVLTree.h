#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#include <iostream>

using namespace std;

template <typename T>
struct Node {

    Node<T>* right = nullptr;
    Node<T>* left = nullptr;
    Node<T>* parent = nullptr;
    unsigned height;
    T value;

    Node(const T& value): value{value}, height{1} {}

    Node(const T& value, Node<T>* _parent): value{value}, parent{_parent}, height{1} {}

    ~Node() {}
};

template <class T>
class AVLTree {
    Node<T>* root = nullptr;
public:

    AVLTree() = default;

    explicit AVLTree(T value) {
        root = new Node(value);
    }

	Node<T>* get_root() {
        return root;
    }

    int height(Node<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    bool isEmpty() {
        return root == nullptr;
    }

    Node<T>* find_parent(const T& value) {
        Node<T>* curr = root;
        Node<T>* parent = nullptr;
        while (curr) {
            parent = curr;
            if (value > curr->value)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return parent;
    }

    /// Rotations

    Node<T>* right_rotate(Node<T>* _node) {
        Node<T>* _root = _node;
        Node<T>* _rootChild = _node->left;

        _root->left = _rootChild->right;

        if (_rootChild->right) {
            _rootChild->right->parent = _root;
        }

        _rootChild->right = _root;

        if (_root->parent) {
            if (_root->parent->right == _root) {
                _root->parent->right = _rootChild;
            } else {
                _root->parent->left = _rootChild;
            }
            _root->parent = _rootChild;
        }

        _rootChild->parent = _root->parent;

        if (_node == root) {
            root = _rootChild;
        }

        _root->height = get_height(_root);
        _rootChild->height = get_height(_rootChild);
    }

    Node<T>* left_rotate(Node<T>* _node) {
        Node<T>* _root = _node;
        Node<T>* _rootChild = _node->right;

        _root->right = _rootChild->left;

        if (_rootChild->left) {
            _rootChild->left->parent = _root;
        }

        _rootChild->left = _root;

        if (_root->parent) {
            if (_root->parent->right == _root) {
                _root->parent->right = _rootChild;
            } else {
                _root->parent->left = _rootChild;
            }
            _root->parent = _rootChild;
        }

        _rootChild->parent = _root->parent;

        if (_node == root) {
            root = _rootChild;
        }

        _root->height = get_height(_root);
        _rootChild->height = get_height(_rootChild);
    }

    /// Obtener Altura

    unsigned get_height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        } else {
            // sacar la altura de casa sub-arbol
            unsigned left_height = get_height(node->left);
            unsigned right_height = get_height(node->right);

            // retornar la mayor altura de ambas
            if (left_height > right_height)
                return left_height+1;
            else
                return right_height+1;
        }
    }

    int get_height_difference(Node<T>* _node) {
        return int(get_height(_node->right)) - int(get_height(_node->left));
    }

    /// Insert

    void insert(const T& value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        } else {
            insert_helper(root, value);
        }
    }

    void insert_helper(Node<T>* _node, const T& value) {
        if (_node->value < value) {
            if (_node->right) {
                insert_helper(_node->right, value);
            } else {
                _node->right = new Node<T>(value, _node);
            }
        } else if (_node->value > value){
            if (_node->left) {
                insert_helper(_node->left, value);
            }
            else {
                _node->left = new Node<T>(value, _node);
            }
        } else {
            return;
        }

        _node->height = get_height(_node);

        int height_difference = get_height_difference(_node);

        if (height_difference < -1 && value < _node->left->value) {
            right_rotate(_node);
        } else if(height_difference > 1 && value > _node->right->value) {
            left_rotate(_node);
        } else if(height_difference > 1 && value < _node->right->value) {
            right_rotate(_node->right);
            left_rotate(_node);
        } else if(height_difference < -1 && value > _node->left->value) {
            left_rotate(_node->left);
            right_rotate(_node);
        }
    }

    void preorder(Node<T>* node) {
        if (node == NULL)
            return;
        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }


    void clear(Node<T>* _root) {
        if (_root == nullptr)
            return;
        clear(_root->left);
        clear(_root->right);
        delete _root;
    }

    ~AVLTree() {
        clear(root);
    }

};


#endif