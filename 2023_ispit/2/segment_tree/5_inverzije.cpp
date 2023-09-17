#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void transliraj_niz(vector<int> &niz, int n, int x) {
    for (int i = 0; i < n; i++)
        niz[i] -= x;
}

void updateTree(vector<int> &seg_tree, int k, int x, int y, int vrednost) {
    if (x == y) {
        seg_tree[k]++;

        return;
    }

    int middle = (x + y) / 2;
    if (vrednost <= middle)
        updateTree(seg_tree, 2 * k, x, middle, vrednost);
    else
        updateTree(seg_tree, 2 * k + 1, middle + 1, y, vrednost);

    seg_tree[k] =  seg_tree[2 * k] + seg_tree[2 * k + 1];
}

int sumaSeg(vector<int> &seg_tree, int k, int x, int y, int a, int b) {
    if (x > b || y < a)
        return 0;

    if (x >= a && y <= b)
        return seg_tree[k];

    int middle = (x + y) / 2;
    return sumaSeg(seg_tree, 2 * k, x, middle, a, b) + sumaSeg(seg_tree, 2 * k + 1, middle + 1, y, a , b);
}

int main() {
//         vector<int> array = {8, 8, 4, 4, 2, 1};        // Izlaz: 13
//     vector<int> array = {8, 8, 4, 0, 2, 1};        // Izlaz: 12
//     vector<int> array = {7, -89, -89, -90, 100, 1, 2};     // Izlaz: 9
    vector<int> array = {7, -89, -89, 100, 1, 2};      // Izlaz: 6

    int n = array.size();
    int min_el = *min_element(array.begin(), array.end());
    if (min_el < 0)
        transliraj_niz(array, n, min_el);

    int max_el = *max_element(array.begin(), array.end());
    int height = ceil(log2(max_el));
    int size = 2 * pow(2, height);

    vector<int> seg_tree(size);

    int rez = 0;
    for (int i = 0; i < n; i++) {
        updateTree(seg_tree, 1, 0, max_el, array[i]);
        rez += sumaSeg(seg_tree, 1, 0, max_el, array[i] + 1, max_el);
    }

    cout << "Broj inverzija: " << rez << "\n";

    return 0;
}
