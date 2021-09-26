#ifndef __SINGLE_LINKED_LIST__
#define __SINGLE_LINKED_LIST__

// Definition for singly-linked list.

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* stringToListNode(string input);

void destroyList(ListNode *head);

void printList(ListNode* node);

ListNode *reverseList(ListNode *head);

ListNode* sortList(ListNode* head);

#endif // !__SINGLE_LINKED_LIST__
