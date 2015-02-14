#ifndef ARRAY_STRUCTURE_H
#define ARRAY_STRUCTURE_H

#include <vector>

#include "StructureInterface.h"

template <class V>
class ArrayStructure : public StructureInterface<int, V>{
    protected:
	    std::vector<V> _vector;
        
    public:
        // Constructors & destructor
        ArrayStructure();										
        ArrayStructure(size_t size);									
        ArrayStructure(const ArrayStructure<V>& source);				
        virtual ~ArrayStructure() {}									

        // Selectors
        virtual size_t size() const { return _vector.size(); }
        //Modifiers
        virtual void pushBack(const V& value) { _vector.push_back(value); }
        virtual void popBack() { _vector.pop_back(); }
        // Operators
        V& operator[] (size_t index) { return _vector[index]; }							
        const V& operator[] (size_t index) const { return _vector[index]; }	

        ArrayStructure<V>& operator = (const ArrayStructure<V>& source);

        void print() const;
};



// Constructors & destructor
template <class V>
ArrayStructure<V>::ArrayStructure() : StructureInterface<int, V>() {
	_vector=std::vector<V>(0);
}

template <class V>
ArrayStructure<V>::ArrayStructure(size_t size) : StructureInterface<int, V>() {
	_vector=std::vector<V>(size);
}

template <class V>
ArrayStructure<V>::ArrayStructure(const ArrayStructure<V>& source) : StructureInterface<int, V>() { 
    // Copy constructor
	_vector=source._vector;
}

// Operators
template <class V>
ArrayStructure<V>& ArrayStructure<V>::operator=(const ArrayStructure<V>& source) {
	if (this == &source) {
        return *this;
    }
	_vector = source._vector;
	return *this;
}

#endif
