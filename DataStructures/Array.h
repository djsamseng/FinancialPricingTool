#ifndef ARRAY_h
#define ARRAY_h

#include "ArrayStructure.h"

template <class I, class V, class C=ArrayStructure<V> >
class Array
{
protected:
	C m_structure;			// The array structure
	I m_start;				// The start index

public:
	// Constructors & destructor
	Array() : m_structure(), m_start(0) {}
    Array(I size) : m_structure(size), m_start(0) {}
    Array(I size, const V& value);
    Array(const Array<I, V, C>& source);
    virtual ~Array() {}

	// Selectors
	I minIndex() const { return m_start; }
    I maxIndex() const { return m_start + size() - 1; }
    I size() const { return m_structure.size(); }
    I start() const { return m_start; }

    //Modifiers
    void pushBack(const V& value) { this->m_structure.pushBack(value); }
    void popBack() { this->m_structure.popBack(); }
    void setStart(const I& index) { m_start = index; }

	// Operators
	virtual V& operator[](I index);
    virtual const V& operator[](I index) const;

	Array<I, V, C>& operator=(const Array<I, V, C>& source);
};

template <class I, class V, class C>
Array<I, V, C>::Array(I size, const V& value) { 
	m_structure = C(size_t(size));
	m_start = 0;
    for (I i = minIndex(); i <= maxIndex(); i++) {
        (*this)[i] = value;
    }
}

template <class I, class V, class C>
Array<I, V, C>::Array(const Array<I, V, C>& source) {
	m_structure = source.m_structure;
	m_start = source.m_start;
}

// Operators
template <class I, class V, class C>
V& Array<I, V, C>::operator[](I index) {
	return m_structure[index - m_start];
}

template <class I, class V, class C>
const V& Array<I, V, C>::operator[](I index) const {
	return m_structure[index - m_start];
}

template <class I, class V, class C>
Array<I, V, C>& Array<I, V, C>::operator=(const Array<I, V, C>& source) {
	if (this == &source) {
        return *this;
    }

	m_structure = source.m_structure;
	m_start = source.m_start;
	
	return *this;
}


#endif
