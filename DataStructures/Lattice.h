#ifndef LATTICE_H
#define LATTICE_H

#include "Array.h"
#include "NumericArray.h"
#include <assert.h>


enum LatticeType{
    BinomialLatticeType = 2,
    TrinomialLatticeType = 3,
    PentagonalLatticeType = 4,
};


template <class I, class V>
class Lattice {
    public:
        Lattice() : _lattice(), _latticeType(BinomialLatticeType) {}
        Lattice(const I& numRows);
        Lattice(const Lattice<I, V>& s);
        virtual ~Lattice() {}

        I minIndex() const { return _lattice.minIndex(); }
        I maxIndex() const { return _lattice.maxIndex(); }
        I size() const { return _lattice.size(); }

        Lattice<I, V>& operator=(const Lattice<I, V>& s);
        NumericArray<I, V>& operator[](const I& index) { return _lattice[index]; }
        const NumericArray<I, V>& operator[](const I& index) const { return _lattice[index]; }
        LatticeType latticeType() const { return _latticeType; }

        void print() const;
    private:
        Array<I, NumericArray<I,V> >_lattice;
        LatticeType _latticeType;
};

template <class I, class V>
Lattice<I, V>::Lattice(const I& numRows) {
    _latticeType = BinomialLatticeType;
    _lattice = Array<I, NumericArray<I, V> >(numRows);
    int nodesInLevel = 1;
    for (int i = _lattice.minIndex(); i <= _lattice.maxIndex(); i++) {
        _lattice[i] = NumericArray<I, V>(nodesInLevel);
        nodesInLevel += _latticeType - 1;
    }
}

template <class I, class V>
Lattice<I, V>::Lattice(const Lattice<I, V>& s) {
    assert(false);
}
template <class I, class V>
Lattice<I, V>& Lattice<I, V>::operator=(const Lattice<I, V>& s) {
    if (&s == this) {
        return *this;
    }
    _latticeType = s._latticeType;
    _lattice = s._lattice;
    return *this;
}

template <class I, class V>
void Lattice<I, V>::print() const {
    for (I i = _lattice.minIndex(); i <= _lattice.maxIndex(); i++) {
        for (I j = _lattice[i].minIndex(); j <= _lattice[i].maxIndex(); j++) {
            std::cout << _lattice[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
    
#endif
