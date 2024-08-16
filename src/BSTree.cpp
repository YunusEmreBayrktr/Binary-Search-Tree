#include<iostream>
#include "LLRBTree.cpp"
#include "AVLTree.cpp"
#include <fstream>

using namespace std;

class TreeNode {
public:
    string category;
    AVLTree AVLTree;
    LLRBTree LLRBTree;
    TreeNode * left;
    TreeNode * right;

    TreeNode(string category) {
        this->category = category;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    TreeNode * root;
    fstream AVLout;
    fstream LLRBTout;

    BST(string fileName1, string fileName2) {
        root = nullptr;
        AVLout.open(fileName1, ios::out);
        LLRBTout.open(fileName2, ios::out);
    }

    void save(){
        AVLout.close();
        LLRBTout.close();
    }

    bool isEmpty() {
        if (root == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    void insert(string category, string name, string price) {
        if (root == nullptr) {
            TreeNode* new_node = new TreeNode(category);
            new_node->AVLTree.AVLinsert(name, price);
            new_node->LLRBTree.insert(name, price);
            root = new_node;
        }
        else {
            TreeNode * temp = root;

            while (temp != nullptr) {
                if (category == temp->category) {
                    temp->AVLTree.AVLinsert(name, price);
                    temp->LLRBTree.insert(name, price);
                    return;
                }
                else if ((category.compare(temp->category) < 0) && (temp->left == nullptr)) {
                    TreeNode* new_node = new TreeNode(category);
                    new_node->AVLTree.AVLinsert(name, price);
                    new_node->LLRBTree.insert(name, price);
                    temp -> left = new_node;
                    break;
                }
                else if (category.compare(temp->category) < 0) {
                    temp = temp -> left;
                }
                else if ((category.compare(temp->category) > 0) && (temp -> right == nullptr)) {
                    TreeNode* new_node = new TreeNode(category);
                    new_node->AVLTree.AVLinsert(name, price);
                    new_node->LLRBTree.insert(name, price);
                    temp -> right = new_node;
                    break;
                }
                else {
                    temp = temp -> right;
                }
            }
        }
    }

    TreeNode * searchNode(string v) {
        if (root == nullptr) {
            return root;
        } else {
            TreeNode * temp = root;
            while (temp != nullptr) {
                if (v == temp -> category) {
                    return temp;
                } else if (v < temp -> category) {
                    temp = temp -> left;
                } else {
                    temp = temp -> right;
                }
            }
            return nullptr;
        }
    }

    int height(TreeNode * r) {
        if (r == nullptr)
            return -1;
        else {
            int lheight = height(r->left);
            int rheight = height(r->right);

            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }

    /* Print nodes at a given level */
    void printGivenLevel(TreeNode * r, int level) {
        if (r == nullptr)
            return;
        else if (level == 0) {
            AVLout << '"' << r->category << '"' << ":" << r->AVLTree.printAllItems(r->AVLTree.root) ;
            LLRBTout << '"' << r->category << '"' << ":" << r->LLRBTree.printAllItems(r->LLRBTree.root) << "\n";
        }
        else
        {
            printGivenLevel(r -> left, level - 1);
            printGivenLevel(r -> right, level - 1);
        }
    }

    void printAllItems() {
        AVLout << "command:printAllItems\n{\n" ;
        LLRBTout << "command:printAllItems\n{\n" ;
        int h = height(this->root);
        for (int i = 0; i <= h; i++)
            printGivenLevel(this->root, i);
        AVLout << "}\n" ;
        LLRBTout << "}\n" ;
    }

    void printAllItemsInCategory(string category){
        TreeNode* node = searchNode(category);
        if(node->AVLTree.root == nullptr){
            AVLout << "command:printAllItemsInCategory\t" << node->category <<
                   "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
            LLRBTout << "command:printAllItemsInCategory\t" << node->category <<
                     "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
        }
        else {
            AVLout << "command:printAllItemsInCategory\t" << node->category <<
                   "\n{\n" << '"' << category << '"' << node->AVLTree.printAllItems(node->AVLTree.root) << "}\n";
            LLRBTout << "command:printAllItemsInCategory\t" << node->category <<
                     "\n{\n" << '"' << category << '"' << node->LLRBTree.printAllItems(node->LLRBTree.root) << "\n}\n";
        }
    }

    void printItem(string category, string name){
        TreeNode* node = searchNode(category);
        if(node->AVLTree.root == nullptr){
            AVLout << "command:printItem\t" << node->category <<
                   "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
            LLRBTout << "command:printItem\t" << node->category <<
                     "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
        }
        else {
            AVLout << "command:printItem\t" << category << "\t" << name <<
                   "\n{\n" << '"' << category << '"' << ":\n\t" << node->AVLTree.getItem(name) << "\n}\n";
            LLRBTout << "command:printItem\t" << category << "\t" << name <<
                     "\n{\n" << '"' << category << '"' << ":\n\t" << node->LLRBTree.getItem(name) << "\n}\n";
        }
    }

    void find(string category, string name){
        TreeNode* node = searchNode(category);
        if(node->AVLTree.root == nullptr){
            AVLout << "command:printItem\t" << node->category <<
                   "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
            LLRBTout << "command:printItem\t" << node->category <<
                     "\n{\n" << '"' << category << '"' << ":" << "{} \n"<<"}\n";
        }
        else {
            AVLout << "command:printItem\t" << category << "\t" << name <<
                   "\n{\n" << '"' << category << '"' << ":\n\t" << node->AVLTree.getItem(name) << "\n}\n";
            LLRBTout << "command:printItem\t" << category << "\t" << name <<
                     "\n{\n" << '"' << category << '"' << ":\n\t" << node->LLRBTree.getItem(name) << "\n}\n";
        }
    }

    TreeNode * minValueNode(TreeNode * node) {
        TreeNode * current = node;

        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    void remove(string category, string name) {
        TreeNode* node = searchNode(category);
        node->AVLTree.AVLremove(name);
        node->LLRBTree.remove(name);
    }

    void updateData(string category, string name, string newPrice){
        TreeNode* node = searchNode(category);
        node->LLRBTree.searchNode(name)->price = newPrice;
        node->AVLTree.searchNode(name)->data = newPrice;
    }
};