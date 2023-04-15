#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;

        int digitsSum = l1->val + l2->val;
        if (digitsSum >= 10) {
            digitsSum -= 10;
            carry = 1;
        }

        ListNode *lSum = new ListNode(digitsSum);
        ListNode *lDigit = lSum;

        while ( l1->next && l2->next ) {
            l1 = l1->next;
            l2 = l2->next;

            digitsSum = l1->val + l2->val + carry;
            if (digitsSum < 10)
                carry = 0;
            else {
                carry = 1;
                digitsSum -= 10;
            }

            lDigit->next = new ListNode(digitsSum);
            lDigit = lDigit->next;
        }

        if (l1 || l2) {
            ListNode *l = l1->next ? l1->next : l2->next;

            while (l) {
                digitsSum = l->val + carry;
                if (digitsSum < 10)
                    carry = 0;
                else {
                    carry = 1;
                    digitsSum -= 10;
                }

                lDigit->next = new ListNode(digitsSum);
                lDigit = lDigit->next;
                l = l->next;
            }
        }

        if (carry)
            lDigit->next = new ListNode(carry);

        return lSum;
    }
};

void printListNode(string name, ListNode *l) {
    cout << name + "[ ";
    while (l) {
        cout << l->val << ' ';
        l = l->next;
    }
    cout << "]\n";
}

int main()
{
    ListNode *l1 = new ListNode(9);
    ListNode *l1Digit = l1;
    ListNode *l2 = new ListNode(9);
    ListNode *l2Digit = l2;

    for (int n=1; n<7; ++n) {
        l1Digit->next = new ListNode(9);
        l1Digit = l1Digit->next;
    }

    for (int n=1; n<4; ++n) {
        l2Digit->next = new ListNode(9);
        l2Digit = l2Digit->next;
    }

    printListNode("l1: ", l1);
    printListNode("l2: ", l2);

    Solution solution;
    ListNode *nodeSum = solution.addTwoNumbers(l1, l2);

    cout << "Sum: \n";
    while (nodeSum != nullptr) {
        cout << nodeSum->val << endl;
        nodeSum = nodeSum->next;
    }

    return 0;
}
