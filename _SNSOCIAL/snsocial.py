import os
import copy

def debug(*args, **kwargs):
    if os.environ.get('DEBUG') is None:
        return
    print(*args, **kwargs)

def display(grid):
    for row in grid:
        for n in row:
            debug(n, "\t", end='')
        debug()

def max_neighbor(rows, cols, grid, cur_x, cur_y):
    m = -1

    if cur_x > 0:
        if cur_y > 0:
            v = grid[cur_y - 1][cur_x - 1]
            debug("TL", v)
            if v > m:
                m = v

        v = grid[cur_y][cur_x - 1]
        debug("L", v)
        if v > m:
            m = v

        if cur_y < rows - 1:
            v = grid[cur_y + 1][cur_x - 1]
            debug("BL", v)
            if v > m:
                m = v

    if cur_x < cols - 1:
        if cur_y > 0:
            v = grid[cur_y - 1][cur_x + 1]
            debug("TR", v)
            if v > m:
                m = v

        v = grid[cur_y][cur_x + 1]
        debug("R", v)
        if v > m:
            m = v

        if cur_y < rows - 1:
            v = grid[cur_y + 1][cur_x + 1]
            debug("BR", v)
            if v > m:
                m = v

    if cur_y > 0:
        v = grid[cur_y - 1][cur_x]
        debug("T", v)
        if v > m:
            m = v

    if cur_y < rows - 1:
        v = grid[cur_y + 1][cur_x]
        debug("B", v)
        if v > m:
            m = v

    return m

def solve(rows, cols, grid):
    debug("rows", rows, "cols", cols)

    iterations = 0

    did_something = True

    while did_something:

        debug("iteration", iterations)

        did_something = False

        snapshot = copy.deepcopy(grid)

        for j in range(rows):
            for i in range(cols):
                debug("j", j, "i", i)
                cur_val = snapshot[j][i]

                max_neigh_val = max_neighbor(rows, cols, snapshot, i, j)

                if max_neigh_val > cur_val:
                    grid[j][i] = max_neigh_val
                    debug("j", j, "i", i, "upgrade", max_neigh_val)
                    did_something = True

                display(grid)

        if did_something:
            debug("did something !")
            iterations += 1

    print(iterations)

def main():
    T = int(input())
    assert(T >= 1)
    assert(T <= 4)


    debug("T [%d]" % T)
    for i in range(T):
        debug("==== i [%d/%d]" % (i + 1, T))

        grid = []
        n, m = map(int, input().split())
        assert(n >= 1)
        assert(n <= 500)
        assert(m >= 1)
        assert(m <= 500)

        debug("n", n)
        debug("m", m)

        for j in range(n):
            row = list(map(int, input().split()))
            m_row = len(row)
            assert(m_row == m)
            grid.append(row)

        display(grid)

        solve(n, m, grid)

main()
