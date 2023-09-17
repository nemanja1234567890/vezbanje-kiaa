#include <iostream>
#include <vector>
#include <climits>
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

// void ispisi(vector<int> niz) {
//     for (int x : niz)
//         cout << x << " ";
//     cout << "\n";
// }

int sum_of_seg(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b) {
    if (lazy_values[k] != 0) {
        // posto dodeljujemo vrednost moramo za ceo segment da pomnozimo tu vrednost
        seg_tree[k] = lazy_values[k] * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] = lazy_values[k];
            lazy_values[2 * k + 1] = lazy_values[k];
        }

        lazy_values[k] = 0;
    }
    // isti kod kao kod segmentna za zbir
    if (x > b || y < a)
        return 0;
    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    return sum_of_seg(seg_tree, lazy_values, 2 * k, x, middle, a, b)
             + sum_of_seg(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b);
}

void update_tree(vector<int> &seg_tree, vector<int> &lazy_values, int k, int x, int y, int a, int b, int vrednost) {
    if (lazy_values[k] != 0) {
        // posto dodeljujemo vrednost moramo za ceo segment da pomnozimo tu vrednost
        seg_tree[k] = lazy_values[k] * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] = lazy_values[k];
            lazy_values[2 * k + 1] = lazy_values[k];
        }

        lazy_values[k] = 0;
    }

    if (x > b || y < a)
        return;
    if (x >= a && y <= b) {
        seg_tree[k] = vrednost * (y - x + 1);

        if (x != y) {
            lazy_values[2 * k] = vrednost;
            lazy_values[2 * k + 1] = vrednost;
        }
        return;
    }

    int middle = (x + y) / 2;
    update_tree(seg_tree, lazy_values, 2 * k, x, middle, a, b, vrednost);
    update_tree(seg_tree, lazy_values, 2 * k + 1, middle + 1, y, a, b, vrednost);

    seg_tree[k] = seg_tree[2 * k] + seg_tree[2 * k + 1];
}

int main() {
    vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();
    int height = ceil(log2(n));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);
    vector<int> lazy_values(size, 0);

    buildSegTree(seg_tree, array, 1, 0, n - 1);

    // a = 2     b =  4       vrednost = 6
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 2, 4, 6);
    // a = 3     b =  5       vrednost = 10
    update_tree(seg_tree, lazy_values, 1, 0, n - 1, 3, 5, 10);

    int a, b;
    cout << "Unesi granice: ";
    cin >> a >> b;

    cout << "sum_of_seg: " << sum_of_seg(seg_tree, lazy_values, 1, 0, n - 1, a, b) << "\n";

    return 0;
}
