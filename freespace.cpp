#include <iostream>

using namespace std;

size_t getMostFreePosition(const string &str)
{
    size_t bestBegin = 0, bestEnd = 0;
    size_t bestLen = 0;
    size_t begin, end = -1;

    do
    {
        begin = str.find('0', end+1);
        if (begin == string::npos)
            break;
        end = str.find('1', begin+1);

        size_t len;
        if (end == string::npos)
        {
            len = str.size() - begin;
            end = str.size();
        }
        else
            len = end - begin;

        if (len > bestLen)
        {
            bestLen = len;
            bestBegin = begin;
            bestEnd = end;
        }

    } while( end < str.size());

    if ( bestBegin == 0 || bestBegin == string::npos)
        return bestBegin;
    if (bestEnd >= str.size())
        return bestEnd-1;

    return (bestBegin+bestEnd) / 2;
}

string pattern = "110001100000001111110000011111";
// string pattern = "11111000";
// string pattern = "";

int main()
{
    cout << "Pattern: " << pattern << endl;
    cout << "Answer: " << getMostFreePosition(pattern) << endl;
    return 0;
}