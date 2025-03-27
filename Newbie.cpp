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
