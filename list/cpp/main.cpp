#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "sList.hpp"
#include "List.hpp"

static const int TEST_ROUND = 3;
static const int LIST_SIZE = 16;
static const int MAX_VALUE = 100;

// Input format [0,1,2,...,99]
static string generateInput() {
    ostringstream out;
    for (int i = 0; i < LIST_SIZE; i++) {
        if (i) out << ",";
        out << rand() % MAX_VALUE;
    }
    return "[" + out.str() + "]";
}



// 测试简单单链表
static void testSingleList() {
    cout << "\n============== test simple singly-linked list ===============\n";
    srand(time(NULL));
    string input;
    ListNode* head = nullptr;
    for (int i = 0; i < TEST_ROUND; i++) {
        input = generateInput();
        cout << input << endl;

        head = stringToListNode(input);
        printList(head);

        head = reverseList(head);
        printList(head);

        head = sortList(head);
        printList(head);

        destroyList(head);
    }
}




// test List initialize
static void testInit() {
    cout << "\n============== initialization of the list ===============\n";
    List<int> lst0;
    for (int i = 0; i < LIST_SIZE; i++)
        lst0.push_back(i);  // test push_back
    lst0.reverse();
    printf("l0 size: %ld\n", lst0.size());
    for (List<int>::const_iterator i = lst0.begin(); i != lst0.end(); ++i) {
        //*i += 60;    // test const_iterator
        printf("%d ", *i);
    }
    printf("\n");
    lst0.reverse();
    for (List<int>::iterator i = lst0.begin(); i != lst0.end(); ++i) {
        *i += 60;    // test iterator
        printf("%d ", *i);
    }
    printf("\n");
    lst0.reverse();
    for (auto i = lst0.begin(); i != lst0.end(); ++i) {
        *i -= 60;    // test auto
        printf("%d ", *i);
    }
    printf("\n");
    lst0.reverse();
    List<int> lst1(lst0);

    while (!lst0.empty()) {
        printf("poped %d,  left %ld\n", *lst0.begin(), lst0.size() - 1);
        lst0.pop_front();
    }


    
    List<int> lst2 = {6,5,4,3,2,1};  // 列表初始化
    printf("l2 size: %ld\n", lst2.size());
    for (auto num : lst2) printf("%d ", num);
    printf("\n");

    lst2 = lst1;
    printf("l2 size: %ld\n", lst2.size());
    for (auto num : lst2) printf("%d ", num);
    printf("\n");

    int nums[6] = {6,5,4,3,2,1};
    List<int> lst3(nums, nums+6);
    for (auto num : lst3) printf("%d ", num);
    printf("\n");
}

// 转移某个链表的全部元素 到另一个链表上
static void testSplice1() {
    cout << "\n============== Transfer all the elements of the list ===============\n";
    List<int> l1 = { 1, 2, 3 };
    List<int> l2 = { 4, 5 };
    List<int> l3 = { 6, 7, 8 };
  
    // 把 l2 的节点全部挂在l1首部，l2变为空
    l1.splice(l1.begin(), l2);
  
    // l1 输出 4 5 1 2 3 
    cout << "List l1 after splice operation" << endl;
    for (auto x : l1)
        cout << x << " ";
  
    // l1 的全部节点转移到 l3，l1 变为空
    l3.splice(l3.end(), l1);
  
    // l3 输出 6 7 8 4 5 1 2 3
    cout << "\nlist l3 after splice operation" << endl;
    for (auto x : l3)
        cout << x << " ";
    
    // l1, l2 为空
    for (auto x : l1) cout << x;
    for (auto x : l2) cout << x; 
    cout << endl;
}

// 转移单个元素
static void testSplice2() {
    cout << "\n============== Transfer a single element ===============\n";
    List<int> l1 = { 1, 2, 3 };
    List<int> l2 = { 4, 5 };
    List<int>::iterator it;
  
    // Iterator pointing to 4
    it = l2.begin();
  
    // transfer 4 at the end of l1
    l1.splice(l1.end(), l2, it);
    cout << "List l1 after splice operation " << endl;
    for (auto x : l1)
        cout << x << " "; // l1 打印 1 2 3 4
    // 把 3 转移到头部
    it = --l1.end();  // 指向4
    --it;    // 指向3
    l1.splice(l1.begin(), l1, it);
    cout << "\nList l1 after splice operation" << endl;
    for (auto x : l1)
        cout << x << " "; // l1 打印 3 1 2 4

    cout << "\nList l2 after splice operation " << endl;
    for (auto x : l2)
        cout << x << " ";  // 5

    cout << endl;
}

// 转移指定区间上的元素
static void testSplice3() {
    cout << "\n============== Transfer a range of elements ===============\n";
    // initializing lists and iterator
    List<int> l1 = { 1, 2, 3, 4, 5 };
    List<int> l2 = { 6, 7, 8 };
    List<int>::iterator it;

    it = ++l1.begin();
    ++it;
    // 把 l1 的 3 4 5 转移到 l2
    l2.splice(l2.begin(), l1, it, l1.end());
  
    cout << "l2: ";
    for (auto x : l2) cout << x << " ";
    cout << endl;

    cout << "l1: ";
    for (auto x : l1) cout << x << " ";
    cout << endl;
}

static void randomSort(List<int> &l1) {
    l1.clear();
    for (int i = 0; i < LIST_SIZE; i++)
        l1.push_back(rand() % MAX_VALUE);
    cout << "l1  : ";
    for (auto x : l1) cout << x << " ";
    cout << endl;

    l1.sort();
    cout << "sort: ";
    for (auto x : l1) cout << x << " ";
    cout << endl << endl;
}


static void testSort() {
    cout << "\n============== Sort List ===============\n";
    List<int> l1;
    srand(time(NULL));
    for (int i = 0; i < TEST_ROUND; i++) {
        randomSort(l1);
    }
}


// test class List<_Tp>
static void testList() {
    testInit();
    testSplice1();
    testSplice2();
    testSplice3();
    testSort();
}

int main() {
    testSingleList();
    testList();
    return 0;
}



