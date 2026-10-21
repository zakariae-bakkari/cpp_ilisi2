#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 1. Inverser par indices : de l'indice 2 (valeur 3) à l'indice 5 (valeur 6) inclus
    reverse(v.begin() + 2, v.begin() + 5 + 1);

    cout << "Apres reverse par indices : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // 2. Inverser par valeurs : entre la valeur 8 et la valeur 9
    auto pos1 = find(v.begin(), v.end(), 8);
    auto pos2 = find(v.begin(), v.end(), 9);

    reverse(pos1, pos2 + 1);

    cout << "Apres reverse par valeurs : ";
    for (int x : v) cout << x << " ";
    cout << endl;

    return 0;
}
