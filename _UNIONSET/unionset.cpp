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
#include <cstdio>

using namespace std;

template <typename T>
ostream &operator << (ostream &a, const vector<T> &b)
{
    return a;
}

void solve();

/***************************************************************************/

#define MAX_SET_LENGTH (2500)
#define SET_FLAG_DATA_SIZE (1 + MAX_SET_LENGTH >> 64)

int main(int argc, char **argv)
{
    int T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= 1);
    for (int i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);
        solve();
    }
    return 0;
}

void solve() {
    int n, k;
    cin >> n >> k;
    D("n=" << n << " k=" << k << endl);
    assert(n >= 1);
    assert(n <= MAX_SET_LENGTH);
    assert(k >= 1);
    assert(k <= MAX_SET_LENGTH);
}
