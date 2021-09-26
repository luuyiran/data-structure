#ifndef _CXX_ARRAY_STACK_
#define _CXX_ARRAY_STACK_

template <typename T>
class ArrayStack {
    vector<T> buf;
public:
    void push(T a) {
        buf.push_back(a);
    };

    void pop() {
        if (empty()) return;
        buf.pop_back();
    };

    T top() {
        if (empty()) return T(0);
        return buf.back();
    };

    bool empty(){
        return buf.empty();
    }
};

#endif
