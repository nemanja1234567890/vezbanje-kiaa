#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void buildSegTree(vector<int> &seg_tree, vector<int> &array, int k, int x, int y) {
    if (x == y) {
        seg_tree[k] = array[x];

        return;
    }

    int middle = (x + y) / 2;
    buildSegTree(seg_tree, array, 2 * k, x, middle);
    buildSegTree(seg_tree, array, 2 * k + 1, middle + 1, y);

    seg_tree[k] = seg_tree[2 * k] + seg_tree[2 * k + 1];
}

int sumaSeg(vector<int> &seg_tree, int k, int x, int y, int a, int b) {
    if (x > b || y < a)
        return 0;

    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    return sumaSeg(seg_tree, 2 * k, x, middle, a, b) + sumaSeg(seg_tree, 2 * k + 1, middle + 1, y, a, b);
}

int main() {
    vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);
    buildSegTree(seg_tree, array, 1, 0, n - 1);

    int a, b;
    cout << "Unesi granice: ";
    cin >> a >> b;

    cout << "Suma segmenta: " << sumaSeg(seg_tree, 1, 0, n - 1, a, b) << "\n";

    return 0;
}
