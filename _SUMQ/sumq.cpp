#include <iostream>
#include <vector>

#ifdef DEBUGBUILD
    #define D(x) do { std::cerr << x; } while (0)
    #undef NDEBUG
#else
    #define D(x)
    #define NDEBUG
#endif

#include <cassert>
#include <cmath>

using namespace std;

template <typename T>
ostream &operator << (ostream &a, const vector<T> &b)
{
    typename vector<T>::const_iterator it = b.begin();
    for (; it!=b.end(); it++) {
        D(*it << "\t");
    }
    return a;
}

/***************************************************************************/

#ifndef uint64
    typedef unsigned long long uint64;
#endif

typedef vector<uint64> IntArray;

uint64 solve();

void read_ints(uint64 len, IntArray& data) {
    for (uint64 i=0; i<len; i++) {
        uint64 v;
        cin >> v;
        data[i] = v;
    }
    assert(len == data.size());
}


int main(int argc, char **argv)
{
    uint64 T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= 1);
    assert(T <= 10);

    for (uint64 i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);

        uint64 p, q, r;
        cin >> p >> q >> r;
        D("p=" << p << " q=" << q << " r=" << r << endl);
        assert(p >= 1);
        assert(p <= 100000);
        assert(q >= 1);
        assert(q <= 100000);
        assert(r >= 1);
        assert(r <= 100000);

        IntArray P(p), Q(q), R(r);
        assert(p == P.capacity());
        assert(q == Q.capacity());
        assert(r == R.capacity());

        read_ints(p, P);
        D("P=" << P << endl);
        read_ints(q, Q);
        D("Q=" << Q << endl);
        read_ints(r, R);
        D("R=" << R << endl);
    }

    return 0;
}

