import os

CONSTRAINT_NONE = 0
CONSTRAINT_TOP = -1
CONSTRAINT_BOTTOM = 1


def debug(*args):
    if os.environ.get('DEBUG') is None:
        return
    print(*args)


def solve(n, top, bottom):

    debug("n", n)

    contrainte = CONSTRAINT_NONE

    found = False

    i = -1
    while i < n:
        i += 1
        if i >= n:
            break

        debug("i", i, "contrainte", contrainte,
              "top", top[i], "bottom", bottom[i])

        if found:

            if top[i] == '.' and bottom[i] == '.':

                debug("found, empty, FINISH")
                break

            elif top[i] == '#' and bottom[i] == '#':

                debug("found, full, SWAP")
                contrainte = -contrainte

            else:

                if contrainte == CONSTRAINT_NONE:

                    if bottom[i] == '#':

                        debug("single, no constraint, set bottom")
                        contrainte = CONSTRAINT_BOTTOM

                    if top[i] == '#':

                        debug("single, no constraint, set top")
                        contrainte = CONSTRAINT_TOP

                else:

                    if contrainte == CONSTRAINT_TOP and bottom[i] == '#':

                        debug("single, contrainte top, is bottom, BREAK")
                        break

                    if contrainte == CONSTRAINT_BOTTOM and top[i] == '#':

                        debug("single, contrainte bottom, is top, BREAK")
                        break

        else:

            if top[i] == '.' and bottom[i] == '.':

                debug("not found, empty, seek")

            elif top[i] == '#' and bottom[i] == '#':

                debug("not found, full, start")
                found = True
                assert(contrainte == CONSTRAINT_NONE)

            else:

                found = True

                if top[i] == '#':

                    contrainte = CONSTRAINT_TOP
                    debug("not found, start, single, contrainte top")

                else:

                    contrainte = CONSTRAINT_BOTTOM
                    debug("not found, start, single, contrainte bottom")

        debug("contrainte", contrainte)

    debug("FINAL", "i", i, "n", n)

    while i < n:
        if top[i] == '#' or bottom[i] == '#':
            print("no")
            return
        i += 1

    print("yes")


def main():
    T = int(input())
    assert(T >= 1)
    assert(T <= 500)

    debug("T [%d]" % T)
    for i in range(T):
        debug("==== i [%d/%d]" % (i + 1, T))

        n = int(input())
        assert(n >= 1)
        assert(n <= 500)

        top = list(input())
        debug(top)

        bottom = list(input())
        debug(bottom)

        assert(len(top) == n)
        assert(len(bottom) == n)

        solve(n, top, bottom)

main()
