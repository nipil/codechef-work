import os


def debug(*args):
    if os.environ.get('DEBUG') is None:
        return
    print(*args)


def solve(n, row):

    debug("n", n)

    snakes = 0
    mongooses = 0

    debug("row before:", row)

    i = -1
    while i < n:
        i += 1
        if i >= n:
            break

        debug("i", i)
        if i > 0:
            debug("prev", row[i - 1])
        debug("cur", row[i])
        if i < n - 1:
            debug("next", row[i + 1])

        if row[i] == 'm' and i > 0 and row[i - 1] == 's':
            row[i] = 'M'
            row[i-1] = ' '

        if row[i] == 'm' and i < n - 1 and row[i + 1] == 's':
            row[i] = 'M'
            row[i+1] = ' '

    debug("row after:", row)

    for w in row:
        if w == 'm' or w == 'M':
            mongooses += 1
        if w == 's':
            snakes += 1

    debug("snakes", snakes)
    debug("mongooses", mongooses)

    if snakes > mongooses:
        print("snakes")
    elif mongooses > snakes:
        print("mongooses")
    else:
        print("tie")

def main():
    T = int(input())
    assert(T >= 1)
    assert(T <= 100)

    debug("T [%d]" % T)
    for i in range(T):
        debug("==== i [%d/%d]" % (i + 1, T))


        row = list(input())
        n = len(row)
        assert(n >= 1)
        assert(n <= 100)

        debug(row)

        solve(n, row)

main()
