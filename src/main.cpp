#include <iostream>
#include <vector>
#include "BSTree.cpp"

vector<string> split(const string &text, char sep);


int main(int argc, char* args[]) {

    BST web(args[2], args[3]);

    fstream input;
    input.open(args[1], ios::in);

    string line;
    while (std::getline(input, line)) {
        vector<string> text = split(line, '\t');


        if(text[0] == "insert"){
            web.insert(text[1], text[2], text[3]);
        }
        else if(text[0] == "remove"){
            web.remove(text[1], text[2]);
        }
        else if(text[0] == "printAllItems"){
            web.printAllItems();
        }
        else if(text[0] == "printAllItemsInCategory"){
            web.printAllItemsInCategory(text[1]);
        }
        else if(text[0] == "printItem"){
            web.printItem(text[1], text[2]);
        }
        else if(text[0] == "find"){
            //web.find(text[1], text[2]);
        }
        else if(text[0] == "updateData"){
            web.updateData(text[1], text[2], text[3]);
        }
    }
    input.close();
    web.save();

    return 0;
}

vector<string> split(const string &text, char sep) {

    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        if (end != start) {
            tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
        tokens.push_back(text.substr(start));
    }
    return tokens;
}