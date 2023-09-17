#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int strToInt(string x) {
    int rez = 0;
    int n = x.size();

    for (int i = 0, j = n - 1; i < n; i++, j--)
        rez += (x[j] - '0') * pow(2, i);

    return rez;
}

struct Node
{
    bool is_leaf;
    Node* nodes[2];
};

Node* createNode() {
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->is_leaf = false;
    new_node->nodes[0] = new_node->nodes[1] = nullptr;

    return new_node;
}

void freeTree(Node *root) {
    if (root == nullptr)
        return;
    for (auto &iter : root->nodes)
        freeTree(iter);
    free(root);
}

void addNum(Node *root, string &num) {
    for (char c : num) {
        int digit = c - '0';
        if (root->nodes[digit] == nullptr) {
            root->nodes[digit] = createNode();
        }
        root = root->nodes[digit];
    }

    root->is_leaf = true;
}

void findXOR(Node *root, string &word, string &XOR) {
    for (char c : word) {
        int digit = c - '0';
        if (root->nodes[abs(digit - 1)]) {
            XOR += "1";
            root = root->nodes[abs(digit - 1)];
        }
        else {
            XOR += "0";
            root = root->nodes[digit];
        }
    }
}

int main() {
    vector<string> numbers = {"101", "000", "011"};

    Node *root = createNode();

    string MAX_XOR, XOR;
    int max = 0;
    for (string &s : numbers) {
        XOR = "";
        addNum(root, s);
        findXOR(root, s, XOR);

        if (strToInt(XOR) > max) {
            max = strToInt(XOR);
            MAX_XOR = XOR;
        }
    }

    cout << "MAX_XOR: " << MAX_XOR << "\t" << max << "\n";

    freeTree(root);
    return 0;
}
