#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Node {
    int key;
    string value;
    Node* parent;
    Node* left;
    Node* right;
    bool color; // true = Red, false = Black
};

class RedBlackTree {
private:
    Node* root;
    Node* TNULL;

    void initializeNULLNode(Node* node, Node* parent) {
        node->key = 0;
        node->value = "";
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = false; // Black
    }
    void inOrderHelper(Node* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->key << ": " << node->value << " ";
            inOrderHelper(node->right);
        }
    }
    void clearTree(Node *node) {
        if (node == TNULL) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }
    string categorizeKey(int key) {
        if (key >= 101 && key <= 199) return "Fruits";
        if (key >= 201 && key <= 299) return "Dairy";
        if (key >= 301 && key <= 399) return "Bakery";
        if (key >= 401 && key <= 499) return "Grains";
        return "Other";
    }

    int countNodes(Node *node) {
        if (node == TNULL) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
public:
    RedBlackTree() {
        TNULL = new Node;
        initializeNULLNode(TNULL, nullptr);
        root = TNULL;
    }

    ~RedBlackTree() {
        // Placeholder for destructor logic
    }
    void inOrderTraversal() {
        inOrderHelper(root);
        cout << endl;
    }

    // Placeholder for insert functionality
    void insert(int key, string value) {
        cout << "Insert function called with key: " << key << " and value: " << value << endl;
        // Placeholder logic for inserting nodes
    }
    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }
    
    Node* search(int key) {
        return searchTreeHelper(root, key);
    }
    
};
