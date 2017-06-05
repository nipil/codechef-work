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



typedef vector<long long> IntArray;

void solve();

inline void read_ll(long long len, IntArray& data) {
    for (long long i=0; i<len; i++) {
        long long v;
        cin >> v;
        assert(v >= -100000000);
        assert(v <=  100000000);
        data[i] = v;
    }
    assert(len == data.size());
}

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

    IntArray A(N);
    read_ll(N, A);
    std::sort(A.begin(), A.end());
    D("A=" << A << endl);

    long long t = 0;

    long long s = 0;
    long long h = 0;

    long long v;
    while (A.size()) {
        v = A.back();
        D("v=" << v << endl);
        A.pop_back();
        if (v >= 0) {
            h += v;
            s++;
            D("STORE: happiness=" << h << " size=" << s << endl);
        } else {
            if (s > 0) {
                t += (h * s);
                D("DUMP: happiness=" << h << " size=" << s << " sub_total=" << t << endl);
            }
            h = v;
            s = 1;
        }
    }
    if (s > 0) {
        t += (h * s);
        D("DUMP: happiness=" << h << " size=" << s << " sub_total=" << t << endl);
    }

    cout << t << endl;
}
