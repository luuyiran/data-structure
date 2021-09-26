#ifndef __LW_ARRAY_HPP__
#define __LW_ARRAY_HPP__
#include <stddef.h>
#include <initializer_list>
///////////////////////////////////////////////////////////////////////////////
template <typename _Tp>
class Array {
public:
    typedef _Tp               value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type*       iterator;   // vector的迭代器是普通指针
    typedef const value_type* const_iterator;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;
    typedef ptrdiff_t         difference_type;


    reference             operator [] (size_type i){return m_buffer[i];}
    const_reference       operator [] (size_type i) const{return m_buffer[i];}

    Array(size_type __count = 0) {
        m_size = __count;
        m_capacity = m_size + 64;
        m_buffer = new _Tp[m_capacity];
    }
    Array(const Array<_Tp> &__rhs)  : m_buffer(nullptr){ 
        *this = __rhs;
    }
    Array(std::initializer_list<_Tp> __list) : m_buffer(nullptr), m_size(0), m_capacity(0) {
        reserve(__list.size());
        for (auto &i : __list)
            push_back(i);
    }
    ~Array() { release();}

    const Array & operator=(const Array<_Tp> &__rhs) {
        if (this != &__rhs) {
            if (m_buffer) delete[] m_buffer;
            m_size = __rhs.size();
            m_capacity = __rhs.capacity();

            m_buffer = new _Tp[m_capacity];
            for (size_type k = 0; k < m_size; k++) m_buffer[k] = __rhs[k];
        }
        return *this;
    }

    void reserve(size_type __newCapacity) {
        if (__newCapacity < m_size) return;
        pointer oldArray = m_buffer;
        m_buffer = new _Tp[__newCapacity];
        for (size_type k = 0; k < m_size; k++) m_buffer[k] = oldArray[k];
        m_capacity = __newCapacity;
        if (oldArray) delete[] oldArray;
    }
    void push_back(const_reference __x) {
        if (m_size == m_capacity) reserve(2 * m_capacity + 1);
        m_buffer[m_size++] = __x;
    }
    void pop_back() {
        if (!m_size || nullptr == m_buffer) return;
        m_size--;
    }
    void clear() {release();}
    iterator begin() {return m_buffer; }
    iterator   end() {return  m_buffer + m_size; }
    pointer  data() {return m_buffer;}

    const_iterator begin() const {return m_buffer; }
    const_iterator   end() const {return  m_buffer + m_size; }
    const_reference front() const{return m_buffer[0];}
    const_reference  back() const{return m_buffer[m_size - 1];}
    const_pointer  data() const  {return m_buffer;}
    const_reference at(size_type index) const {return m_buffer[index];}

    size_type size() const      {return m_size;}
    size_type capacity() const  {return m_capacity;}

    bool empty() const {return m_size == 0;}
    void resize(size_type __x) {
        if (__x > m_capacity) reserve(__x * 2 + 1);
        m_size = __x;
    }
    
private:
    void release() {
        if (m_buffer)  delete[] m_buffer;
        m_buffer = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
private:
    pointer            m_buffer;
    size_type          m_size;
    size_type          m_capacity;
};

#endif
