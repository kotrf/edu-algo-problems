#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void stripSmiles(string &str)
{
    size_t posWr = 0;
    size_t posRd = 0;
    size_t smileBegin = -1, smileEnd = 0;

    while (posRd < str.size())
    {
        posRd = str.find(":-", posRd);

        if (posRd == string::npos)
        {
            while (smileEnd != str.size())
                str[posWr++] = str[smileEnd++];
            break;
        }

        while (smileEnd != posRd)
            str[posWr++] = str[smileEnd++];

        smileBegin = posRd; // next smile
        posRd = smileBegin + 2;

        if (posRd < str.size())
        {
            auto smileType = str[posRd];
            if (smileType == '(' || smileType == ')')
            {
                ++posRd;
                while (posRd < str.size() && str[posRd] == smileType)
                    ++posRd;
                smileEnd = posRd;
            }
        }
    }

    str.resize(posWr);
}

vector<string> testStrings = {
    "012:-)67:-((CDE",
    ":-)67:-((CDE",
    ":-))",
    "aaa",
    ":--)"};

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

    // string longStr(1000, 'a');      // 6 us
    // string longStr(10000, 'a');     // 64 us
    // string longStr(100000, 'a');    // 496 us
    // string longStr(1000000, 'a');   // 4548 us
    string longStr(10000000, 'a');  // 45812 us

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
