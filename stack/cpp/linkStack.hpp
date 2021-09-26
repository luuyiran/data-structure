#ifndef _CXX_LINK_STACK_
#define _CXX_LINK_STACK_

template <typename T>
class LinkStack {
    struct ListNode {
        T data;
        ListNode* next;
        ListNode() : next(nullptr) {}
        ListNode(T &val, ListNode *ptr) : data(val), next(ptr) {}
    };
    ListNode *head;

public:
    LinkStack() : head(nullptr) {}
    ~LinkStack() {
        while (head) {
            ListNode *del = head;
            head = head->next;
            delete del;
        }
    }

    void push(T a) {
        head = new ListNode(a, head);
    }

    void pop() {
        if (empty()) return;
        ListNode *del = head;
        head = head->next;
        delete del;
    }

    T top() { 
        if (empty()) return T(0);
        return head->data; 
    }

    bool empty() { 
        return nullptr == head; 
    }
};

#endif
