#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> coll = {1,2,3,4,5,6,7,8,9};

    // find position of element with value 5
    vector<int>::const_iterator pos;
    pos = find(coll.cbegin(), coll.cend(), 3);

    //print the found value
    cout << "pos: " << *pos << endl;

    // convert iterator to reerse iterator rpos
    vector<int>::const_reverse_iterator rpos(pos);

    //print the found value using reverse iterator
    cout << "rpos: " << *rpos << endl;

    //reversed vector:
    std::reverse_iterator<vector<int>::const_iterator> rbegin(coll.cend());       
}
