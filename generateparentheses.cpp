#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    void genParens(string str, int n, int open, int close, vector<string> &res) {
        if (str.size() == 2*n) {
            res.push_back(str);
        }
        if (open < n)
            genParens(str+'(', n, open+1, close, res);
        if (close < open)
            genParens(str+')', n, open, close+1, res);
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;
        genParens(string(), n, 0, 0, res);
        return res;
    }
};

int main()
{
    Solution sol;
    auto res = sol.generateParenthesis(3);

    for (auto const item: res)
        cout << "  " << item << endl;

    return 0;
}