#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

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

static constexpr int smile0Pos = 3;
static constexpr int smile1Pos = -7;
const string smile0 = ":-)";
const string smile1 = ":-(((";

int main()
{
    for (auto str: testStrings)
    {
        cout << "Input: " << str << endl;
        stripSmiles(str);
        cout << "Output: " << str << endl;
    }

    cout << "Run time measurements\n";

    // string longStr(1000, 'a');      // 13 us
    // string longStr(10000, 'a');     // 127 us
    // string longStr(100000, 'a');    // 954 us
    // string longStr(1000000, 'a');   // 8886 us
    string longStr(10000000, 'a');  // 87188 us

    for (int n=0; n<smile0.size(); ++n)
        longStr[smile0Pos+n] = smile0[n];
    for (int n=0; n<smile1.size(); ++n)
        longStr[smile1Pos+n+longStr.size()] = smile1[n];


    unsigned long runTimeMs = 0;
    static constexpr int Runs = 100;

    for ( int runCnt=0; runCnt < Runs; ++runCnt)
    {
        auto start = high_resolution_clock::now();
        stripSmiles(longStr);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        runTimeMs += duration.count();
    }

    runTimeMs /= Runs;
    cout << "Duration: " << runTimeMs << endl;

    return 0;
}
