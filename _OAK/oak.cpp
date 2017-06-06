/*
SUBMIT AS C++14

empty WA submit:
- subtask1 0.85s
- subtask2 0.86s
- subtask3 0.93s
- subtask4 0.89s
*/

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
#include <cstdint>
#include <climits>

using namespace std;

template <typename T>
ostream &operator << (ostream &a, const vector<T> &b)
{
    typename vector<T>::const_iterator it = b.begin();
    for (; it!=b.end(); it++) {
        if (it != b.begin())
            D("\t");
        D(*it);
    }
    return a;
}

void solve();

template <typename T>
inline void read_integer(T& target, const T& minValue, const T& maxValue) {
    cin >> target;
    D("target=" << target << "\tmin=" << minValue << "\tmax=" << maxValue << endl);
    assert(target >= minValue);
    assert(target <= maxValue);
}

inline void do_tests(unsigned long long minT, unsigned long long maxT) {
    unsigned long long T;
    read_integer(T, minT, maxT);
    for (unsigned long long i=0; i<T; i++) {
        D("==== Test " << i + 1 << "/" << T << endl);
        solve();
    }
}

int main(int argc, char **argv)
{
    do_tests(1, 5);
    return 0;
}

/***************************************************************************/

class Branch {
public:
    unsigned long long id;
    unsigned long long w;
    unsigned long long c;
    unsigned long long parent;
    vector<unsigned long long> children;
};

ostream &operator << (ostream &a, const Branch &b)
{
    D("Branch: id=" << b.id << "\tw=" << b.w << "\tc=" << b.c << "\tparent=" << b.parent << "\tcchildren=[" << b.children << "]");
}

class Event {
public:
    unsigned long long id;
    unsigned long long state;
    unsigned long long q;
    unsigned long long u;
    unsigned long long x;
};

ostream &operator << (ostream &a, const Event &e)
{
    D("Event: id=" << e.id << "\ts=" << e.state << "\tq=" << e.q << "\tu=" << e.u << "\tx=" << e.x);
}

typedef vector<Branch> Branches;
typedef vector<Event> Events;

inline void subtask_1_small(unsigned long long n, unsigned long long m, Branches& branches, Events& events);
inline void subtask_2_nopersist(unsigned long long n, unsigned long long m, Branches& branches, Events& events);
inline void subtask_3_nobird(unsigned long long n, unsigned long long m, Branches& branches, Events& events);
inline void subtask_4_general(unsigned long long n, unsigned long long m, Branches& branches, Events& events);

inline void solve() {

    unsigned long long n, m;
    read_integer(n, 1ULL, 100000ULL);
    read_integer(m, 1ULL, 100000ULL);
    D("n=" << n << "\tm=" << m << endl);

    // problem classification
    bool small_dataset = (n <= 100 && m <= 100);
    bool need_persist = false;
    bool no_bird = true;

    D("Building trunk..." << endl);

    Branches branches(n+1);

    Branch& trunk = branches[0];
    trunk.id = 0;
    trunk.w = ULLONG_MAX;
    trunk.c = 0;
    trunk.parent = 0;
    D("trunk=" << trunk << endl);

    D("Building branches..." << endl);

    for (unsigned long long i=1; i<=n; i++) {
        unsigned long long p, w;
        read_integer(p, 0ULL, i-1);
        read_integer(w, 0ULL, 10000000ULL);

        D("i=" << i << "\tp=" << p << "\tw=" << w << endl);
        Branch& branch = branches[i];
        branch.id = i;
        branch.w = w;
        branch.c = 0;
        branch.parent = p;
        branches[branch.parent].children.push_back(i);
    }

    for (Branches::const_iterator it = branches.begin(); it != branches.end(); it++) {
        D("branch=" << *it << endl);
    }

    D("Building events..." << endl);

    Events events(m);

    for (unsigned long long i=0; i<m; i++) {
        unsigned long long state, q, u, x;
        read_integer(state, 0ULL, m-1);
        read_integer(q, 1ULL, 2ULL);
        read_integer(u, 1ULL, n);
        if (q == 1) {
            read_integer(x, 0ULL, 10000000ULL);
        } else {
            x = 0;
        }
        D("id=" << i << "\tstate=" << state << "\tq=" << q << "\tu=" << u << "\tx=" << x << endl);

        if (i != state) {
            need_persist = true;
            D("need_persist" << endl);
        }

        if (q == 2) {
            no_bird = false;
            D("has_birds" << endl);
        }

        Event& event = events[i];
        event.id = i;
        event.state = state;
        event.q = q;
        event.u = u;
        event.x = x;
    }

    for (Events::const_iterator it = events.begin(); it != events.end(); it++) {
        D("event=" << *it << endl);
    }

    D("small_dataset=" << small_dataset << "\tneed_persist=" << need_persist << "\tno_bird=" << no_bird << endl);
    if (small_dataset) {
        subtask_1_small(n, m, branches, events);
    } else if (!need_persist) {
        subtask_2_nopersist(n, m, branches, events);
    } else if (no_bird) {
        subtask_3_nobird(n, m, branches, events);
    } else {
        subtask_4_general(n, m, branches, events);
    }
}

inline void subtask_1_small(unsigned long long n, unsigned long long m, Branches& branches, Events& events) {
    cout << "subtask_1_small" << endl;
}

inline void subtask_2_nopersist(unsigned long long n, unsigned long long m, Branches& branches, Events& events) {
    cout << "subtask_2_nopersist" << endl;
}

inline void subtask_3_nobird(unsigned long long n, unsigned long long m, Branches& branches, Events& events) {
    cout << "subtask_3_nobird" << endl;
}

inline void subtask_4_general(unsigned long long n, unsigned long long m, Branches& branches, Events& events) {
    cout << "subtask_4_general" << endl;
}
