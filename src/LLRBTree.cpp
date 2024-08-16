#include <iostream>


using namespace std;
enum Color {RED, BLACK};

struct Node {
    string name;
    string price;
    Node *left;
    Node *right;
    Color color;
    Node(string name, string price) : name(name), price(price), left(nullptr), right(nullptr), color(RED) {}
};

class LLRBTree {
public:
    Node *root;
private:
    string out;

    bool isRed(Node *node) {
        if (node == nullptr) return false;
        return node->color == RED;
    }

    Node* rotateLeft(Node *node) {
        Node *right = node->right;
        node->right = right->left;
        right->left = node;
        right->color = node->color;
        node->color = RED;
        return right;
    }

    Node* rotateRight(Node *node) {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        left->color = node->color;
        node->color = RED;
        return left;
    }

    void flipColors(Node *node) {
        node->color = static_cast<Color>(!node->color);
        node->left->color = static_cast<Color>(!node->left->color);
        node->right->color = static_cast<Color>(!node->right->color);
    }

    Node* insert(Node *node, string name, string price) {
        if (node == nullptr) return new Node(name, price);

        if (name.compare(node->name) < 0) {
            node->left = insert(node->left, name, price);
        } else if (name.compare(node->name) > 0) {
            node->right = insert(node->right, name, price);
        }

        if (isRed(node->right) && !isRed(node->left)) node = rotateLeft(node);
        if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
        if (isRed(node->left) && isRed(node->right)) flipColors(node);

        return node;
    }

    Node* remove(Node *node, string name) {
        if (node == nullptr) return nullptr;

        if (name.compare(node->name) < 0) {
            node->left = remove(node->left, name);
        } else if (name.compare(node->name) > 0) {
            node->right = remove(node->right, name);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                return temp;
            } else {
                Node *successor = findSuccessor(node);
                node->name = successor->name;
                node->right = remove(node->right, successor->name);
            }
        }

        if (isRed(node->right) && !isRed(node->left)) node = rotateLeft(node);
        if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
        if (isRed(node->left) && isRed(node->right)) flipColors(node);

        return node;
    }

    Node* findSuccessor(Node *node) {
        Node *temp = node->right;
        while (temp->left != nullptr) temp = temp->left;
        return temp;
    }

    bool search(Node *node, string name ) {
        if (node == nullptr) return false;
        if (name == node->name) return true;
        if (name.compare(node->name) < 0) return search(node->left, name);
        else return search(node->right, name);
    }

    void LLRBTprint(Node *node, int level)
    {
        if (node != NULL)
        {
            LLRBTprint(node->right, level + 1);
            for (int i = 0; i < 4 * level; i++)
                std::cout << " ";
            std::cout << node->name << ":" <<node->price << ":"  << std::endl;
            LLRBTprint(node->left, level + 1);
        }
    }

    int height(Node* root) {
        if (root == nullptr) {
            return -1;
        }
        int left_height = height(root->left);
        int right_height = height(root->right);
        return 1 + std::max(left_height, right_height);
    }

    void printSingleLevel(Node* node, int level) {

        if ( node == nullptr){
            return;
        }
        else if (level == 0) {
            out += '"' + node->name + '"' + ":" + '"' + node->price + '"' + ","  ;
        }
        else
        {
            printSingleLevel(node->left, level-1);
            printSingleLevel(node->right, level-1);
        }
    }

public:
    LLRBTree() : root(nullptr) {}

    void insert(string name, string price) {
        root = insert(root, name, price);
        root->color = BLACK;
    }

    void remove(string name) {
        root = remove(root, name);
        if (root != nullptr) root->color = BLACK;
    }

    Node * searchNode(std::string v) {
        if (root == nullptr) {
            return root;
        } else {
            Node * temp = root;
            while (temp != nullptr) {
                if (v == temp->name) {
                    return temp;
                } else if (v.compare(temp->name) < 0) {
                    temp = temp -> left;
                } else {
                    temp = temp -> right;
                }
            }
            return nullptr;
        }
    }

    std::string printAllItems(Node* node) {
        this->out = "";
        if (this->root == nullptr) {
            out += "{}\n";
        }
        int h = height(this->root);

        for (int i = 0; i <= h; i++) {
            out += "\n\t";
            printSingleLevel(node, i);
            out.pop_back();
        }
        return this->out;
    }

    std::string getItem(std::string name){
        Node* node = searchNode(name);
        if(node == nullptr){
            return "{}";
        }
        else {
            return '"' + node->name + '"' + ':' + '"' + node->price + '"';
        }
    }

};
