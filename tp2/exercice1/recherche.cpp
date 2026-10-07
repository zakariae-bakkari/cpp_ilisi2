#include "recherche.h"
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