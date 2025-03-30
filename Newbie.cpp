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
    void inorderForCategories(Node *node, map<string, vector<string>> &categories) {
        if (node != TNULL) {
            inorderForCategories(node->left, categories);
            string category = categorizeKey(node->key);
            categories[category].push_back(node->value);
            inorderForCategories(node->right, categories);
        }
    }
    void fixInsert(Node *node) {
        Node *uncle;
        while (node->parent && node->parent->color) {
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;
                if (uncle && uncle->color) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rightRotate(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->left;
                if (uncle && uncle->color) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    leftRotate(node->parent->parent);
                }
            }
            if (node == root) break;
        }
        root->color = false;
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

    void inorderTraversal(Node *node, ostream &out) {
        if (node != TNULL) {
            inorderTraversal(node->left, out);
            out << node->key << " " << node->value << "\n";
            inorderTraversal(node->right, out);
        }
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
    
    void insert(int key, const string &value) {
        Node *node = new Node;
        node->parent = nullptr;
        node->key = key;
        node->value = value;
        node->left = TNULL;
        node->right = TNULL;
        node->color = true;

        Node *parent = nullptr;
        Node *current = root;

        while (current != TNULL) {
            parent = current;
            if (key < current->key) current = current->left;
            else current = current->right;
        }

        node->parent = parent;
        if (!parent) root = node;
        else if (key < parent->key) parent->left = node;
        else parent->right = node;

        if (!node->parent) {
            node->color = false;
            return;
        }

        if (!node->parent->parent) return;

        fixInsert(node);
    }

    Node *search(int key) {
        Node *current = root;
        while (current != TNULL && current->key != key) {
            if (key < current->key) current = current->left;
            else current = current->right;
        }
        return current;
    }
    void updateFile(const string &filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << " for writing!" << endl;
            return;
        }
        inorderTraversal(root, file);
        file.close();
        cout << "Tree state written to " << filename << "!" << endl;
    }
    

    void loadDataFromFile(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: File could not be opened!" << endl;
            return;
        }
        int key;
        string value;
        while (file >> key >> value) {
            insert(key, value);
        }
        file.close();
    }
    
};
