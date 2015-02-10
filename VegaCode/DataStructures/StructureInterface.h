#ifndef STRUCTURE_INTERFACE_H
#define STRUCTURE_INTERFACE_H

#include <iostream>
#include <assert.h>

template <class I, class V>
class StructureInterface {
    public:
        StructureInterface() {}
        virtual void pushBack(const V& value);
        virtual void popBack();
        virtual void pushFront(const V& value);
        virtual void popFront();
        virtual void insert(const I& index, const V& value);
        virtual void removeAt(const I& index);
        virtual void remove(const V& value);
};

template <class I, class V>
void StructureInterface<I, V>::pushBack(const V& value) {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::popBack() {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::pushFront(const V& value) {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::popFront() {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::insert(const I& index, const V& value) {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::removeAt(const I& index) {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}
template <class I, class V>
void StructureInterface<I, V>::remove(const V& value) {
    std::cout << "Operation not supported by this data structure" << std::endl;
    assert(false);
}

#endif
