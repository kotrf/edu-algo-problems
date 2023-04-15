#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> parentheses;

        for ( auto c: s) {
            switch(c)
            {
                case '(': parentheses.push(')'); break;
                case '[': parentheses.push(']'); break;
                case '{': parentheses.push('}'); break;
                case ')':
                case ']':
                case '}':
                    if (parentheses.empty())
                        return false;
                    if (parentheses.top() != c)
                        return false;
                    parentheses.pop();
                    break;
            }
        }

        return parentheses.empty();
    }
};

int main()
{
    Solution solution;
    cout << solution.isValid("()") << endl;
    return 0;
}
