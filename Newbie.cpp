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

public:
    RedBlackTree() {
        TNULL = new Node;
        initializeNULLNode(TNULL, nullptr);
        root = TNULL;
    }

    ~RedBlackTree() {
        // Placeholder for destructor logic
    }
};
