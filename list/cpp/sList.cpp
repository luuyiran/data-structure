#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "sList.hpp"

static void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

static void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

static vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    // Input format [0,1,2,...,99]  ,valid index 1-size-2
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) 
        output.push_back(stoi(item));
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode dummy;
    ListNode* ptr = &dummy;
    for (int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    return dummy.next;
}

void destroyList(ListNode *head) {
    if (head) {
        destroyList(head->next);
        delete head;
    }
}

void printList(ListNode *node) {
    while (node && node->next) {
        cout << node->val << "->";
        node = node->next;
    }
    if (node)
        cout << node->val << endl;
    else
        cout << "Empty LinkedList" << endl;
}



ListNode *reverseList(ListNode *head) {
    if (NULL == head || NULL == head->next) return head;
    ListNode *p = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return p;
}

static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (NULL == l1) return l2;
    if (NULL == l2) return l1;

    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

ListNode* sortList(ListNode* head) {
    if (nullptr == head || nullptr == head->next) return head;
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* l2 = slow->next;
    ListNode* l1 = head;
    slow->next = nullptr;

    return mergeTwoLists(sortList(l1), sortList(l2));
}



