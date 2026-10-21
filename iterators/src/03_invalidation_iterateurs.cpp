#include <iostream>
#include <vector>
using namespace std;

int main() {
vector<int> v={1,2,3};
auto it=v.begin();
v.insert(v.begin(), 0); // insert 0 at the beginning
cout << "v: " << *it;

// c'est un comportement indefini, car l'iterateur it pointe vers un element qui a ete deplace

}// c'est un comportement indefini, car l'iterateur it pointe vers un element qui a ete deplace