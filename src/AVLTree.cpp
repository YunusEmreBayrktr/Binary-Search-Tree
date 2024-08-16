#include <iostream>
#include <algorithm>
#include <string>

class AVLTree
{
public:
    struct Node
    {
        std::string key;
        std::string data;
        int height;
        Node *left;
        Node *right;

        Node(std::string k, std::string d) : key(k), data(d), height(1), left(NULL), right(NULL) {}
    };

    Node *root;
    std::string out ;

    int height(Node *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int balanceFactor(Node *node)
    {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node *node)
    {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node *AVLrotateRight(Node *node)
    {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        updateHeight(node);
        updateHeight(left);
        return left;
    }

    Node *AVLrotateLeft(Node *node)
    {
        Node *right = node->right;
        node->right = right->left;
        right->left = node;
        updateHeight(node);
        updateHeight(right);
        return right;
    }

    Node *AVLbalance(Node *node)
    {
        updateHeight(node);

        if (balanceFactor(node) == 2)
        {
            if (balanceFactor(node->left) < 0)
                node->left = AVLrotateLeft(node->left);
            return AVLrotateRight(node);
        }
        if (balanceFactor(node) == -2)
        {
            if (balanceFactor(node->right) > 0)
                node->right = AVLrotateRight(node->right);
            return AVLrotateLeft(node);
        }

        return node;
    }

public:
    AVLTree() : root(NULL) {}

    void AVLinsert(std::string key, std::string data)
    {
        root = AVLinsertNode(root, key, data);
    }

    void AVLremove(std::string key)
    {
        root = AVLremoveNode(root, key);
    }

    std::string AVLsearch(std::string key)
    {
        Node *node = root;
        while (node != NULL)
        {
            if (key == node->key)
                return node->data;
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return "";
    }

    void AVLprint(Node *node, int level)
    {
        if (node != NULL)
        {
            AVLprint(node->right, level + 1);
            for (int i = 0; i < 4 * level; i++)
                std::cout << " ";
            std::cout << node->key << ":" << node->data << std::endl;
            AVLprint(node->left, level + 1);
        }
    }

    void printSingleLevel(Node* node, int level) {

        if ( node == nullptr){
            return;
        }
        else if (level == 0) {
            out += '"' + node->key + '"' + ":" + '"' + node->data + '"' + ","  ;
        }
        else
        {
            printSingleLevel(node->left, level-1);
            printSingleLevel(node->right, level-1);
        }
    }

    std::string printAllItems(Node* node) {
        this->out = "";
        if (this->root == nullptr) {
            return out += "{}\n";
        }
        int height = root->height;

        for (int i = 0; i <= height; i++) {

            out += "\n\t";
            printSingleLevel(node, i);
            out.pop_back();
        }
        return this->out;
    }

    std::string getItem(std::string name){
        Node* node = searchNode(name);
        if (node == nullptr){
            return  "{}";
        }
        else {
            return '"' + node->key + '"' + ':' + '"' + node->data + '"';
        }
    }

    Node * searchNode(std::string v) {
        if (root == nullptr) {
            return root;
        } else {
            Node * temp = root;
            while (temp != nullptr) {
                if (v == temp->key) {
                    return temp;
                } else if (v.compare(temp->key) < 0) {
                    temp = temp -> left;
                } else {
                    temp = temp -> right;
                }
            }
            return nullptr;
        }
    }

private:
    Node *AVLinsertNode(Node *node, std::string key, std::string data)
    {
        if (node == NULL)
            return new Node(key, data);

        if (key < node->key)
            node->left = AVLinsertNode(node->left, key, data);
        else
            node->right = AVLinsertNode(node->right, key, data);

        return AVLbalance(node);
    }

    Node *AVLremoveNode(Node *node, std::string key)
    {
        if (node == NULL)
            return NULL;

        if (key < node->key)
            node->left = AVLremoveNode(node->left, key);
        else if (key > node->key)
            node->right = AVLremoveNode(node->right, key);
        else
        {
            Node *left = node->left;
            Node *right = node->right;
            delete node;
            if (right == NULL)
                return left;
            Node *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return AVLbalance(min);
        }
        return AVLbalance(node);
    }

    Node *findMin(Node *node)
    {
        if (node->left == NULL)
            return node;
        return findMin(node->left);
    }

    Node *removeMin(Node *node)
    {
        if (node->left == NULL)
            return node->right;
        node->left = removeMin(node->left);
        return AVLbalance(node);
    }

};