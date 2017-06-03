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

class BoolArray {

private:
    vector<unsigned long long> data;
    unsigned int length;
    unsigned int data_length;

public:
    inline void reset() {
        this->data.clear();
        this->data.resize(this->data_length);
    }

    inline BoolArray(unsigned int len) {
        this->length = len;
        this->data_length = 1 + (this->length >> 6); // div 64bits
        this->data.reserve(this->data_length);
        reset();
    }

    void print() {
        vector<unsigned long long>::const_iterator it = this->data.begin();
        int i = 0;
        for (; it!=this->data.end(); it++) {
            cout << i++ << "=" << hex << *it << dec << "\t";
        }
        cout << endl;
    }

    inline void set(unsigned int n, bool value) {
        assert(n < this->length);
        unsigned long long idx = n >> 6; // div 64 bits
        unsigned long long off = n % 64;
        unsigned long long mask = 1ULL << off;
        unsigned long long & v = this->data.at(idx);
        if (value) {
            v |= mask;
        } else {
            v &= ~mask;
        }
        D("n=" << n << " idx=" << idx << " off=" << off << " mask=" << hex << mask << dec << " v=" << hex << v << dec << endl);
    }

    inline bool get(unsigned int n) {
        assert(n < this->length);
        unsigned long long idx = n >> 6; // div 64 bits
        unsigned long long off = n % 64;
        unsigned long long mask = 1ULL << off;
        unsigned long long & v = this->data.at(idx);
        return (v & mask) != 0;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    D("n=" << n << " k=" << k << endl);
    assert(n >= 1);
    assert(n <= MAX_SET_LENGTH);
    assert(k >= 1);
    assert(k <= MAX_SET_LENGTH);
}
