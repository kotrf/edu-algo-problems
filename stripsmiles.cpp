#include <iostream>
#include <vector>

using namespace std;

void stripSmiles(string &str)
{
    size_t rdPos = 0, wrPos = 0;

    while (rdPos < str.size())
    {
        if ( rdPos >= str.size() - 2
            || str[rdPos] != ':' || str[rdPos+1] != '-'
            || str[rdPos+2] != ')' && str[rdPos+2] != '(' )
                str[wrPos++] = str[rdPos++];
        else
        {
            rdPos += 2;
            auto smileType = str[rdPos++];
            while (rdPos < str.size() && str[rdPos] == smileType)
                ++rdPos;
        }
    }

    str.resize(wrPos);
}

vector<string> testStrings = {
    "012:-)67:-((CDE",
    ":-)67:-((CDE",
    ":-))",
    "aaa",
    ":--)"
};

int main()
{
    for (auto str: testStrings)
    {
        cout << "Input: " << str << endl;
        stripSmiles(str);
        cout << "Output: " << str << endl;
    }

    return 0;
}
