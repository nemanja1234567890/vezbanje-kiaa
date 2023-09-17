#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool prostBroj(int x) {
    if (x == 1)
        return false;

    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0)
            return false;

    return true;
}

void buildSegTree(vector<int> &seg_tree, vector<int> &array, int k, int x, int y) {
    if (x == y) {
        if (!prostBroj(array[x]))
            seg_tree[k] = 1;
        else
            seg_tree[k] = 0;

        return;
    }

    int middle = (x + y) / 2;
    buildSegTree(seg_tree, array, 2 * k, x, middle);
    buildSegTree(seg_tree, array, 2  * k + 1, middle + 1, y);

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
    vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8};

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);
    buildSegTree(seg_tree, array, 1, 0, n - 1);

    int a, b;
    cout << "Unesi granice: ";
    cin >> a >> b;

    cout << "Broj slozenih: " << sumaSeg(seg_tree, 1, 0, n - 1, a, b) << "\n";

    return 0;
}
