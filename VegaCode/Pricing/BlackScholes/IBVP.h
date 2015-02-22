#ifndef IBVP_H
#define IBVP_H

template <class T>
class IBVP {
    public:
        //x is the underlying price, t is time
        IBVP(int minT, int maxT, int minX, int maxX) : _min_t(minT), _max_t(maxT), _min_x(minX), _max_x(maxX) {}
        virtual const T diffusion(const T& t, const T& x) const = 0;
        virtual const T convection(const T& t, const T& x) const = 0;
        virtual T zeroTerm(const T& t, const T& x) const = 0;
        virtual const T rightHandSide(const T& t, const T& x) const = 0;
        virtual const T rightBC(const T& t, const T& x) const = 0;
        virtual const T leftBC(const T& t, const T& x) const = 0;
        virtual const T initialC(const T& x) const = 0;
        
        const int minT() const { return _min_t; }
        const int maxT() const { return _max_t; }
        const int minX() const { return _min_x; }
        const int maxX() const { return _max_x; }
    private:
        int _min_t;
        int _max_t;
        int _min_x;
        int _max_x;

};

#endif
