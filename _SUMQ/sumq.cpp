#include <iostream>
#include <vector>
#include <algorithm>

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

typedef vector<unsigned long long> IntArray;

void solve();

inline void read_ull(unsigned long long len, IntArray& data) {
    for (unsigned long long i=0; i<len; i++) {
        unsigned long long v;
        cin >> v;
        assert(v >= 1);
        assert(v <= 1000000000);
        data[i] = v;
    }
    assert(len == data.size());
}

int main(int argc, char **argv)
{
    unsigned long long T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= 1);
    assert(T <= 10);

    for (int i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);
        solve();
    }

    return 0;
}

/***************************************************************************/

inline void solve() {

    int p, q, r;
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

    read_ull(p, P);
    std::sort(P.begin(), P.end());
    D("P=" << P << endl);
    read_ull(q, Q);
    std::sort(Q.begin(), Q.end());
    D("Q=" << Q << endl);
    read_ull(r, R);
    std::sort(Q.begin(), Q.end());
    D("R=" << R << endl);

    IntArray::const_iterator it_x, it_y, it_z;

    unsigned long long total = 0;

    // f(x,y,z) = (X + Y) * (Y + Z)
    // optimization due to loop implementations :
    // f = (X + Y) * (Y + Z)
    // f = (X + Y) * Y + (X + Y) * Z
    // f = Y * Y + X * Y + (X + Y) * Z

    // y loop : Y * Y
    // x loop : X * Y and X + Y
    // z loop : XpY * Z

    for (it_y=Q.begin() ; it_y!=Q.end(); it_y++) {
        unsigned long long Y = *it_y;
        unsigned long long yty = Y * Y;
        unsigned long long y_st = yty;

        for (it_x=P.begin() ; it_x!=P.end(); it_x++) {
            unsigned long long X = *it_x;
            if (X > Y) {
                break;
            }

            unsigned long long xpy = Y + X;
            unsigned long long xty = X * Y;
            unsigned long long yx_st = yty + xty;

            for (it_z=R.begin() ; it_z!=R.end(); it_z++) {
                unsigned long long Z = *it_z;

                if (Z > Y) {
                    break;
                }

                unsigned long long ztxpy = Z * xpy;
                unsigned long long yxz_st = yx_st + ztxpy;

                D("{" << X << "," << Y << "," << Z << "} : " << yxz_st << endl);

                total += yxz_st;
            }
        }
    }

    total %= 1000000007ULL;
    cout << total << endl;
}
