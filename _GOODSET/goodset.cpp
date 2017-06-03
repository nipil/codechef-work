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
 
const int MIN_AMOUNT = 1;
const int MAX_AMOUNT = 100;
 
template <typename T>
ostream &operator << (ostream &a, const vector<T> &b)
{
    typename vector<T>::const_iterator it = b.begin();
    for (; it!=b.end(); it++) {
        D(*it << "\t");
    }
	return a;
}
 
void solve(int n) {
 
    D("n:" << n << endl);
 
    vector<int> goodset;
    
    int a=1, b=2, c;
    
    if (n == 1) {
        cout << a << endl;
        return;
    }
 
    cout << a << " " << b;
    if (n == 2) {
            cout << endl;
            return;
    }
    
    n -= 2;
    while(n--) {
        c = b + a + 1;
        cout << " " << c;
        a = b;
        b = c;
    }
    
    cout << endl;
}
 
int main(int argc, char **argv)
{
    int T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= MIN_AMOUNT);
    assert(T <= MAX_AMOUNT);
 
    for (int i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);
        
        int n;
        cin >> n;
        D("n=" << n << endl);
        assert(n >= MIN_AMOUNT);
        assert(n <= MAX_AMOUNT);
 
        solve(n);
    }
 
	return 0;
}
