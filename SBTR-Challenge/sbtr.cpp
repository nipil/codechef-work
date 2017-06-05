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

typedef vector<int> IntArray;

template <typename T>
void read_integers(int len, vector<T>& data)
{
    for (int i=0; i<len; i++) {
        T v;
        cin >> v;
        assert(v >= 1);
        assert(v <= 1000000000);
        data[i] = v;
    }
    assert(len == data.size());
}

int main(int argc, char **argv)
{
    int n, m;
    cin >> n >> m;
    D("n=" << n << "\tm=" << m << endl);
    assert(n >= 1);
    assert(n <= 10000);
    assert(m >= n -1);
    assert(m <= 50000);


    IntArray costs(n);
    read_integers(n, costs);
    D("costs" << endl << costs << endl);

    IntArray edges(m);
    read_integers(m, edges);
    D("edges" << endl << edges << endl);



    // dumb solution: destroy everything
    cout << n << endl;
    for (int i=1; i <= n; i++) {
        if (i != 1) {
            cout << " ";
        }
        cout << i;
    }
    cout << endl;

    return 0;
}
