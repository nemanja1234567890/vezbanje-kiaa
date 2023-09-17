#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

struct Node
{
    int largest;
    int s_largest;
};

void buildSegTree(vector<Node> &seg_tree, vector<int> &array, int k, int x, int y) {
    if (x == y) {
        seg_tree[k].largest = array[x];
        seg_tree[k].s_largest = INT_MIN;

        return;
    }

    int middle = (x + y) / 2;
    buildSegTree(seg_tree, array, 2 * k, x, middle);
    buildSegTree(seg_tree, array, 2 * k + 1, middle + 1, y);

    seg_tree[k].largest = max(seg_tree[2 * k].largest, seg_tree[2 * k + 1].largest);
    seg_tree[k].s_largest = min(max(seg_tree[2 * k].largest, seg_tree[2 * k + 1].s_largest),
                                max(seg_tree[2 * k].s_largest, seg_tree[2 * k + 1].largest));
}

Node sumaSeg(vector<Node> &seg_tree, int k, int x, int y, int a, int b) {
    Node tmp_node;
    tmp_node.largest = INT_MIN;
    tmp_node.s_largest = INT_MIN;

    if (x > b || y < a)
        return tmp_node;
    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    Node levi = sumaSeg(seg_tree, 2 * k, x, middle, a, b);
    Node desni = sumaSeg(seg_tree, 2 * k + 1, middle + 1, y, a, b);

    tmp_node.largest = max(levi.largest, desni.largest);
    tmp_node.s_largest = min(max(levi.largest, desni.s_largest),
                             max(levi.s_largest, desni.largest));

    return tmp_node;
}

int main() {
    vector<int> array = {1, 8, 6, 5, 7, 4, 2, 3};

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<Node> seg_tree(size);
    buildSegTree(seg_tree, array, 1, 0, n - 1);

    int a, b;
    cout << "Unesi granice: ";
    cin >> a >> b;

    Node tmp_node = sumaSeg(seg_tree, 1, 0, n - 1, a, b);
    cout << "Proizvod: " << tmp_node.largest * tmp_node.s_largest << "\n";

    return 0;
}
