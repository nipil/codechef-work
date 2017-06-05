#include <iostream>
#include <vector>
#include <queue>
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

void solve();

template <typename T>
inline void read_integer(T& target, const T& minValue, const T& maxValue) {
    cin >> target;
    assert(target >= minValue);
    assert(target <= maxValue);
}

inline void do_tests(int minT, int maxT) {
    int T;
    read_integer(T, minT, maxT);
    for (int i=0; i<T; i++) {
        D("==== Test " << i + 1 << "/" << T << endl);
        solve();
    }
}

int main(int argc, char **argv)
{
    do_tests(1, 3);
    return 0;
}

/***************************************************************************/

typedef vector<int> IntArray;

inline void solve() {

    int N, Q;
    read_integer(N, 1, 100000);
    read_integer(Q, 1, 100000);
    D("N=" << N << "\tQ=" << Q << endl);

    IntArray A(N);
    for (int i=0; i<N; i++) {
        read_integer(A[i], 1, 100000);
    }
    D("A=" << A << endl);

    for (int i=0; i<Q; i++) {
        D("-- Sub-test " << i + 1 << "/" << Q << endl);

        int a, b, c, d;
        read_integer(a, 1, 100000);
        read_integer(b, 1, 100000);
        read_integer(c, 1, 100000);
        read_integer(d, 1, 100000);

        a--;
        b--;
        c--;
        d--;

        D("a=" << a << "\tb=" << b << "\tc=" << c << "\td=" << d << endl);

        int l = b - a;
        assert(l == d - c);
        l++;

        D("l=" << l << endl);

        // easy: same
        if (a == c) {
            cout << "YES" << endl;
            continue;
        }

        // easy: single
        if (a == b) {
            cout << "YES" << endl;
            continue;
        }


        // general case

        priority_queue<int> q_a, q_c;
        IntArray::const_iterator it_a, it_c;
        it_a = A.begin() + a;
        it_c = A.begin() + c;
        for (int i=0; i<l; i++) {
            q_a.push(*it_a++);
            q_c.push(*it_c++);
        }

        int mismatch = 0;
        for (int i=0; i<l; i++) {
            D("qa=" << q_a.top() << "\tqc=" << q_c.top() << endl);
            if (q_a.top() != q_c.top()) {
                mismatch++;
                D("mismatch=" << mismatch << endl);
                if (mismatch > 1) {
                    break;
                }
            }
            q_a.pop();
            q_c.pop();
        }

        cout << (mismatch < 2 ? "YES" : "NO") << endl;
    }
}
