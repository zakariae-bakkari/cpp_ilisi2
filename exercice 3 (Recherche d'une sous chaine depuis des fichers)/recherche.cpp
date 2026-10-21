// Exercice 1 : est ce que les lettres de s2 sont dans s1 (dans le meme ordre)
#include <iostream>
#include <string>
using namespace std;

bool recherche(string s1, string s2)
{
    size_t pos = 0;

    for (size_t i = 0; i < s2.size(); i++)
    {
        // on cherche la lettre a partir de pos
        size_t p = s1.find(s2[i], pos);

        if (p == string::npos)
            return false;

        // la prochaine lettre doit etre apres celle la
        pos = p + 1;
    }

    return true;
}

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
