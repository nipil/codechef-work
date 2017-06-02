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
const int MAX_TEST = 4;
const int MAX_GRID = 500;
const int MAX_VALUE = 1000000;

typedef vector<int> IntVector;
typedef vector<IntVector> IntGrid;
typedef pair<int,int> Coord;
typedef vector<Coord> CoordVector;

ostream &operator << (ostream &a, const Coord &b)
{
    D("(" << b.first << "," << b.second << ") ");
	return a;
}

template <typename T>
ostream &operator << (ostream &a, const vector<T> &b)
{
    typename vector<T>::const_iterator it = b.begin();
    for (; it!=b.end(); it++) {
        D(*it << "\t");
    }
	return a;
}

ostream &operator << (ostream &a, const IntGrid &b)
{
    IntGrid::const_iterator it = b.begin();
    for (; it!=b.end(); it++) {
        D(*it << endl);
    }
	return a;
}

int solve(int n, int m, IntGrid& grid) {

    D("grid:" << endl << grid);

    int grid_min_value = MAX_VALUE;
    CoordVector grid_min_coords;

    int grid_max_value = 0;
    CoordVector grid_max_coords;

    // find grid minimum and maximum wealth (value & coords)
    for (int y=0; y<n; y++) {
        const IntVector& row = grid[y];
        for (int x=0; x<m; x++) {
            int v = row[x];
            D("x=" << x << " y=" << y << " v=" << v << endl);
            // update min/max if needed
            if (v > grid_max_value) {
                grid_max_value = v;
                grid_max_coords.clear();
                D("higher max" << endl);
            }
            if (v < grid_min_value) {
                grid_min_value = v;
                grid_min_coords.clear();
                D("lower min" << endl);
            }
            // store min/max coordinates
            if (v == grid_max_value) {
                grid_max_coords.push_back(make_pair(x, y));
            }
            if (v == grid_min_value) {
                grid_min_coords.push_back(make_pair(x, y));
            }
        }
    }

    D("minvalue=" << grid_min_value << endl
        << "coords:" << endl << grid_min_coords << endl
        << "maxvalue=" << grid_max_value << endl
        << "coords:" << endl << grid_max_coords << endl);
    
    // handle same wealth everywhere already
    if (grid_min_value == grid_max_value) {
        D("social from start !" << endl);
        return 0;
    }
    
    // search for maximum of the every minimum distance 
    int max_of_min_distance = -1;

    // iterate over poorest houses
    CoordVector::const_iterator poor = grid_min_coords.begin();
    for (;poor!= grid_min_coords.end(); poor++) {

        // search for min distance between this poor and each rich
        int min_distance = MAX_GRID + 1;
        
        // iterate over richest houses
        CoordVector::const_iterator rich = grid_max_coords.begin();
        for (; rich != grid_max_coords.end(); rich++) {

            // distance between 2 houses is max(delta_x, delta_y)
            // as we can move diagonally: see below example
            //     X
            //    X   delta_x = 5, delta_y = 3, distance = 5
            // XXX
            int distance = std::max(
                abs(poor->first - rich->first),
                abs(poor->second - rich->second)
            );
            
            D("poor=" << *poor << "rich=" << *rich << "distance=" << distance << endl);
            if (distance < min_distance) {
                min_distance = distance;
                D("min_distance=" << min_distance << endl);
            }
        }
        
        // update maximum distance if minimum found was greater
        if (min_distance > max_of_min_distance) {
            max_of_min_distance = min_distance;
            D("max_of_min_distance=" << max_of_min_distance << endl);
        }
    }
    
    int result = max_of_min_distance;
    D("result=" << result << endl);
    return result;
}

int main(int argc, char **argv)
{
    int T;
    cin >> T;
    D("T=" << T << endl);
    assert(T >= MIN_AMOUNT);
    assert(T <= MAX_TEST);

    IntGrid grid;

    for (int i=0; i<T; i++) {
        D("test: " << i + 1 << "/" << T << endl);
        
        int n;
        cin >> n;
        D("n=" << n << endl);
        assert(n >= MIN_AMOUNT);
        assert(n <= MAX_GRID);

        int m;
        cin >> m;
        D("m=" << m << endl);
        assert(m >= MIN_AMOUNT);
        assert(m <= MAX_GRID);

        grid.clear();

        int v;
        for (int j=0; j<n; j++) {

            IntVector row;
            for (int k=0; k<m; k++) {
                cin >> v;
                assert(v >= MIN_AMOUNT);
                assert(v <= MAX_VALUE);
                row.push_back(v);
            }

            grid.push_back(row);
        }

        int result = solve(n, m, grid);
        cout << result << endl;
    }

	return 0;
}
