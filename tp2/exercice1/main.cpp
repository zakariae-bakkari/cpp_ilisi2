#include <iostream>
#include "recherche.h"
using namespace std;

int main()
{
    string s1, s2;

    cout << "mot 1 : ";
    cin >> s1;
    cout << "mot 2 : ";
    cin >> s2;

    if (recherche(s1, s2))
        cout << s2 << " se trouve dans " << s1 << endl;
    else
        cout << s2 << " ne se trouve pas dans " << s1 << endl;

    return 0;
}
