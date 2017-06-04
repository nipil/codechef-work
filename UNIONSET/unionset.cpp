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
        D("==== " << i + 1 << "/" << T << endl);
        solve();
    }
    return 0;
}

class BoolArray {

private:
    vector<unsigned long long> data;
    unsigned int start;
    unsigned int length;
    unsigned int storage_length;

public:
    inline void resetAll() {
        this->data.clear();
        this->data.resize(this->storage_length);
    }

    inline BoolArray(unsigned int len) {
        D("length_constructor " << this->length << endl);
        this->start = 0;
        this->length = len;
        this->storage_length = 1 + (this->length >> 6); // div 64bits
        this->data.reserve(this->storage_length);
        resetAll();
    }

    inline BoolArray(unsigned int start_included, unsigned int end_included) {
        D("range_constructor " << start_included << " " << end_included << endl);
        assert(start_included >= 0);
        assert(start_included <= end_included);
        this->start = start_included;
        this->length = end_included - start_included + 1;
        this->storage_length = 1 + (this->length >> 6); // div 64bits
        this->data.reserve(this->storage_length);
        resetAll();
    }

    void print() const {
        vector<unsigned long long>::const_iterator it = this->data.begin();
        int i = 0;
        for (; it!=this->data.end(); it++) {
            cout << i++ << "=" << hex << *it << dec << "\t";
        }
        cout << endl;
    }

    inline void set(unsigned int n) {
        n -= this->start;
        assert(n < this->length);
        unsigned long long idx = n >> 6; // div 64 bits
        unsigned long long off = n % 64;
        unsigned long long mask = 1ULL << off;
        unsigned long long & v = this->data.at(idx);
        v |= mask;
        D("n=" << n << " idx=" << idx << " off=" << off << " mask=" << hex << mask << dec << " v=" << hex << v << dec << endl);
    }

    inline void clear(unsigned int n) {
        n -= this->start;
        assert(n < this->length);
        unsigned long long idx = n >> 6; // div 64 bits
        unsigned long long off = n % 64;
        unsigned long long mask = 1ULL << off;
        unsigned long long & v = this->data.at(idx);
        v &= ~mask;
        D("n=" << n << " idx=" << idx << " off=" << off << " mask=" << hex << mask << dec << " v=" << hex << v << dec << endl);
    }

    inline bool get(unsigned int n) const {
        n -= this->start;
        assert(n < this->length);
        unsigned long long idx = n >> 6; // div 64 bits
        unsigned long long off = n % 64;
        unsigned long long mask = 1ULL << off;
        const unsigned long long & v = this->data.at(idx);
        return (v & mask) != 0;
    }

    static void Test() {
        BoolArray a(1,1);
        D("a1" << "=" << a.get(1) << endl);
        a.set(1);
        D("a1" << "=" << a.get(1) << endl);
        a.clear(1);
        D("a1" << "=" << a.get(1) << endl);

        D("s/e" << endl);
        BoolArray d(70);
        for (int i=0; i<5; i++) {
            D("d" << i << "=" << d.get(i) << endl);
            d.set(i);
            D("d" << i << "=" << d.get(i) << endl);
            d.clear(i);
            D("d" << i << "=" << d.get(i) << endl);
        }
        D("s/e" << endl);
        BoolArray b(1, 70);
        for (int i=1; i<=70; i++) {
            D("b" << i << "=" << b.get(i) << endl);
            b.set(i);
            D("b" << i << "=" << b.get(i) << endl);
            b.clear(i);
            D("b" << i << "=" << b.get(i) << endl);
        }

        // BoolArray::Test();
        int l = 63;
        BoolArray x(l), y(l);
        for (int i=0; i<l; i++) {
            x.set(i);
            y.set(i);
        }
        D("result=" << BoolArray::UnionHasAll(a, b) << endl);
        a.clear(0);
        b.clear(0);
        D("result=" << BoolArray::UnionHasAll(a, b) << endl);
    }

    static inline bool UnionHasAll(const BoolArray& a, const BoolArray& b) {
        assert(a.length == b.length);
        int last_full = (a.length >> 6) - 1;

        // test every full
        D("last_full=" << last_full << endl);
        for (int i=0; i<=last_full; i++) {
            unsigned long long ai = a.data.at(i);
            D("A" << i << "=" << hex << ai << dec << endl);
            unsigned long long bi = b.data.at(i);
            D("B" << i << "=" << hex << bi << dec << endl);
            unsigned long long r = ~(a.data.at(i) | b.data.at(i));
            D("R" << i << "=" << hex << r << dec << endl);
            if (r != 0) {
                return false;
            }
        }

        int remain = a.length % 64;
        D("remain=" << remain << endl);
        if (remain == 0) {
            D("completed" << endl);
            return true;
        }

        int last = last_full + 1;
        D("last=" << last << endl);
        unsigned long long mask = (1ULL << remain) - 1;
        D("mask=" << hex << mask << dec << endl);
        unsigned long long r = a.data.at(last) | b.data.at(last);
        D("R=" << hex << r << dec << endl);
        return (r == mask);
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

    // data for all sets
    vector<BoolArray> data;
    for (int i=0; i<n; i++) {
        // flag storage for current set
        BoolArray current(1, k);

        // read set length
        int l;
        cin >> l;
        D("L" << i << "=" << l << endl);

        // iterate over input
        for (int j=0; j<l; j++) {
            int v;
            cin >> v;
            D("V" << j << "=" << v << endl);
            // set flag when present
            current.set(v);
        }

        // add this set to all sets
        data.push_back(current);
    }

    // single-set edge case
    if (n == 1) {
/*
        // test set with itself
        BoolArray& d = data.front();
        bool result = BoolArray::UnionHasAll(d, d);
        if (result) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
*/
        // do not test set with itself
        cout << 0 << endl;

        // end testing for this test case
        return;
    }

    // cross-set results
    int valid = 0;
    vector<BoolArray>::const_iterator it_a, it_b;
    it_a = data.begin();
    for (; it_a != data.end(); it_a++) {
        it_b = it_a + 1;
        for (; it_b != data.end(); it_b++) {
            bool result = BoolArray::UnionHasAll(*it_a, *it_b);
            valid += result ? 1 : 0;
        }
    }
    cout << valid << endl;
}
