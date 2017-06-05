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

typedef vector<long long> IntArray;

void solve();

int main(int argc, char **argv)
{
    int T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= 1);
    assert(T <= 8);

    for (int i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);
        solve();
    }

    return 0;
}

/***************************************************************************/

inline void solve() {

    long long N;
    cin >> N;
    D("N=" << N << endl);
    assert(N >= 1);
    assert(N <= 100000);

    if (N == 1) {
        long long v;
        cin >> v;
        D("single-dish " << v << endl);
        cout << v << endl;
        return;
    }

    // load and sum
    long long s = 0;
    vector<long long> A(N);
    IntArray::iterator it = A.begin();
    while (N--) {
        long long v;
        cin >> v;
        assert(v >= -100000000);
        assert(v <=  100000000);
        *it++ = v;
        s += v;
    }

    // sort increasing
    std::sort(A.begin(), A.end());
    D("s=" << s << "\tA=" << A << endl);

    // first max is "eat one by one"
    long long m = s;

    // search max by splitting single eaten and grouped eaten
    long long p = 0;
    long long b = 0;

    IntArray::const_reverse_iterator rit;
    for (rit=A.rbegin(); rit != A.rend(); rit++) {
        const long long &v = *rit;
        s -= v;
        p += v;
        b++;

        long long total = p * b + s;
        D("cur=" << *rit << "\ts=" << s << "\tp=" << p << "\tb=" << b << "\tt=" << total << endl);

        if (total > m) {
            m = total;
            D("new_max=" << m << endl);
        }
    }

    cout << m << endl;
}
