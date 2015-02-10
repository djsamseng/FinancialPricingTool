#ifndef NUMERIC_ARRAY_H
#define NUMERIC_ARRAY_H

#include "Array.h"

template <class I, class V, class C=ArrayStructure<V> >
class NumericArray: public Array<I, V, C> {
private:
public:
	// Constructors & destructor
	NumericArray() : Array<I, V, C>() {}
    NumericArray(I size) : Array<I, V, C>(size) {}
	NumericArray(I size, const V& value) : Array<I, V, C>(size, value) {}
    NumericArray(const NumericArray<I, V, C>& source) : Array<I, V, C>(source) {}
    NumericArray(const Array<I, V, C>& source) : Array<I, V, C>(source) {}
    virtual ~NumericArray() {}

	// Operators
	NumericArray<I, V, C>& operator=(const NumericArray<I, V, C>& source);

	NumericArray<I, V, C> operator-() const;		// Unary minus

	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator+(const NumericArray<I, V, C>& v,const V& a);	// Add v to every element
	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator+(const V& a, const NumericArray<I, V, C>& v);

	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator-(const NumericArray<I, V, C>& v, const V& a);	// Subtract v from every element
	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator-(const V& a, const NumericArray<I, V, C>& v);

	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator*(const NumericArray<I, V, C>& v, const V& a);	// Multiply every element by v
	template <class I1, class V1, class C1>
	friend NumericArray<I, V, C> operator*(const V& a, const NumericArray<I, V, C>& v);

	NumericArray<I, V, C> operator/(const V& a) const;	// Divide every element by a
	
	NumericArray<I, V, C> operator+(const NumericArray<I, V, C>& v) const;	// Add the elements
	NumericArray<I, V, C> operator-(const NumericArray<I, V, C>& v) const;	// Subtract the elements
	NumericArray<I, V, C> operator*(const NumericArray<I, V, C>& v) const;	// Multiply the elements
	NumericArray<I, V, C> operator/(const NumericArray<I, V, C>& v) const;	// Divide the elements

	NumericArray<I, V, C>& operator+=(const V& v);	// Add v to every element
	NumericArray<I, V, C>& operator-=(const V& v);	// Subtract v from every element
	NumericArray<I, V, C>& operator*=(const V& v);	// Multiply every element by v
	NumericArray<I, V, C>& operator/=(const V& v);	// Divide every element by v

	NumericArray<I, V, C>& operator+=(const NumericArray<I, V, C>& v);// Add the elements
	NumericArray<I, V, C>& operator-=(const NumericArray<I, V, C>& v);// Subtract the elements
	NumericArray<I, V, C>& operator*=(const NumericArray<I, V, C>& v);// Multiply the elements
};


template <class V, class I> void scale(NumericArray<V,I>& v, const V& a); // v * a
template <class V, class I> void scale(const V& a, NumericArray<V,I>& v); // a * v

template <class V, class I> void add(NumericArray<V,I>& v, const V& a); // v + a
template <class V, class I> void add(const V& a, NumericArray<V,I>& v); // a + v

template <class V, class I> void 
			scaleAndOffset(NumericArray<V,I>& v, const V& a, const V& b); // (a * v) + b	

template <class V, class I> void subtract(NumericArray<V,I>& v, const V& a); // v - a
template <class V, class I> void subtract(const V& a, NumericArray<V,I>& v); // a - v

template <class V, class I> void divide(NumericArray<V,I>& v, const V& a); // v / a

template <class V, class I> void toggleSign(NumericArray<V,I>& v); // -v (unary minus)


template <class V, class I> void assign(NumericArray<V,I>& v, const V& RHS); // All elements = RHS




// ------- IMPLEMENTATION --------

// Operators
template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator=(const NumericArray<I, V, C>& source) {
	// Exit if same object
	if (this == &source) {
       return *this;
    }

	// Call baseclass assignment
	Array<I, V, C>::operator = (source);

	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C> NumericArray<I, V, C>::operator-() const { // Unary minus
	NumericArray<I, V, C> result(this->size());

	// Copy all elements negative
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
        result[i] = - (*this)[i];
    }
	// Return result
	return result;
}

template <class I, class V, class C>
NumericArray<I, V, C> operator+(const NumericArray<I, V, C>& v, const V& a) { // Add v to every element
	NumericArray<I, V, C> result(v.size());

	// Copy all elements + v
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		result[i] = v[i] + a;
    }
	// Return result
	return result;
}


template <class I, class V, class C>
NumericArray<I, V, C> operator+(const V& a, const NumericArray<I, V, C>& v) {
	return v + a;
}

template <class I, class V, class C>
NumericArray<I, V, C> operator*(const NumericArray<I, V, C>& v, const V& a) { // Multiply to every element by a
	NumericArray<I, V, C> result(v.size());

	// Copy all elements + v
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		result[i] = v[i] * a;
    }
	// Return result
	return result;
}

template <class I, class V, class C>
NumericArray<I, V, C> operator*(const V& a, const NumericArray<I, V, C>& v)
{
	return v * a;
}


template <class I, class V, class C>
NumericArray<I, V, C> operator-(const NumericArray<I, V, C>& v, const V& a) { // Subtract v from every element
	NumericArray<I, V, C> result(v.size());

	// Copy all elements - v
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		result[i] = v[i] - a;
    }
	// Return result
	return result;
}

template <class I, class V, class C>
NumericArray<I, V, C> operator-(const V& a, const NumericArray<I, V, C>& v) {
	NumericArray<I, V, C> result(v.size());

	// Copy all elements - v
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		result[i] = a - v[i];
    }
	// Return result
	return result;

}

template <class I, class V, class C>
NumericArray<I, V, C> NumericArray<I, V, C>::operator/(const V& a) const { // Add v to every element
	NumericArray<I, V, C> result(this->size());

	// Copy all elements + v
	for (I i = this->minIndex(); i <= this->maxIndex(); i++) {
		result[i] = (*this)[i] / a;
    }
	// Return result
	return result;
}


template <class I, class V, class C>
NumericArray<I, V, C> NumericArray<I, V, C>::operator+(const NumericArray<I, V, C>& v) const { // Add the elements
	NumericArray<I, V, C> result(this->size());

	// Result[x]=Source[x]+v[x];
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
        result[i] = (*this)[i] + v[i];
    }
	// Return result
	return result;
}

template <class I, class V, class C>
NumericArray<I, V, C> NumericArray<I, V, C>::operator - (const NumericArray<I, V, C>& v) const { // Subtract the elements
	NumericArray<I, V, C> result(this->size());

	// Result[x]=Source[x]-v[x];
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
        result[i] = (*this)[i] - v[i];
    }
	// Return result
	return result;
}


template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator += (const V& v) { // Add v to every element
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] + v;
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator -= (const V& v) { // Subtract v from every element
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] - v;
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator *= (const V& v) { // Multiply every element by v
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] * v;
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator /= (const V& v) { // Divide every element by v
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] / v;
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator += (const NumericArray<I, V, C>& v) { // Add the elements
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] + v[i];
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator -= (const NumericArray<I, V, C>& v) { // Subtract the elements
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] - v[i];
    }
	return *this;
}

template <class I, class V, class C>
NumericArray<I, V, C>& NumericArray<I, V, C>::operator *= (const NumericArray<I, V, C>& v) { // Multiply the elements
	for (I i=this->minIndex(); i<=this->maxIndex(); i++) {
		(*this)[i] = (*this)[i] * v[i];
    }
	return *this;
}







template <class V, class I> void scale(NumericArray<V,I>& v, const V& a) { // v * a
	for (I i = v.minIndex(); i <= v.maxIndex(); i++)	{
		v[i] *= a;
	}
}

template <class V, class I> void scale(const V& a, NumericArray<V,I>& v) { // a * v
	scale(v, a);
}

template <class V, class I> void add(NumericArray<V,I>& v, const V& a) { // v + a
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] += a;
	}
}

template <class V, class I> void add(const V& a, NumericArray<V,I>& v) { // a + v
	add(v, a);
}

template <class V, class I> void scaleAndOffset(NumericArray<V,I>& v, const V& a, const V& b) { // (a * v) + b	
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] *= a;
		v[i] += b;
	}
}

template <class V, class I> void subtract(NumericArray<V,I>& v, const V& a) { // v - a

	for (I i = v.minIndex(); i <= v.maxIndex(); i++)
	{
		v[i] -= a;
	}
}

template <class V, class I> void subtract(const V& a, NumericArray<V,I>& v) { // a - v
	// This operation is not commutative, so redo the for loop
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] = a - v[i];
	}
}

template <class V, class I> void divide(NumericArray<V,I>& v, const V& a) { // v / a
	for (I i= v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] /= a;
    }
}

template <class V, class I> void toggleSign(NumericArray<V,I>& v) { // -v (unary minus)
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] = -v[i];
	}
}

template <class V, class I> void assign(NumericArray<V,I>& v, const V& RHS) { // All elements = RHS
	for (I i = v.minIndex(); i <= v.maxIndex(); i++) {
		v[i] = RHS;
	}
}



#endif
