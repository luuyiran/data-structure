// 双向链表，带迭代器、简单空间配置器

#ifndef __LW_LIST__
#define __LW_LIST__
// 所需头文件包含到cpp中，此处省略，详见main.cpp
#include <initializer_list>

// 空间配置器
template <typename T>
struct _lstAlloc {
    static inline T *allocate(size_t cnt) {
        return (T *)::operator new(cnt * sizeof(T));
    }
    static inline void deallocate(T *ptr) { delete (ptr); }
    static inline void construct(T *ptr, const T &e) { new (ptr) T(e); }
    static inline void destruct(T *ptr) { ptr->~T(); }
};
// 节点定义
struct _listNodeBase {
    _listNodeBase   *m_prev;
    _listNodeBase   *m_next;
    _listNodeBase(_listNodeBase *pr = nullptr, _listNodeBase *nxt = nullptr) 
        : m_prev(pr), m_next(nxt) {}
};

template <typename _Tp>
struct _listNode : public _listNodeBase {
    _Tp          *m_data;
    _listNode(const _Tp *_d = nullptr, _listNodeBase *_p = nullptr, _listNodeBase *_n = nullptr)
      : _listNodeBase(_p, _n), m_data(_d) {}
};

// 迭代器 用三个参数是为了方便 iterator 、 const_iterator
template<typename _Tp, typename _Ref, typename _Ptr>
struct _listIterator {
    typedef _Ptr                pointer;
    typedef _Ref                reference;
    typedef _listIterator<_Tp,_Ref,_Ptr>             _Self;
    typedef _listIterator<_Tp,_Tp&,_Tp*>             iterator;
    typedef _listIterator<_Tp,const _Tp&,const _Tp*> const_iterator;

    typedef _listNodeBase       _baseNode;
    typedef _listNode<_Tp>      _Node;

    _baseNode *m_current;

    _listIterator() {}
    _listIterator(_baseNode* __x) : m_current(__x) {}
    _listIterator(const iterator& __x) : m_current(__x.m_current) {}

    reference operator*() const { return (*((_Node *)m_current)->m_data); }
    pointer operator->() const { return &(operator*()); }

    _Self& operator++() { 
        m_current = m_current->m_next;
        return *this;
    }
    _Self operator++(int) { 
        _Self __tmp = *this;
        ++(*this);
        return __tmp;
    }

    _Self& operator--() { 
        m_current = m_current->m_prev;
        return *this;
    }
    _Self operator--(int) { 
        _Self __tmp = *this;
        --(*this);
        return __tmp;
    }
    bool operator==(const const_iterator & __x) const {
        return m_current == __x.m_current;
    }
    bool operator!=(const const_iterator & __x) const {
        return m_current != __x.m_current;
    }
};


template <typename _Tp, typename _Alloc = _lstAlloc<_Tp>>
class List {
public:
    typedef _Tp                 value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;

    typedef size_t              size_type;

    typedef _listNodeBase       _baseNode;
    typedef _listNode<_Tp>      _Node;

    typedef _Alloc              allocator;

    typedef _listIterator<_Tp,_Tp&,_Tp*>             iterator;
    typedef _listIterator<_Tp,const _Tp&,const _Tp*> const_iterator;


    List() { init();}

    ~List() {
        clear();
        dropNode(m_end);
    }

    List(const List<_Tp,_Alloc> &rhs) {
        init();
        *this = rhs;
    }

    // 列表初始化
    List(std::initializer_list<_Tp> __list) {
        init();
        for (auto &i : __list)
            push_back(i);
    }

    template <class _InputIterator>
    List( _InputIterator __first, _InputIterator __last) {
        init();
        while (__first != __last)
            push_back(*__first++);
    }

    const List &operator=(const List<_Tp,_Alloc> &rhs) {
        if (this == &rhs) return *this;
        clear();
        for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back(*itr);
        return *this;
    }

    iterator begin() {return m_end->m_next;}
    const_iterator begin() const {return m_end->m_next;}

    iterator end() {return m_end;}
    const_iterator end() const {return m_end;}

    bool empty() const {return m_end->m_next == m_end;}
    void clear() { while (!empty()) pop_front();}
    // 在for循环遍历中尽量不用这个判断迭代结束
    size_type size() const {  
        size_type __size = 0;
        for (const_iterator __pos = begin(); __pos != end(); ++__pos, ++__size);
        return __size; 
    }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *--end(); }
    const_reference back() const { return *--end(); }
    void push_front(const _Tp &__x) { insert(begin(), __x); }
    void push_back(const _Tp &__x) { insert(end(), __x); }
    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    // Insert __x at __position.
    iterator insert(iterator __position, const _Tp &__x) {
        _Node *__tmp = createNode(__x);
        __tmp->m_prev = __position.m_current->m_prev;
        __tmp->m_next = __position.m_current;
        __position.m_current->m_prev->m_next = __tmp;
        __position.m_current->m_prev = __tmp;
        return __tmp;
    }


    // Erase item at itr.
    iterator erase(iterator __position) {
        _baseNode *__next_node = __position.m_current->m_next;
        _baseNode *__prev_node = __position.m_current->m_prev;
        _Node *__del = (_Node *)__position.m_current;

        __prev_node->m_next = __next_node;
        __next_node->m_prev = __prev_node;

        destroyNode(__del);

        return __next_node;
    }

    iterator erase(iterator __start, iterator __end) {
        for(iterator __pos = __start; __pos != __end; )
            __pos = erase(__pos);
        return __end;
    }


    // 升序合并
    void merge(List &__x) {
        iterator __first1 = begin();
        iterator __last1 = end();
        iterator __first2 = __x.begin();
        iterator __last2 = __x.end();
        while (__first1 != __last1 && __first2 != __last2)
            if (*__first2 < *__first1) {
                iterator __j = __first2;
                ++__j;
                transfer(__first1, __first2, __j);
                __first2 = __j;
            } else
                ++__first1;
        if (__first2 != __last2) transfer(__last1, __first2, __last2);
    }

    void reverse() {
        _baseNode *__tmp = nullptr;
        _baseNode *__start = m_end->m_next;
        _baseNode *__pos = __start;

        do {
            // swap 
            __tmp = __pos->m_next;
            __pos->m_next = __pos->m_prev;
            __pos->m_prev = __tmp;
            // next node
            __pos = __tmp;
        } while (__pos != __start);
    }

    // 分治排序
    List &sort() {
        // 回溯条件
        if (size() <= 1) return *this;
        List l2;
        _baseNode *__slow = m_end->m_next;
        _baseNode *__fast = __slow;
        // 偶数从中间砍断，奇数前面多一个点
        while (__fast->m_next != m_end && __fast->m_next->m_next != m_end) {
            __slow = __slow->m_next;
            __fast = __fast->m_next->m_next;
        }

        transfer(l2.begin(), iterator(__slow->m_next), iterator(m_end));
        sort();
        merge(l2.sort());
        return *this;
    }


    void splice(iterator __position, List& __x) {
        if (!__x.empty()) 
        this->transfer(__position, __x.begin(), __x.end());
    }
    void splice(iterator __position, List&, iterator __i) {
        iterator __j = __i;
        ++__j;
        // 要插入的节点与 pos 上的是同一节点，或是 pos 上的前一个节点
        if (__position == __i || __position == __j) return;
        this->transfer(__position, __i, __j);
    }
    void splice(iterator __position, List&, iterator __first, iterator __last) {
        if (__first != __last) 
        this->transfer(__position, __first, __last);
    }

private:

    // 把前闭后开区间 [first, last) 接到__pos之前的位置
    // 插入前：
    // ... <--> __fir_pre <--> 【 __fir <--> ... <--> __lat_pre 】 <--> __last <--> ...   
    // ... <--> __pos_pre <--> 【插入位置】 __pos <--> __pos_next <--> ...
    // 插入后：
    // ... <--> __fir_pre <--> 【】 __last <--> ...   
    // ... <--> __pos_pre <--> 【 __fir --> ... <--> __lat_pre 】<--> __pos <--> __pos_next <--> ...
    void transfer(iterator __position, iterator __first, iterator __last) {
        if (__first == __last) return;      // insert empty
        if (__position == __last) return;   // [first, last) already lie befor __pos

        // Remove [first, last) from its old position.
        __last.m_current->m_prev->m_next = __position.m_current;
        __first.m_current->m_prev->m_next = __last.m_current;
        __position.m_current->m_prev->m_next = __first.m_current;

        // Splice [first, last) into its new position.
        _baseNode *__pos_pre = __position.m_current->m_prev;
        __position.m_current->m_prev = __last.m_current->m_prev;
        __last.m_current->m_prev = __first.m_current->m_prev;
        __first.m_current->m_prev = __pos_pre;
    }

    // 分配节点的内存，即分配 3 个指针的空间
    typedef _lstAlloc<_Node>  nodeAlloc;
    _Node *getNode() {
        return nodeAlloc::allocate(1);
    }

    void dropNode(_Node *ptr) {
        nodeAlloc::deallocate(ptr);
    }

    // 除分配 3 个指针空间外，分配 m_data 指向的内存
    _Node *createNode(const _Tp &__x) {
        _Node *__tmp = getNode();
        __tmp->m_data = allocator::allocate(1);
        allocator::construct(__tmp->m_data, __x);
        return __tmp;
    }

    void destroyNode(_Node *ptr) {
        allocator::destruct(ptr->m_data);   // 析构对象 _Tp
        allocator::deallocate(ptr->m_data); // 释放 _Tp 对象内存
        dropNode(ptr);      // 释放指针的内存
    }

    void init() {
        m_end = getNode();
        m_end->m_prev = m_end;
        m_end->m_next = m_end;
    }

private:
    // 通过基类的 2 个指针即可标明链表的头和尾
    _Node        *m_end;
};

#endif // !__LW_LIST__
